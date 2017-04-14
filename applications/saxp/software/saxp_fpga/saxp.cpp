
#define POLYBENCH_USE_SCALAR_LB
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <sched.h>        // for sched_xxx() function calls
#include <sys/types.h>    // for pid_t
#include <sys/resource.h> // for getpriority()
#include <time.h>

extern "C" {
#include <fpgacl_memory.h>
#include <measurement.h>
#include <set_frequency.h>
#include <monitoring.h>
}

#include "accel.h"

extern char log_file_name[1000];

#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM  10

void refresh_hardware(int *accel_status);
int run_command(char cmd[1000]);



double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}


void init_array(float* a, float* b)
{
	time_t t;
	srand((unsigned) time(&t));

	int i;
	for (i = 0; i < DATA_LENGTH; i++) {
		a[i] = rand()/(float)RAND_MAX;//row
		b[i] = rand()/(float)RAND_MAX;//row
	}

}



void kernel_sw(float* a, float* b) {

	int i;
	for (i = 0; i < DATA_LENGTH; i++) {
		b[i] = 2.34*a[i] + 5.2355;
	}
}


double software_part_start;
double software_part_end;
double hardware_part_start;
double hardware_part_end;

int first_iteration;
double software_part_time = 0;
double hardware_part_time = 0;

void kernel_hw(float* a, float* b, u32 n) {

	accel_write(a, b, n);
	accel_start();
	sleep(1);
	//accel_wait();
}

int validate(float* c_sw, float* c_hw ) {
	int i;

	for (i = 0; i < DATA_LENGTH; i++) {
		float hw = c_hw[i];
		float sw = c_sw[i];
//		printf("Data at out_data at c_hw[%d] = %f != c_sw[%d] = %f\n", i, hw, i,  sw);

		float diff = fabs(hw - sw);
		if(diff > 0.001 || diff != diff){
			printf("Error in out_data at c_hw[%d] = %f != c_sw[%d] = %f\n", i, hw, i,  sw);
			return -1;
		}
	}
	return 0;
}
#define SOFTWARE_ITERATION 10

int main(int argc, char** argv)
{

	int accel_status = 0;
	int status;

	double time_scale_hardware = 1.0;
   	double hardware_start;
   	double hardware_end;
	double hardware_execution_time;
	FILE* fp_v;
	double software_start;
   	double software_end;
   	double software_execution_time;


   	printf("main: check point 1\n");


   	/* Variable declaration/allocation. */


	//time_scale_hardware = 1 / 30.0;

	float* a_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);
	float* b_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);
	float* b_hw_result = (float *)malloc(sizeof(float)*DATA_LENGTH);


	DATA_TYPE *a_hw;
	DATA_TYPE *b_hw;
	DATA_TYPE *c_hw;

	init_array(a_sw, b_sw);


	software_start = getTimestamp();
	for (int i = 0; i < SOFTWARE_ITERATION; i++) {
		kernel_sw(a_sw, b_sw);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);



	int frequency_factor_min = 16;
	int vccint_min = 0.67;


	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);
	VOLTAGE_SCALING_PROLOGUE(vccint_min, 0.73, 0.01);
	FREQUENCY_SCALING_PROLOGUE(frequency_factor_min, 50, 1);

	refresh_hardware(&accel_status);



	if ( (a_hw=(DATA_TYPE *)fpgacl_malloc(DATA_LENGTH*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (b_hw=(DATA_TYPE *)fpgacl_malloc(DATA_LENGTH*sizeof(DATA_TYPE))) == NULL )
			perror("memory allocation for b");

	init_array(a_sw, b_sw);
	fpgacl_memwrite((void *)a_sw, (u32*)a_hw, sizeof(DATA_TYPE)*DATA_LENGTH);

	kernel_hw(a_hw, b_hw, DATA_LENGTH);
	kernel_sw(a_sw, b_sw);

	fpgacl_memread((void*)b_hw_result, (u32 *)b_hw, sizeof(float)*DATA_LENGTH);

	status = validate(b_sw, b_hw_result);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
		printf("Validation FAILED!\n");
		frequency_factor_min = freq+1;
	}


	if (status == 0) {
		//=============================================================================
		// compute the iteration_number
		//=============================================================================


		hardware_start = getTimestamp();
		for (int i = 0; i < EXE_TIME_MONITORING_ITERATION_NUM; i++) {
			kernel_hw(a_hw, b_hw, DATA_LENGTH);
		}
		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 2000/hardware_execution_time;
		//============================================================================
		fp_v=fopen(log_file_name, "a");
		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			kernel_hw(a_hw, b_hw, DATA_LENGTH);
		}
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");

		fclose(fp_v);
	}

	fpgacl_free((u32)a_hw);
	fpgacl_free((u32)b_hw);

	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();


	//==================================================================
	//        END:: HARDWARE ACCELERATOR
	//==================================================================


	// Be clean.
	free(a_sw);
	free(b_sw);


	fpgacl_free((u32)a_hw);
	fpgacl_free((u32)b_hw);



	free(b_hw_result);

	return 0;
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

		sprintf(cmd, "cat saxp_4X.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat  saxp_4X.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}






}
