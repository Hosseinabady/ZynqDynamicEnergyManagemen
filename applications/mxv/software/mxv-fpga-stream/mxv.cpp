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

void init_data(float* c_golden, float* b_golden, int n, int m);

void mxv_golden(int n, int m, DATA_TYPE *  a,
		DATA_TYPE *  b, DATA_TYPE *  c);

void mxv_hw(int n, int m, DATA_TYPE *  a,
		DATA_TYPE *  b, DATA_TYPE *  c);

int validate(int n, int m,
		     DATA_TYPE *a_golden,
		     DATA_TYPE *a_hw);
int main(int argc, char *argv[])
{

	int accel_status = 0;
	DATA_TYPE *a_golden,*b_golden,*c_golden;
	DATA_TYPE *a_hw,*b_hw,*c_hw, *a_hw_result;
	int status;
	int i, j, m, n;
	FILE* fp_v;
	char cmd[100];

	printf("Please give m and n: ");
	n=N;
	m=M;
	printf("\n");

	if ( (a_golden=(DATA_TYPE *)malloc(n*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (b_golden=(DATA_TYPE *)malloc(m*n*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for b");
	if ( (c_golden=(DATA_TYPE *)malloc(m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for c");




	if ( (a_hw_result=(DATA_TYPE *)malloc(n*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");

	printf("Initializing matrix b and vector c\n");


	init_data(c_golden, b_golden, n, m);

	printf("Executing mxv function for n = %d m = %d\n",n,m);

	software_start = getTimestamp();
	for ( i = 0; i < 1; i++) {
		for ( j = 0; j < 1; j++) {
			(void) mxv_golden(n, m, a_golden, b_golden, c_golden);
		}
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

	int frequency_factor_min = 5;
	int vccint_min = 0.67;


	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);
	VOLTAGE_SCALING_PROLOGUE(vccint_min, 1.0, 0.01);
	FREQUENCY_SCALING_PROLOGUE(frequency_factor_min, 50, 1);

	refresh_hardware(&accel_status);

	if ( (a_hw=(DATA_TYPE *)fpgacl_malloc(n*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (b_hw=(DATA_TYPE *)fpgacl_malloc(m*n*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for b");
	if ( (c_hw=(DATA_TYPE *)fpgacl_malloc(m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for c");




	//--------------------validation check start------------------------------------------
	init_data(c_golden, b_golden, n, m);
	fpgacl_memwrite((void *)a_golden, (u32*)a_hw, sizeof(DATA_TYPE)*n);
	fpgacl_memwrite((void *)b_golden, (u32*)b_hw, sizeof(DATA_TYPE)*n*m);
	fpgacl_memwrite((void *)c_golden, (u32*)c_hw, sizeof(DATA_TYPE)*m);

	hardware_start = getTimestamp();

	mxv_hw(n, m, a_hw, b_hw, c_hw);

	hardware_end = getTimestamp();
	hardware_execution_time = (hardware_end-hardware_start)/(1000);
	printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);


	mxv_golden(n, m, a_golden, b_golden, c_golden);


	fpgacl_memread((void*)a_hw_result, (u32 *)a_hw, sizeof(float)*n);

	status = validate(n, m, a_golden, a_hw_result);
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
			(void) mxv_hw(n, m, a_hw, b_hw, c_hw);
		}

		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 2000/hardware_execution_time;
		//============================================================================
		fp_v=fopen(log_file_name, "a");
		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			(void) mxv_hw(n, m, a_hw, b_hw, c_hw);
		}
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");

		if (MANUAL_POWER_MONITOR_ITERATION != 1) {
			printf("loop for manual power monitoring!\n");
			for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
				for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
					(void) mxv_hw(n, m, a_hw, b_hw, c_hw);
				}
			}
		}
		fclose(fp_v);

	}

	fpgacl_free((u32)a_hw);
	fpgacl_free((u32)b_hw);
	fpgacl_free((u32)c_hw);

	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();



	free(a_golden);
	free(b_golden);
	free(c_golden);
	free(a_hw_result);



	return(status);
}

void mxv_golden(int n, int m, DATA_TYPE *  a, DATA_TYPE *  b,
		DATA_TYPE *  c)
{
   int i, j;

   for (i=0; i<n; i++)
   {
      a[i] = 0.0;
      for (j=0; j<m; j++)
         a[i] += b[i*m+j]*c[j];
   }
}



void mxv_hw(int n, int m, DATA_TYPE *  a,
		DATA_TYPE *  b, DATA_TYPE *  c) {


	accel_write(n, m, a, b, c);
	accel_start();
	sleep(1);  //interrupt

//	accel_wait(); //polling
//	printf("mxv_hw: end\n");


}

int validate(int n, int m,
		     DATA_TYPE *a_golden,
		     DATA_TYPE *a_hw) {
	int i, j, k = 0, p = 0;
	for(i = 0; i < n; i++) {
		DATA_TYPE hw = a_hw[i];
		DATA_TYPE sw = a_golden[i];
		DATA_TYPE diff = hw - sw;
		if(fabs(diff) > 0.01){
			printf("Error in out_data at A_hw[%d] = %f != A_sw[%d] = %f\n", i, hw, i, sw);
			return -1;
		}
	}
	return 0;
}



void init_data(float* c_golden, float* b_golden, int n, int m) {

	int i, j;
	for (j=0; j<m; j++) {
		c_golden[j] = rand()/(1.0*RAND_MAX);
	}
	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			b_golden[i*m+j] = rand()/(1.0*RAND_MAX);
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

		sprintf(cmd, "cat  mxv-stream-4X.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat   mxv-stream-4X.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}





}
