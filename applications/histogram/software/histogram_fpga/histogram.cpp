#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "accel.h"

extern "C" {
#include <measurement.h>
#include <set_frequency.h>
#include <fpgacl_memory.h>
#include <monitoring.h>
}


#include <sys/time.h>
#include <time.h>


extern char log_file_name[1000];

double hardware_start;
double hardware_end;
double hardware_execution_time;

double software_start;
double software_end;
double software_execution_time;


void refresh_hardware(int *accel_status);
int run_command(char cmd[1000]);
void init_data(DATA_TYPE* data, u32 *histogram, u32 n);



#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM  10
#define SOFTWARE_ITERATION                 10


void histogram_sw(DATA_TYPE *  data,
		u32 *  histogram);

void histogram_accel(DATA_TYPE *  data,
		u32 *  histogram);

int validate(u32 *histogram_golden,
		     u32 *histogram_hw);
int main(int argc, char *argv[])
{

	int accel_status = 0;
	DATA_TYPE *data_golden;
	u32       *histogram_golden;
	DATA_TYPE *data_hw;
	u32 *histogram_hw,*histogram_hw_result;

	int status;

	FILE* fp_v;
	char cmd[100];

	printf("Please give m and n: ");

	printf("\n");

	if ( (data_golden=(DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (histogram_golden=(u32 *)malloc(BIN_LENGTH*sizeof(u32))) == NULL )
		perror("memory allocation for b");


	if ( (histogram_hw_result=(u32 *)malloc(BIN_LENGTH*sizeof(u32))) == NULL )
		perror("memory allocation for a");


	printf("accel_prologue ceck point 1\n");



	init_data(data_golden, histogram_golden, DATA_LENGTH);



	software_start = getTimestamp();
	for (int i = 0; i < SOFTWARE_ITERATION; i++) {
		histogram_sw(data_golden, histogram_golden);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

	int frequency_factor_min = 5;
	int vccint_min = 0.67;


	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);
	VOLTAGE_SCALING_PROLOGUE(vccint_min, 0.93, 0.01);
	FREQUENCY_SCALING_PROLOGUE(frequency_factor_min, 50, 1);

	refresh_hardware(&accel_status);

	if ( (data_hw=(DATA_TYPE *)fpgacl_malloc(DATA_LENGTH*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (histogram_hw=(u32 *)fpgacl_malloc(BIN_LENGTH*sizeof(u32))) == NULL )
		perror("memory allocation for b");


	//--------------------validation check start------------------------------------------
	init_data(data_golden, histogram_golden, DATA_LENGTH);
	fpgacl_memwrite((void *)data_golden, (u32*)data_hw, sizeof(DATA_TYPE)*DATA_LENGTH);

	fpgacl_memwrite((void *)histogram_golden, (u32*)histogram_hw, sizeof(BIN_LENGTH*sizeof(u32)));

	hardware_start = getTimestamp();

	histogram_accel(data_hw, histogram_hw);

	hardware_end = getTimestamp();
	hardware_execution_time = (hardware_end-hardware_start)/(1000);
	printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);


	histogram_sw(data_golden, histogram_golden);

	fpgacl_memread((void*)histogram_hw_result, (u32 *)histogram_hw, sizeof(u32)*BIN_LENGTH);

	status = validate(histogram_golden, histogram_hw_result);
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
		for (int i = 0; i < EXE_TIME_MONITORING_ITERATION_NUM; i++) {
			histogram_accel(data_hw, histogram_hw);
		}

		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 2000/hardware_execution_time;
		//============================================================================
		fp_v=fopen(log_file_name, "a");
		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			histogram_accel(data_hw, histogram_hw);;
		}
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");


		fclose(fp_v);
	}

	fpgacl_free((u32)data_hw);
	fpgacl_free((u32)histogram_hw);


	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();



	free(data_golden);
	free(histogram_golden);

	free(histogram_hw_result);



	return(status);
}

void histogram_sw(DATA_TYPE *  data, u32 *  histogram)
{

	srand((unsigned) time(NULL));

	for (int i = 0; i < DATA_LENGTH; i++) {
		u32 index =  (u32)data[i];
		if (index > 255) {
			printf("Error in input data at data[%d]=%f is greater than 255\n", i,data[i]);
			return;
		}
		histogram[index]++;
	}
}



void histogram_accel(DATA_TYPE *  data,
		    u32 *  histogram) {


	accel_write(data, histogram);
//	printf("mxv_hw: started\n");

	accel_start();
	sleep(10);  //interrupt

//	accel_wait(); //polling
//	printf("mxv_hw: end\n");


}

int validate(u32 *histogram_golden,
		     u32 *histogram_hw) {
	int status = 0;
	for(int i = 0; i < BIN_LENGTH; i++) {
		u32 hw = histogram_hw[i];
		u32 sw = histogram_golden[i];
		u32 diff = hw - sw;
		if(diff != 0){
			printf("Error in out_data at A_hw[%d] = %d != A_sw[%d] = %d\n", i, hw, i, sw);
			status = -1;
			break;
		}
	}
	return status;
}

void init_data(DATA_TYPE* data, u32 *histogram, u32 n){


	  int i, j;

	  for (i = 0; i < DATA_LENGTH; i++) {
		  data[i] = (u32)((float)rand()/(float)(RAND_MAX)) * 255;
	  }
	  for (int i = 0; i < BIN_LENGTH; i++) {
		  histogram[i] = 0;
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

		sprintf(cmd, "cat histogram.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat  histogram.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}






}
