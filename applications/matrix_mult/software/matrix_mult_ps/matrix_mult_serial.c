#include "matrix_mult.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

double getTimestamp();

double benchmarker_1_start;
double benchmarker_1_end;
double benchmarker_1_execution_time;

double benchmarker_2_start;
double benchmarker_2_end;
double benchmarker_2_execution_time;



/* N should be power of 2, and larger than 8 */


DATA_TYPE a[N][M],b[M][P],result1[N][P],result2[N][P];

unsigned initializor_dummy(DATA_TYPE* uiParam0, DATA_TYPE* uiParam1, DATA_TYPE* uiParam2, DATA_TYPE* uiParam3 )
{
	DATA_TYPE *p = (DATA_TYPE *)uiParam0;
	int i,j;

	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
            *(p+i*N+j) = 0;

	return 1;
}

unsigned validator_dummy(DATA_TYPE uiParam0, DATA_TYPE uiParam1, DATA_TYPE uiParam2, DATA_TYPE uiParam3 )
{
	return 1;
}


unsigned benchmarker_1(DATA_TYPE uiParam0, DATA_TYPE uiParam1, DATA_TYPE uiParam2, DATA_TYPE uiParam3 )
{
	int i,j,k;

	for(i=0;i<N;i++)
		for(j=0;j<P;j++)
			for(k=0;k<M;k++)
		        result1[i][j] += a[i][k]*b[k][j];

	return 1;
}

#define BLOCK 8
unsigned benchmarker_2(DATA_TYPE uiParam0, DATA_TYPE uiParam1, DATA_TYPE uiParam2, DATA_TYPE uiParam3 )
{
	int io,jo,ko,ii,ki,ji;
	DATA_TYPE *rresult, *rb, *ra;

	for (io = 0; io < N; io += BLOCK)
	    for (jo = 0; jo < P; jo += BLOCK)
	        for (ko = 0; ko < M; ko += BLOCK)
	            for (ii = 0, rresult = &result2[io][jo], ra = &a[io][ko]; ii < BLOCK; ii++, rresult += P, ra += M)
	                for (ki = 0, rb = &b[ko][jo];	ki < BLOCK; ki++, rb += P)
	                    for (ji = 0; ji < BLOCK; ji++)
	                        rresult[ji] += ra[ki] * rb[ji];

	return 1;
}


int main()
{
	unsigned int i,j;
	int iRetCode;


	printf("----Benchmarking starting----\r\n");

	printf("Matrix size= %d * %d\r\n", N, N);

	// We need to validate the algorithm's correctness
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
		{
		    a[i][j]=i*1+j*2;
		}


	for(i=0;i<M;i++)
		for(j=0;j<P;j++)
		{
		    b[i][j]=i*2+j*3;
		}


	for(i=0;i<N;i++)
		for(j=0;j<P;j++)
		{
		    result1[i][j]=0;
		    result2[i][j]=0;
		}

	benchmarker_1_start = getTimestamp();
	benchmarker_1(0,0,0,0);
	benchmarker_1_end = getTimestamp();
	benchmarker_1_execution_time = (benchmarker_1_end-benchmarker_1_start)/(1000);
	printf("benchmarker_1 execution time  %.6lf ms elapsed\n", benchmarker_1_execution_time);


	benchmarker_2_start = getTimestamp();
	benchmarker_2(0,0,0,0);
	benchmarker_2_end = getTimestamp();
	benchmarker_2_execution_time = (benchmarker_2_end-benchmarker_2_start)/(1000);
	printf("benchmarker_1 execution time  %.6lf ms elapsed\n", benchmarker_2_execution_time);


	if(DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("huge number of iteration for manual monitoring\n");
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				benchmarker_2(0,0,0,0);
			}
		}
	}



	iRetCode=memcmp(result1, result2, N*P*sizeof(DATA_TYPE) );
	if(iRetCode==0)
	{
	    printf("Algorithm validation success!\r\n" );
	}
	else
	{
	    printf("Algorithm validation failed! Exit application.\r\n" );
	    return -1;
	}




    printf("----Benchmarking Complete----\r\n");

	return 0;
}

double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}
