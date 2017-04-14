
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>
#include <math.h>
#include <time.h>
extern "C" {
#include <fpgacl_memory.h>
#include <measurement.h>
#include <set_frequency.h>
#include <monitoring.h>
}

#include "accel.h"
extern char log_file_name[1000];

#define HARDWARE_ITERATION 10
#define NUMBER_OF_HARDWARE_ITERATION_FOR_MANUAL_POWER_MONITORING 1

void init_array(float* h_CallCPU, float*  h_PutCPU, float*  h_S, float*  h_X, float*   h_T, int optionCount);
int run_command(char cmd[1000]);
void refresh_hardware(int *accel_status);
extern "C" void BlackScholesCPU(
    float *h_Call, //Call option price
    float *h_Put,  //Put option price
    float *h_S,    //Current stock price
    float *h_X,    //Option strike price
    float *h_T,    //Option years
    float R,       //Riskless rate of return
    float V,       //Stock volatility
    unsigned int optionCount
);
void BlackScholes_hw(
    float *h_Call, //Call option price
    float *h_Put,  //Put option price
    float *h_S,    //Current stock price
    float *h_X,    //Option strike price
    float *h_T,    //Option years
    unsigned int optionCount
) ;

int validate(float* data_sw, float* data_hw, int optionCount) {
	int i;

	for (i = 0; i < optionCount; i++) {
		float hw = data_hw[i];
		float sw = data_sw[i];

		float diff = fabs(hw - sw);
		if(diff > 0.001 || diff != diff){
			printf("Error in out_data at c_hw[%d] = %f != c_sw[%d] = %f\n", i, hw, i,  sw);
			return -1;
		}
	}
	return 0;
}

float randFloat(float low, float high){
    float t = (float)rand() / (float)RAND_MAX;
    return (1.0f - t) * low + t * high;
}

int main(int argc, char **argv) {
	printf("check point 1\n");
	int accel_status = 0;
	float	*h_CallCPU,
	        *h_PutCPU,
	        *h_CallFPGA,
	        *h_PutFPGA,
	        *h_S,
	        *h_X,
	        *h_T,
			*h_SFPGA,
	        *h_XFPGA,
	        *h_TFPGA;


	int status;

	double time_scale_hardware = 1.0;
   	double hardware_start;
   	double hardware_end;
	double hardware_execution_time;

	double software_start;
   	double software_end;
   	double software_execution_time;

   	FILE* fp_v;
   	printf("check point 2\n");

	const unsigned int   optionCount = OPT_N;
	const float                    R = 0.02f;
	const float                    V = 0.30f;

	h_CallCPU = (float *)malloc(optionCount * sizeof(float));
	h_PutCPU = (float *)malloc(optionCount * sizeof(float));

	float	*memory = (float *)malloc(5*optionCount * sizeof(float));
	float	*h_CallFPGA_results = memory + 0 * optionCount;
	float	*h_PutFPGA_results  = memory + 1 * optionCount;
	h_S                = memory + 2 * optionCount;
	h_X                = memory + 3 * optionCount;
	h_T                = memory + 4 * optionCount;

	srand(time(NULL));
	printf("check point 3\n");


	init_array(h_CallCPU, h_PutCPU, h_S, h_X, h_T, optionCount);

	printf("check point 4\n");
	software_start = getTimestamp();
	for (u32 i = 0; i < 10; i++)
		BlackScholesCPU(h_CallCPU, h_PutCPU, h_S, h_X, h_T, R, V, optionCount);
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(10*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

	int frequency_factor_min = 5;
	int vccint_min = 0.67;

	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);
	VOLTAGE_SCALING_PROLOGUE(vccint_min, 1, 0.01);
	FREQUENCY_SCALING_PROLOGUE(frequency_factor_min, 50, 1);

	refresh_hardware(&accel_status);

	init_array(h_CallCPU, h_PutCPU, h_S, h_X, h_T, optionCount);

	if ( (h_CallFPGA=(DATA_TYPE *)fpgacl_malloc(optionCount*sizeof(DATA_TYPE))) == NULL )
			perror("memory allocation for h_CallFPGA");
	if ( (h_PutFPGA=(DATA_TYPE *)fpgacl_malloc(optionCount*sizeof(DATA_TYPE))) == NULL )
			perror("memory allocation for h_PutFPGA");
	if ( (h_SFPGA=(DATA_TYPE *)fpgacl_malloc(optionCount*sizeof(DATA_TYPE))) == NULL )
			perror("memory allocation for h_SFPGA");
	if ( (h_XFPGA=(DATA_TYPE *)fpgacl_malloc(optionCount*sizeof(DATA_TYPE))) == NULL )
			perror("memory allocation for h_XFPGA");
	if ( (h_TFPGA=(DATA_TYPE *)fpgacl_malloc(optionCount*sizeof(DATA_TYPE))) == NULL )
			perror("memory allocation for h_TFPGA");

	fpgacl_memwrite((void *)h_CallCPU, (u32*)h_CallFPGA, sizeof(DATA_TYPE)*optionCount);
	fpgacl_memwrite((void *)h_PutCPU, (u32*)h_PutFPGA, sizeof(DATA_TYPE)*optionCount);
	fpgacl_memwrite((void *)h_S, (u32*)h_SFPGA, sizeof(DATA_TYPE)*optionCount);
	fpgacl_memwrite((void *)h_X, (u32*)h_XFPGA, sizeof(DATA_TYPE)*optionCount);
	fpgacl_memwrite((void *)h_T, (u32*)h_TFPGA, sizeof(DATA_TYPE)*optionCount);

	//--------------------validation check start------------------------------------------

	BlackScholesCPU(h_CallCPU, h_PutCPU, h_S, h_X, h_T, R, V, optionCount);
	BlackScholes_hw(h_CallFPGA, h_PutFPGA, h_SFPGA, h_XFPGA, h_TFPGA, optionCount);

	fpgacl_memread((void*)h_CallFPGA_results, (u32 *)h_CallFPGA, sizeof(float)*optionCount);


	status = validate(h_CallCPU, h_CallFPGA_results, optionCount);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
		printf("Validation FAILED!\n");
		frequency_factor_min = freq+1;
	}
	//--------------------validation check end------------------------------------------

	if (status == 0) {

		//=============================================================================
		// compute the iteration_number
		//=============================================================================

		hardware_start = getTimestamp();
		for (int i = 0; i < HARDWARE_ITERATION; i++)
			BlackScholes_hw(h_CallFPGA, h_PutFPGA, h_SFPGA, h_XFPGA, h_TFPGA, optionCount);

		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(HARDWARE_ITERATION*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 2000/hardware_execution_time;

		fp_v=fopen(log_file_name, "a");


		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++)
			BlackScholes_hw(h_CallFPGA, h_PutFPGA, h_SFPGA, h_XFPGA, h_TFPGA, optionCount);
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");

		if(NUMBER_OF_HARDWARE_ITERATION_FOR_MANUAL_POWER_MONITORING != 1) {
			printf("huge number of iteration applied for manual power monitoring \n");

			for(int i = 0; i < NUMBER_OF_HARDWARE_ITERATION_FOR_MANUAL_POWER_MONITORING; i++) {
				for(int j = 0; j < NUMBER_OF_HARDWARE_ITERATION_FOR_MANUAL_POWER_MONITORING; j++) {
					BlackScholes_hw(h_CallFPGA, h_PutFPGA, h_SFPGA, h_XFPGA, h_TFPGA, optionCount);
				}
			}
		}
		fclose(fp_v);
	}

	fpgacl_free((u32)h_CallFPGA);
	fpgacl_free((u32)h_PutFPGA);
	fpgacl_free((u32)h_SFPGA);
	fpgacl_free((u32)h_XFPGA);
	fpgacl_free((u32)h_TFPGA);


	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();

	//==================================================================
	//        END:: HARDWARE ACCELERATOR
	//==================================================================



	free(h_CallCPU);
	free(h_PutCPU);
	free(memory);


	return 0;
}

void BlackScholes_hw(
    float *h_Call, //Call option price
    float *h_Put,  //Put option price
    float *h_S,    //Current stock price
    float *h_X,    //Option strike price
    float *h_T,    //Option years
    unsigned int optionCount
) {

	accel_write(h_Call, h_Put, h_S, h_X, h_T, optionCount );
	accel_start();
	//accel_wait();  //polling
	sleep(100);       //interrupt

}

void init_array(float* h_CallCPU, float*  h_PutCPU, float*  h_S, float*  h_X, float*   h_T, int optionCount)  {
	for(unsigned int i = 0; i < optionCount; i++){
		h_CallCPU[i]  = -1.0f;
		h_PutCPU[i]   = -1.0f;
		h_S[i]        = randFloat(5.0f, 30.0f);
		h_X[i]        = randFloat(1.0f, 100.0f);
		h_T[i]        = randFloat(0.25f, 10.0f);
	}
}

int run_command(char cmd[1000]) {
	FILE *pp;
	int status = 0;
	pp = popen(cmd, "r");
	if (pp != NULL) {
	    while (1) {
	      char *line;
	      char buf[1000];
	      line = fgets(buf, sizeof buf, pp);
	      if (line == NULL) break;
	      if (line[0] == 'd') printf("%s", line); /* line includes '\n' */
	    }
	    status = -1;
	}
	pclose(pp);
	return status;
}


void refresh_hardware(int *accel_status) {
	char cmd[100];

	sprintf(cmd, "chmod u+x initial.sh");
	run_command(cmd);

	sprintf(cmd, "chmod u+x clean.sh");
	run_command(cmd);

	if (*accel_status == 0) {

		printf("refresh_hardware: check point 1\n");
		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		accel_prologue();

		sprintf(cmd, "cat bs-stream.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat bs-stream.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}






}
