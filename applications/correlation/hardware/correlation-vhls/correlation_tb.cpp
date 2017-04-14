/**
 * This version is stamped on Apr. 14, 2015
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */


/**
 * This version is modified for Xilinx Vivado-HLS on Dec. 15, 2015
 *
 * Contact:
 *   Mohammad Hosseinabady <m.hosseinabady@bristol.ac.uk>
 *   mohammad@hosseinabady.com
 *
 *
 */
/* correlation.c: this file is part of PolyBench/C */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include "polybench.h"

/* Include benchmark-specific header. */
#include "correlation.h"


/* Array initialization. */
static
void init_array (int m,
		 int n,
		 DATA_TYPE *float_n,
		 DATA_TYPE POLYBENCH_2D(data_sw,N,M,n,m),
		 DATA_TYPE POLYBENCH_2D(data_hw,N,M,n,m))
{
  int i, j;

  *float_n = (DATA_TYPE)N;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++) {
    	DATA_TYPE tmp = (DATA_TYPE)(i*j)/M +rand()/(1.0*RAND_MAX)+ i;
    	data_sw[i][j] = tmp;
    	data_hw[i][j] = tmp;
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


static
void hardware_kernel_correlation(int m, int n,
			DATA_TYPE float_n,
			DATA_TYPE POLYBENCH_2D(data,N,M,n,m),
			DATA_TYPE POLYBENCH_2D(corr,M,M,m,m),
			DATA_TYPE POLYBENCH_1D(mean,M,m),
			DATA_TYPE POLYBENCH_1D(stddev,M,m))
{
	  int i, j, k;
	  DATA_TYPE* memory = 0;
	  u32 data_offset  = (u32)data/4;
	  u32 corr_offset  = (u32)corr/4;


	  correlation(
			  	  memory,
				  memory,

				  data_offset,
				  corr_offset,
				  n,
				  m);
	  for (i = 0; i < _PB_M; i++)
	    for (j = i; j < _PB_M; j++)
	    	corr[j][i] = corr[i][j];

}

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void software_kernel_correlation(int m, int n,
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

int validate(DATA_TYPE POLYBENCH_2D(corrHW,M,M,m,m),
		     DATA_TYPE POLYBENCH_2D(corrSW,M,M,m,m)) {
	int i, j;
	for(i = 0; i < M; i++)
		for(j = 0; j < M; j++) {
			DATA_TYPE hw = corrHW[i][j];
			DATA_TYPE sw = corrSW[i][j];
			DATA_TYPE diff = hw - sw;
			if(fabs(diff) > 0.1){
				printf("Error in out_data at hw_cov[%d][%d] = %f != sw_cov[%d][%d] = %f\n", i, j, hw, i, j, sw);
				return -1;
			}
		}
	return 0;

}



int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int n = N;
  int m = M;

  /* Variable declaration/allocation. */
  DATA_TYPE float_n;
  POLYBENCH_2D_ARRAY_DECL(dataSW,DATA_TYPE,N,M,n,m);
  POLYBENCH_2D_ARRAY_DECL(dataHW,DATA_TYPE,N,M,n,m);
  POLYBENCH_2D_ARRAY_DECL(corrSW,DATA_TYPE,M,M,m,m);
  POLYBENCH_2D_ARRAY_DECL(corrHW,DATA_TYPE,M,M,m,m);
  POLYBENCH_1D_ARRAY_DECL(mean,DATA_TYPE,M,m);
  POLYBENCH_1D_ARRAY_DECL(stddev,DATA_TYPE,M,m);

  /* Initialize array(s). */
  init_array (m, n, &float_n, POLYBENCH_ARRAY(dataSW), POLYBENCH_ARRAY(dataHW));
  //init_array (m, n, &float_n, POLYBENCH_ARRAY(dataHW));

  /* Start timer. */
  polybench_start_instruments;

  /* Run software kernel. */
  software_kernel_correlation (m, n, float_n,
		      POLYBENCH_ARRAY(dataSW),
		      POLYBENCH_ARRAY(corrSW),
		      POLYBENCH_ARRAY(mean),
		      POLYBENCH_ARRAY(stddev));

   /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Run hardware kernel. */
  hardware_kernel_correlation (m, n, float_n,
    		      POLYBENCH_ARRAY(dataHW),
    		      POLYBENCH_ARRAY(corrHW),
    		      POLYBENCH_ARRAY(mean),
    		      POLYBENCH_ARRAY(stddev));


  //validate
  int status = validate(POLYBENCH_ARRAY(corrHW),POLYBENCH_ARRAY(corrSW));
  if (status == 0) {
	  printf("Validation PASSED!\n");
  } else {
	  printf("Validation FAILED!\n");
  }
  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(m, POLYBENCH_ARRAY(corrSW)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(dataSW);
  POLYBENCH_FREE_ARRAY(dataHW);
  POLYBENCH_FREE_ARRAY(corrSW);
  POLYBENCH_FREE_ARRAY(corrHW);
  POLYBENCH_FREE_ARRAY(mean);
  POLYBENCH_FREE_ARRAY(stddev);

  return status;
}
