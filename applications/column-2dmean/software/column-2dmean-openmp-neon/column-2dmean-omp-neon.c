#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "column-2dmean.h"
#include <sys/time.h>
#include <time.h>



double software_start;
double software_end;
double software_execution_time;




double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}

#define MANUAL_POWER_MONITOR_ITERATION 1


void init_data(DATA_TYPE *data, int n, int m);

void column_2dmean_golden(DATA_TYPE *  data, DATA_TYPE *  mean_sw, DATA_TYPE  float_n, int n, int m);


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


	DATA_TYPE float_n = 1.0*n;

	init_data(data_sw, n, m);

	software_start = getTimestamp();
	column_2dmean_golden(data_sw, mean_sw, float_n, n, m);
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);


	software_start = getTimestamp();
	if(DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("huge number of iteration for manual monitoring\n");
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				column_2dmean_golden(data_sw, mean_sw, float_n, n, m);
			}
		}
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

	free(data_sw);
	free(mean_sw);



}

void column_2dmean_golden(DATA_TYPE *  data, DATA_TYPE *  mean_sw, DATA_TYPE  float_n, int n, int m)
{
	int i, j;
# pragma omp parallel
# pragma omp for
	for ( j = 0; j < m; j++)  {
		mean_sw[j] = 0.0;
	}

#pragma omp parallel for default(none) \
        shared(m,n, data, mean_sw, float_n) private(i,j)
	for ( i = 0; i < n; i++) {
		for ( j = 0; j < m; j++)  {
	    	DATA_TYPE d_1 = data[(i)*m+j];
	    	mean_sw[j] += d_1;

		}
	}
# pragma omp parallel
# pragma omp for
	for ( j = 0; j < m; j++)  {
		mean_sw[j] /= float_n;
	}
}




void init_data(DATA_TYPE *data, int n, int m) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			data[i*m+j] = (i+j)*(rand()/(RAND_MAX*1.0));
		}
	}
}

