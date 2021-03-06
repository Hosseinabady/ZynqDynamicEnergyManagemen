#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

/* Include polybench common header. */
#include "polybench.h"


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


#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM  10


/* Array initialization. */
static
void init_data (int m, int n,
		 DATA_TYPE *float_n,
		 DATA_TYPE POLYBENCH_2D(data_sw,N,M,n,m))
{
  int i, j;

  *float_n = (DATA_TYPE)n;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++) {
    	DATA_TYPE tmp = ((DATA_TYPE) i*j+i+j) / M + rand()/(RAND_MAX*1.0);//rand()/(RAND_MAX*1.0);//((DATA_TYPE) i*j+i+j) / M;
    	data_sw[i][j] = tmp;
    }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int m,
		 DATA_TYPE POLYBENCH_2D(corr,M,M,m,m))

{
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("corr");
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      if ((i * m + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
      fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, corr[i][j]);
    }
  POLYBENCH_DUMP_END("corr");
  POLYBENCH_DUMP_FINISH;
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */

static
void sw_kernel_correlation(int m, int n,
			DATA_TYPE float_n,
			DATA_TYPE POLYBENCH_2D(data,N,M,n,m),
			DATA_TYPE POLYBENCH_2D(corr,M,M,m,m),
			DATA_TYPE POLYBENCH_1D(mean,M,m),
			DATA_TYPE POLYBENCH_1D(stddev,M,m))
{
  int i, j, k;

  DATA_TYPE eps = SCALAR_VAL(0.1);


#pragma scop
  for (j = 0; j < _PB_M; j++)
    {
      mean[j] = SCALAR_VAL(0.0);
      for (i = 0; i < _PB_N; i++)
    	  mean[j] += data[i][j];
      mean[j] /= float_n;
    }


   for (j = 0; j < _PB_M; j++)
    {
      stddev[j] = SCALAR_VAL(0.0);
      for (i = 0; i < _PB_N; i++)
        stddev[j] += (data[i][j] - mean[j]) * (data[i][j] - mean[j]);
      stddev[j] /= float_n;
      stddev[j] = SQRT_FUN(stddev[j]);
      /* The following in an inelegant but usual way to handle
         near-zero std. dev. values, which below would cause a zero-
         divide. */
      stddev[j] = stddev[j] <= eps ? SCALAR_VAL(1.0) : stddev[j];
    }

  /* Center and reduce the column vectors. */
  for (i = 0; i < _PB_N; i++)
    for (j = 0; j < _PB_M; j++)
      {
        data[i][j] -= mean[j];
        data[i][j] /= SQRT_FUN(float_n) * stddev[j];
      }

  /* Calculate the m * m correlation matrix. */
  for (i = 0; i < _PB_M-1; i++)
    {
      corr[i][i] = SCALAR_VAL(1.0);
      for (j = i+1; j < _PB_M; j++)
        {
          corr[i][j] = SCALAR_VAL(0.0);
          for (k = 0; k < _PB_N; k++)
            corr[i][j] += (data[k][i] * data[k][j]);
          corr[j][i] = corr[i][j];
        }
    }
  corr[_PB_M-1][_PB_M-1] = SCALAR_VAL(1.0);
#pragma endscop

}






/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void hw_kernel_correlation(	int n,
							int m,
							DATA_TYPE* hw_data,
							DATA_TYPE* hw_cov)
{
  int i, j, k;

	accel_write(n, m, hw_data, hw_cov);
	accel_start();
	sleep(10);  //interrupt


//	accel_wait(); //polling
//	printf("mxv_hw: end\n");



}

int validate(int n, int m, DATA_TYPE POLYBENCH_2D(sw_cov,M,M,m,m), DATA_TYPE *hw_cov) {
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			DATA_TYPE hw = hw_cov[i*m+j];
			DATA_TYPE sw = sw_cov[i][j];
			DATA_TYPE diff = hw - sw;
			if(fabs(diff) > 0.01){
				printf("Error in out_data at hw_cov[%d][%d] = %f != sw_cov[%d][%d] = %f\n", i, j, hw, i, j, sw);
				return -1;
			}
		}


	return 0;

}

int main(int argc, char** argv)
{
	int status;
	int accel_status = 0;
  /* Retrieve problem size. */
	int n = N;
	int m = M;
	FILE* fp_v;
	DATA_TYPE *hw_data;
	DATA_TYPE *hw_corr;
	DATA_TYPE *hw_corr_result;
  /* Variable declaration/allocation. */
	DATA_TYPE float_n;
	POLYBENCH_2D_ARRAY_DECL(sw_data,DATA_TYPE,N,M,n,m);
	POLYBENCH_2D_ARRAY_DECL(sw_corr,DATA_TYPE,M,M,m,m);
	POLYBENCH_1D_ARRAY_DECL(sw_mean,DATA_TYPE,M,m);
	POLYBENCH_1D_ARRAY_DECL(sw_stddev,DATA_TYPE,M,m);

	hw_corr_result = (DATA_TYPE*)malloc(m*m*sizeof(DATA_TYPE));

  /* Initialize array(s). */
	init_data (m, n, &float_n, POLYBENCH_ARRAY(sw_data));


  /* Start timer. */
	polybench_start_instruments;

  /* Run kernel. */
	printf("software execution started\n");
	software_start = getTimestamp();
	sw_kernel_correlation (m, n, float_n,
		     POLYBENCH_ARRAY(sw_data),
		     POLYBENCH_ARRAY(sw_corr),
		     POLYBENCH_ARRAY(sw_mean),
			 POLYBENCH_ARRAY(sw_stddev));

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
	sw_kernel_correlation (m, n, float_n,
		     POLYBENCH_ARRAY(sw_data),
		     POLYBENCH_ARRAY(sw_corr),
		     POLYBENCH_ARRAY(sw_mean),
			 POLYBENCH_ARRAY(sw_stddev));



	if ( (hw_data=(DATA_TYPE *)fpgacl_malloc(n*m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (hw_corr=(DATA_TYPE *)fpgacl_malloc(m*m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for b");

	//--------------------validation check start------------------------------------------
	init_data(m, n, &float_n, POLYBENCH_ARRAY(sw_data));
	fpgacl_memwrite((void *)sw_data, (u32*)hw_data, sizeof(DATA_TYPE)*n*m);

	sw_kernel_correlation (m, n, float_n,
			     POLYBENCH_ARRAY(sw_data),
			     POLYBENCH_ARRAY(sw_corr),
			     POLYBENCH_ARRAY(sw_mean),
				 POLYBENCH_ARRAY(sw_stddev));
	hw_kernel_correlation (n, m, hw_data, hw_corr);

	fpgacl_memread((void*)hw_corr_result, (u32 *)hw_corr, sizeof(DATA_TYPE)*m*m);

	hardware_start = getTimestamp();
	for (int i = 0; i < M; i++)
	    for (int j = i; j < M; j++)
	    	hw_corr_result[j*M+i] = hw_corr_result[i*M+j];

	status = validate(m, m, POLYBENCH_ARRAY(sw_corr), hw_corr_result);
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
			hw_kernel_correlation (n, m, hw_data, hw_corr);
		}
		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 2000/hardware_execution_time;

		fp_v=fopen(log_file_name, "a");
		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			hw_kernel_correlation (n, m, hw_data, hw_corr);
		}
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");

		fclose(fp_v);
	}




	fpgacl_free((u32)hw_data);
	fpgacl_free((u32)hw_corr);


	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;




  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(m, POLYBENCH_ARRAY(sw_corr)));


  /* Be clean. */
  POLYBENCH_FREE_ARRAY(sw_data);
  POLYBENCH_FREE_ARRAY(sw_corr);
  POLYBENCH_FREE_ARRAY(sw_mean);

  free(hw_corr_result);

  return status;
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

		sprintf(cmd, "cat  correlation.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat   correlation.bin > /dev/xdevcfg");

		run_command(cmd);

		accel_prologue();
	}





}
