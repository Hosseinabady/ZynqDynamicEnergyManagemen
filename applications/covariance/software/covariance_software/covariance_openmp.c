#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

/* Include polybench common header. */
#include "polybench.h"
#include <sys/time.h>
#include <time.h>
#include <covariance.h>



double software_start;
double software_end;
double software_execution_time;


double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}


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
void sw_kernel_covariance(int m, int n,
		       DATA_TYPE float_n,
		       DATA_TYPE POLYBENCH_2D(data,M,N,m,n),
		       DATA_TYPE POLYBENCH_2D(symmat,M,M,m,m),
		       DATA_TYPE POLYBENCH_1D(mean,M,m))
{
  int i, j, j1, j2;

  #pragma scop
  /* Determine mean of column vectors of input data matrix */
  #pragma omp parallel
  {
    #pragma omp for private (i)
    for (j = 0; j < _PB_M; j++)
      {
        mean[j] = 0.0;
	for (i = 0; i < _PB_N; i++)
	  mean[j] += data[i][j];
	mean[j] /= float_n;
      }

    /* Center the column vectors. */
    #pragma omp for private (j)
    for (i = 0; i < _PB_N; i++)
      for (j = 0; j < _PB_M; j++)
	data[i][j] -= mean[j];

    /* Calculate the m * m covariance matrix. */
    #pragma omp for private (j2, i)
    for (j1 = 0; j1 < _PB_M; j1++)
      for (j2 = j1; j2 < _PB_M; j2++)
	{
          symmat[j1][j2] = 0.0;
	  for (i = 0; i < _PB_N; i++)
	    symmat[j1][j2] += data[i][j1] * data[i][j2];
	  symmat[j2][j1] = symmat[j1][j2];
        }
  }
  #pragma endscop
}




int main(int argc, char** argv)
{

  /* Retrieve problem size. */
	int n = N;
	int m = M;

	  printf("n = %d, m=%d\n", n, m);

	FILE* fp_v;
	DATA_TYPE *hw_data;
	DATA_TYPE *hw_corr;
	DATA_TYPE *hw_corr_result;
  /* Variable declaration/allocation. */
	DATA_TYPE float_n;
	POLYBENCH_2D_ARRAY_DECL(sw_data,DATA_TYPE,N,M,n,m);
	POLYBENCH_2D_ARRAY_DECL(sw_cov,DATA_TYPE,M,M,m,m);
	POLYBENCH_1D_ARRAY_DECL(sw_mean,DATA_TYPE,M,m);


  /* Initialize array(s). */
	init_data (m, n, &float_n, POLYBENCH_ARRAY(sw_data));

  /* Start timer. */
	polybench_start_instruments;

  /* Run kernel. */
	printf("software execution started\n");
	software_start = getTimestamp();
	for (int i = 0; i < EXE_TIME_MONITORING_ITERATION_NUM; i++) {
		sw_kernel_covariance (m, n, float_n,
			     POLYBENCH_ARRAY(sw_data),
			     POLYBENCH_ARRAY(sw_cov),
			     POLYBENCH_ARRAY(sw_mean));
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

	if(DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("huge number of iteration for manual monitoring\n");
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				sw_kernel_covariance (m, n, float_n,
					     POLYBENCH_ARRAY(sw_data),
					     POLYBENCH_ARRAY(sw_cov),
					     POLYBENCH_ARRAY(sw_mean));
			}
		}
	}

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(sw_data);
  POLYBENCH_FREE_ARRAY(sw_cov);
  POLYBENCH_FREE_ARRAY(sw_mean);

  return 0;
}




