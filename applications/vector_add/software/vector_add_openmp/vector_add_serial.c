#include <stdlib.h>  // rand(), srand()
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "vector_add.h"



double getTimestamp();
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



void kernel_sw(float* a, float* b, float* c) {

	int i;
#pragma scop
	for (i = 0; i < DATA_LENGTH; i++) {
		c[i] = a[i]+b[i];
	}
#pragma endscop
}


double software_part_start;
double software_part_end;
double hardware_part_start;
double hardware_part_end;

int first_iteration;
double software_part_time = 0;
double hardware_part_time = 0;


int validate(float* c_sw, float* c_hw ) {
	int i;

	for (i = 0; i < DATA_LENGTH; i++) {
		float hw = c_hw[i];
		float sw = c_sw[i];

		float diff = fabs(hw - sw);
		if(diff > 0.001 || diff != diff){
			printf("Error in out_data at c_hw[%d] = %f != c_sw[%d] = %f\n", i, hw, i,  sw);
			return -1;
		}
	}
	return 0;
}


int main(int argc, char** argv)
{


	int status;

	double time_scale_hardware = 1.0;

	double software_start;
   	double software_end;
   	double software_execution_time;


   	printf("main: check point 1\n");


   	/* Variable declaration/allocation. */


	//time_scale_hardware = 1 / 30.0;

	float* a_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);
	float* b_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);
	float* c_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);


	init_array(a_sw, b_sw);



	software_start = getTimestamp();
	for (int i = 0; i < SOFTWARE_ITERATION; i++) {
		kernel_sw(a_sw, b_sw, c_sw);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
	printf("serial execution time  %.6lf ms elapsed\n", software_execution_time);


	//==================================================================


	if (DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("huge nubmer of iterations for manual power measurement\n");
		software_start = getTimestamp();
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				kernel_sw(a_sw, b_sw, c_sw);
			}
		}
		software_end = getTimestamp();
		software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
		printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

	}


	for (int i = 0; i < DATA_LENGTH; i++) {
		printf ("c[%d] = %f\n", i, c_sw[i]);
	}

	// Be clean.
	free(a_sw);
	free(b_sw);
	free(c_sw);


	return 0;
}

double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}
