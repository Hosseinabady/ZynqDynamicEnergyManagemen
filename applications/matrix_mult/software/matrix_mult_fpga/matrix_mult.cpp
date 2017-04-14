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
void init_data(int n, int m, int p, DATA_TYPE* c_golden, DATA_TYPE* b_golden);




#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM  10



void matrix_mult_golden(int n, int m, int p, DATA_TYPE *  a,
		DATA_TYPE *  b, DATA_TYPE *  c);

void matrix_mult_hw(int n, int m, int p, DATA_TYPE *  a,
		DATA_TYPE *  b, DATA_TYPE *  c);

int validate(int n, int m, int p,
		     DATA_TYPE *a_golden,
		     DATA_TYPE *a_hw);
int main(int argc, char *argv[])
{

	int accel_status = 0;
	DATA_TYPE *a_golden,*b_golden,*c_golden;
	DATA_TYPE *a_hw,*b_hw,*c_hw, *c_hw_result;
	int status;
	int i, j, m, n, p;
	FILE* fp_v;
	char cmd[100];

	n=N;
	m=M;
	p=P;
	printf("\n");

	if ( (a_golden=(DATA_TYPE *)malloc(n*m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (b_golden=(DATA_TYPE *)malloc(m*p*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for b");
	if ( (c_golden=(DATA_TYPE *)malloc(n*p*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for c");




	if ( (c_hw_result=(DATA_TYPE *)malloc(n*p*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");




	printf("Initializing matrix b and vector c\n");


	init_data(n, m, p, a_golden, b_golden);

	printf("Executing matrix_mult function for n = %d m = %d p = %d\n",n,m, p);

	software_start = getTimestamp();
	for ( i = 0; i < 1; i++) {
		for ( j = 0; j < 1; j++) {
			(void) matrix_mult_golden(n, m, p, a_golden, b_golden, c_golden);
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


	if ( (a_hw=(DATA_TYPE *)fpgacl_malloc(n*m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (b_hw=(DATA_TYPE *)fpgacl_malloc(m*p*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for b");
	if ( (c_hw=(DATA_TYPE *)fpgacl_malloc(n*p*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for c");




	//--------------------validation check start------------------------------------------
	init_data(n, m, p, a_golden, b_golden);
	fpgacl_memwrite((void *)a_golden, (u32*)a_hw, sizeof(DATA_TYPE)*n*m);
	fpgacl_memwrite((void *)b_golden, (u32*)b_hw, sizeof(DATA_TYPE)*m*p);
	fpgacl_memwrite((void *)c_golden, (u32*)c_hw, sizeof(DATA_TYPE)*n*p);

	matrix_mult_hw(n, m, p, a_hw, b_hw, c_hw);
	matrix_mult_golden(n, m, p, a_golden, b_golden, c_golden);

	fpgacl_memread((void*)c_hw_result, (u32 *)c_hw, sizeof(DATA_TYPE)*n*p);

	status = validate(n, m, p, c_golden, c_hw_result);
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
			(void) matrix_mult_hw(n, m, p, a_hw, b_hw, c_hw);
		}

		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 4000/hardware_execution_time;
		//============================================================================
		fp_v=fopen(log_file_name, "a");
		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			(void) matrix_mult_hw(n, m, p, a_hw, b_hw, c_hw);
		}
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");

		if (MANUAL_POWER_MONITOR_ITERATION != 1) {
			printf("loop for manual power monitoring!\n");
			for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
				for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
					(void) matrix_mult_hw(n, m, p, a_hw, b_hw, c_hw);
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
	free(c_hw_result);



	return(status);
}

void matrix_mult_golden(int n, int m, int p, DATA_TYPE *  a, DATA_TYPE *  b, DATA_TYPE *  c)
{
	   int i, j, k;

		for(i=0;i<N;i++) {
			for(j=0;j<P;j++) {
				c[i*p+j] = 0.0;
				for(k=0;k<M;k++) {
					c[i*p+j] += a[i*m+k]*b[k*p+j];
				}
			}
		}
}



void matrix_mult_hw(int n, int m, int p, DATA_TYPE *  a, DATA_TYPE *  b, DATA_TYPE *  c) {


	accel_write(n, m, p, a, b, c);
//	printf("matrix_mult_hw: started\n");

	accel_start();
	sleep(1);  //interrupt

//	accel_wait(); //polling
//	printf("matrix_mult_hw: end\n");


}

int validate(int n, int m, int p,
		     DATA_TYPE *a_golden,
		     DATA_TYPE *a_hw) {
	int i, j, k = 0;
	for(i = 0; i < n*p; i++) {
		DATA_TYPE hw = a_hw[i];
		DATA_TYPE sw = a_golden[i];
		DATA_TYPE diff = hw - sw;
		if(diff != 0){
			printf("Error in out_data at A_hw[%d] = %d != A_sw[%d] = %d\n", i, hw, i, sw);
			return -1;
		}
//		if (k++ < 10)
//			printf("Error in out_data at A_hw[%d] = %d != A_sw[%d] = %d\n", i, hw, i, sw);
	}
	return 0;
}



void init_data(int n, int m, int p, DATA_TYPE* a_golden, DATA_TYPE* b_golden) {
	srand(time(NULL));
	int i, j;

	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			a_golden[i*m+j] = rand();
		}
	}

	for (i=0; i<m; i++) {
		for (j=0; j<p; j++) {
			b_golden[i*p+j] = rand();
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
	printf("refresh_hardware: check point 1\n");
	char cmd[100];


	sprintf(cmd, "chmod u+x initial.sh");
	run_command(cmd);


	sprintf(cmd, "chmod u+x clean.sh");
	run_command(cmd);



	if (*accel_status == 0) {



		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		accel_prologue();

		sprintf(cmd, "cat matrix_mult_512x512x256.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {



		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat  matrix_mult_512x512x256.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}






}
