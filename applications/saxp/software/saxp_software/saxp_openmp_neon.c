# include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <saxp.h>


double software_start;
double software_end;
double software_execution_time;
double software_part_time = 0;



double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}


void init_array(float* a, float* b)
{
	time_t t;
	srand((unsigned) time(&t));

	int i;
	for (i = 0; i < DATA_LENGTH; i++) {
		a[i] = rand()/(float)RAND_MAX;//row
		b[i] = rand()/(float)RAND_MAX;//row
	}

}



void kernel_sw(float* a, float* b) {

	int i;
# pragma omp parallel
# pragma omp for
	for (i = 0; i < DATA_LENGTH; i++) {
		b[i] = 2.34*a[i] + 5.2355;
	}
}





#define SOFTWARE_ITERATION 10

int main(int argc, char** argv)
{




   	printf("main: check point 1\n");


   	/* Variable declaration/allocation. */


	//time_scale_hardware = 1 / 30.0;

	float* a_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);
	float* b_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);


	init_array(a_sw, b_sw);


	software_start = getTimestamp();
	for (int i = 0; i < SOFTWARE_ITERATION; i++) {
		kernel_sw(a_sw, b_sw);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);


	if(DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("huge number of iteration for manual monitoring\n");
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				kernel_sw(a_sw, b_sw);
			}
		}
	}

	free(a_sw);
	free(b_sw);

	return 0;
}

