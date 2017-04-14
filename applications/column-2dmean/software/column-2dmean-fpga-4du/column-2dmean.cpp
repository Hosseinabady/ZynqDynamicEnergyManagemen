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
void init_data(float* c_golden, float* b_golden, int n, int m);



#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM  10

void init_data(DATA_TYPE *data, int n, int m);

void column_2dmean_golden(DATA_TYPE *  data, DATA_TYPE *  mean_sw, DATA_TYPE  float_n, int n, int m);

void column_2dmean_hw(DATA_TYPE *  data, DATA_TYPE *  mean, int n);

int validate(DATA_TYPE *mean_sw, DATA_TYPE *mean_hw, int m);
int main(int argc, char *argv[])
{

	int accel_status = 0;
	int n = N;
	int m = M;
	int status;
	FILE* fp_v;
	char cmd[100];

 	DATA_TYPE *data_sw;
 	DATA_TYPE *mean_sw;
 	DATA_TYPE *mean_hw_result;
 	DATA_TYPE *data_hw;
 	DATA_TYPE *mean_hw;


 	data_sw = (DATA_TYPE *)malloc(n*m*sizeof(DATA_TYPE));
	mean_sw = (DATA_TYPE *)malloc(m*sizeof(DATA_TYPE));
	mean_hw_result = (DATA_TYPE *)malloc(m*sizeof(DATA_TYPE));

	DATA_TYPE float_n = 1.0*n;

	init_data(data_sw, n, m);

	software_start = getTimestamp();
	column_2dmean_golden(data_sw, mean_sw, float_n, n, m);
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);



	int frequency_factor_min = 10;
	int vccint_min = 0.65;

	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);
	VOLTAGE_SCALING_PROLOGUE(vccint_min, 0.83, 0.01);
	FREQUENCY_SCALING_PROLOGUE(frequency_factor_min, 50, 1);


	refresh_hardware(&accel_status);
	if ( (data_hw=(DATA_TYPE *)fpgacl_malloc(n*m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (mean_hw=(DATA_TYPE *)fpgacl_malloc(m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for b");



	//--------------------validation check start------------------------------------------
	init_data(data_sw, n, m);
	fpgacl_memwrite((void *)data_sw, (u32*)data_hw, sizeof(DATA_TYPE)*n*m);



	column_2dmean_hw(data_hw, mean_hw, n);
	column_2dmean_golden(data_sw, mean_sw, float_n, n, m);

	fpgacl_memread((void*)mean_hw_result, (u32 *)mean_hw, sizeof(DATA_TYPE)*m);

	status = validate(mean_sw, mean_hw_result, m);
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
			column_2dmean_hw(data_hw, mean_hw, n);
		}

		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 4000/hardware_execution_time;
		//============================================================================
		fp_v=fopen(log_file_name, "a");
		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			column_2dmean_hw(data_hw, mean_hw, n);
		}
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");

		if (MANUAL_POWER_MONITOR_ITERATION != 1) {
			printf("loop for manual power monitoring!\n");
			for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
				for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
					column_2dmean_hw(data_hw, mean_hw, n);
				}
			}
		}
		fclose(fp_v);
	}

	fpgacl_free((u32)data_hw);
	fpgacl_free((u32)mean_hw);

	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();


	free(data_sw);
	free(mean_sw);
	free(mean_hw_result);


	return(status);
}

void column_2dmean_golden(DATA_TYPE *  data, DATA_TYPE *  mean_sw, DATA_TYPE  float_n, int n, int m)
{

	for (int j = 0; j < m; j++)  {
		mean_sw[j] = 0.0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)  {
	    	DATA_TYPE d_1 = data[(i)*m+j];
	    	mean_sw[j] += d_1;

		}
	}

	for (int j = 0; j < m; j++)  {
		mean_sw[j] /= float_n;
	}
}



void column_2dmean_hw(DATA_TYPE *  data, DATA_TYPE *  mean, int n) {


	accel_write(data, mean, n);
	accel_start();
	sleep(1);  //interrupt

	//accel_wait(); //polling

}

int validate(DATA_TYPE *mean_sw, DATA_TYPE *mean_hw, int m) {
	int status;

	for (int row = 0; row < m; row++) {

		float hw = mean_hw[row];
		float sw = mean_sw[row];

		float diff = fabs(hw - sw);
		if(diff > 0.001 || diff != diff){
			printf("Error in data at mean_hw[%d] = %f != mean_sw[%d] = %f\n", row, hw, row, sw);
			return -1;
		}
		if (row == 100) {
			printf("data  at data at mean_hw[%d] = %f != mean_sw[%d] = %f\n", row, hw, row, sw);
		}
	}

	return 0;
}



void init_data(DATA_TYPE *data, int n, int m) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			data[i*m+j] = (i+j)*(rand()/(RAND_MAX*1.0));
		}
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


		sprintf(cmd, "cat   column-2dmean_parallel.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);


		sprintf(cmd, "cat   column-2dmean_parallel.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}


}
