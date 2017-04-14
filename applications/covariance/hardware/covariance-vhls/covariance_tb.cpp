/**
 * This version is stamped on Apr. 14, 2015
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
/* covariance.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include "polybench.h"

/* Include benchmark-specific header. */
#include "covariance.h"



/* Array initialization. */
static
void init_array (int m, int n,
		 DATA_TYPE *float_n,
		 DATA_TYPE POLYBENCH_2D(data_sw,N,M,n,m),
		 DATA_TYPE POLYBENCH_2D(data_hw,N,M,n,m))
{
  int i, j;

  *float_n = (DATA_TYPE)n;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++) {
    	DATA_TYPE tmp = ((DATA_TYPE) i*j+i+j) / M + rand()/(RAND_MAX*1.0);//rand()/(RAND_MAX*1.0);//((DATA_TYPE) i*j+i+j) / M;
    	data_sw[i][j] = tmp;
    	data_hw[i][j] = tmp;
    }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int m,
		 DATA_TYPE POLYBENCH_2D(cov,M,M,m,m))

{
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("cov");
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      if ((i * m + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
      fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, cov[i][j]);
    }
  POLYBENCH_DUMP_END("cov");
  POLYBENCH_DUMP_FINISH;
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void sw_kernel_covariance(int m, int n,
		       DATA_TYPE float_n,
		       DATA_TYPE POLYBENCH_2D(data,N,M,n,m),
		       DATA_TYPE POLYBENCH_2D(cov,M,M,m,m),
		       DATA_TYPE POLYBENCH_1D(mean,M,m))
{
  int i, j, k;

#pragma scop
  for (j = 0; j < _PB_M; j++)
    {
      mean[j] = SCALAR_VAL(0.0);
      for (i = 0; i < _PB_N; i++)
        mean[j] += data[i][j];
      mean[j] /= float_n;
    }

//	for (int i = 0; i < 10; i++)
//		printf("mean[%d=%f\n ", i, mean);
  for (i = 0; i < _PB_N; i++)
    for (j = 0; j < _PB_M; j++)
      data[i][j] -= mean[j];

  for (i = 0; i < _PB_M; i++)
    for (j = i; j < _PB_M; j++)
      {
        cov[i][j] = SCALAR_VAL(0.0);
        for (k = 0; k < _PB_N; k++)
        	cov[i][j] += data[k][i] * data[k][j];
        cov[i][j] /= (float_n - SCALAR_VAL(1.0));
        cov[j][i] = cov[i][j];
      }
#pragma endscop

}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void hw_kernel_covariance(int m, int n,
		       DATA_TYPE float_n,
		       DATA_TYPE POLYBENCH_2D(data,N,M,n,m),
		       DATA_TYPE POLYBENCH_2D(cov,M,M,m,m),
		       DATA_TYPE POLYBENCH_1D(mean,M,m))
{
  int i, j, k;

  DATA_TYPE* memory = 0;
  u32 data_offset = (u32)data/4;
  u32 cov_offset  = (u32)cov/4;

  covariance(memory, data_offset,  cov_offset,  N, M);

  for (i = 0; i < _PB_M; i++)
    for (j = i; j < _PB_M; j++)
    	cov[j][i] = cov[i][j];
}

int validate(DATA_TYPE POLYBENCH_2D(hw_cov,M,M,m,m),
		     DATA_TYPE POLYBENCH_2D(sw_cov,M,M,m,m)) {
	int i, j, k=0;
	for(i = 0; i < M; i++)
		for(j = 0; j < M; j++) {
			DATA_TYPE hw = hw_cov[i][j];
			DATA_TYPE sw = sw_cov[i][j];
			DATA_TYPE diff = hw - sw;
			if(fabs(diff) > 0.01){
				printf("Error in out_data at hw_cov[%d][%d] = %f != sw_cov[%d][%d] = %f\n", i, j, hw, i, j, sw);
				if (k++>10)
					return -1;
			}
		}
	printf("Output PASSED at cov_sw[%d][%d]=%f == cov_hw[%d][%d]=%f\n", 0, 0, sw_cov[0][0], 0, 0, hw_cov[0][0]);
	printf("Output PASSED at cov_sw[%d][%d]=%f == cov_hw[%d][%d]=%f\n", 1, 3, sw_cov[1][3], 1, 3, hw_cov[1][3]);

	return 0;

}

int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int n = N;
  int m = M;

  /* Variable declaration/allocation. */
  DATA_TYPE float_n;
  POLYBENCH_2D_ARRAY_DECL(sw_data,DATA_TYPE,N,M,n,m);
  POLYBENCH_2D_ARRAY_DECL(sw_cov,DATA_TYPE,M,M,m,m);
  POLYBENCH_1D_ARRAY_DECL(sw_mean,DATA_TYPE,M,m);


  POLYBENCH_2D_ARRAY_DECL(hw_data,DATA_TYPE,N,M,n,m);
  POLYBENCH_2D_ARRAY_DECL(hw_cov,DATA_TYPE,M,M,m,m);
  POLYBENCH_1D_ARRAY_DECL(hw_mean,DATA_TYPE,M,m);


  /* Initialize array(s). */
  init_array (m, n, &float_n, POLYBENCH_ARRAY(sw_data), POLYBENCH_ARRAY(hw_data));





  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
 sw_kernel_covariance (m, n, float_n,
		     POLYBENCH_ARRAY(sw_data),
		     POLYBENCH_ARRAY(sw_cov),
		     POLYBENCH_ARRAY(sw_mean));

  hw_kernel_covariance (m, n, float_n,
  		     POLYBENCH_ARRAY(hw_data),
  		     POLYBENCH_ARRAY(hw_cov),
  		     POLYBENCH_ARRAY(hw_mean));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;



  //validate
  int status = validate(POLYBENCH_ARRAY(hw_cov),POLYBENCH_ARRAY(sw_cov));
  if (status == 0) {

	  printf("Validation PASSED!\n");
  } else {
	  printf("Validation FAILED!\n");

  }

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(m, POLYBENCH_ARRAY(sw_cov)));
  polybench_prevent_dce(print_array(m, POLYBENCH_ARRAY(hw_cov)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(sw_data);
  POLYBENCH_FREE_ARRAY(sw_cov);
  POLYBENCH_FREE_ARRAY(sw_mean);

  POLYBENCH_FREE_ARRAY(hw_cov);
  POLYBENCH_FREE_ARRAY(hw_data);
  POLYBENCH_FREE_ARRAY(hw_mean);

  return status;
}
