#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "histogram.h"
#include <sys/time.h>
#include <time.h>

double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}




double software_start;
double software_end;
double software_execution_time;


void init_data(DATA_TYPE* data, u32 *histogram, u32 n);



#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM  10
#define SOFTWARE_ITERATION                 10


void histogram_sw(DATA_TYPE *  data,
		u32 *  histogram);

int main(int argc, char *argv[])
{


	DATA_TYPE *data_golden;
	u32       *histogram_golden;
	DATA_TYPE *data_hw;
	u32 *histogram_hw,*histogram_hw_result;

	int status;




	if ( (data_golden=(DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (histogram_golden=(u32 *)malloc(BIN_LENGTH*sizeof(u32))) == NULL )
		perror("memory allocation for b");


	if ( (histogram_hw_result=(u32 *)malloc(BIN_LENGTH*sizeof(u32))) == NULL )
		perror("memory allocation for a");


	printf("accel_prologue ceck point 1\n");



	init_data(data_golden, histogram_golden, DATA_LENGTH);



	software_start = getTimestamp();
	for (int i = 0; i < SOFTWARE_ITERATION; i++) {
		histogram_sw(data_golden, histogram_golden);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);




	   software_start = getTimestamp();
	    if(DELAY_FOR_POWER_MEASUREMENT != 1) {
	 	   printf("enter in huge iterations for manual power measurement\n");
	 	   for (int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
	 		   for (int k = 0; k < DELAY_FOR_POWER_MEASUREMENT; k++) {
	 			  histogram_sw(data_golden, histogram_golden);
	 		   }
	 	   }
	    }
	    software_end = getTimestamp();
	    software_execution_time = (software_end-software_start)/(DELAY_FOR_POWER_MEASUREMENT*1000);
	    printf("software execution time  %.6lf ms elapsed\n", software_execution_time);


	free(data_golden);
	free(histogram_golden);

	return(status);
}

void histogram_sw(DATA_TYPE *  data, u32 *  histogram)
{

	int n = DATA_LENGTH;
	u32 index, i;
#pragma omp parallel for default(none) \
        shared(n, data, histogram) private(i,index)
	for (i = 0; i < n; i++) {
		index =  (u32)data[i];
//		if (index > 255) {
//			printf("Error in input data at data[%d]=%f is greater than 255\n", i,data[i]);
//			return;
//		}
		histogram[index]++;
	}
}




void init_data(DATA_TYPE* data, u32 *histogram, u32 n){

	srand((unsigned) time(NULL));
	  int i, j;

	  for (i = 0; i < DATA_LENGTH; i++) {
		  data[i] = (u32)((float)rand()/(float)(RAND_MAX)) * 255;
	  }
	  for (int i = 0; i < BIN_LENGTH; i++) {
		  histogram[i] = 0;
	  }

}
