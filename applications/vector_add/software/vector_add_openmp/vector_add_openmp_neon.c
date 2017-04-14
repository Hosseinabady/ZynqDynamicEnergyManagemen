
# include <omp.h>
#include <stdlib.h>  // rand(), srand()
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "vector_add.h"
#include <arm_neon.h>



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

# pragma omp parallel
# pragma omp for
	for (i = 0; i < DATA_LENGTH; i++) {
//		c[i] = a[i]+b[i];
		float f = a[i];
		float g = b[i];
		float h;
		int ret;
		asm volatile (
		        "add %[h], %[f], %[g]"
		        // outputs
		        : [h]"=r"(h)
		        // inputs
		        : [f]"r"(f), [g]"r"(g)
		    );
		 c[i] = h;
	}
}

double software_part_start;
double software_part_end;
double hardware_part_start;
double hardware_part_end;

int first_iteration;
double software_part_time = 0;
double hardware_part_time = 0;





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

   	float * a_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);
   	float * b_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);
   	float * c_sw = (float *)malloc(sizeof(float)*DATA_LENGTH);



	init_array(a_sw, b_sw);


	software_start = getTimestamp();
	for (int i = 0; i < SOFTWARE_ITERATION; i++) {
		kernel_sw(a_sw, b_sw, c_sw);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
	printf("parallel openmp+neon execution time  %.6lf ms elapsed\n", software_execution_time);

	for (int i = 0; i <DATA_LENGTH; i++) {
		if (c_sw[i] != a_sw[i]+b_sw[i]) {
			printf("validation failed\n c_sw[%d] = %f != a_sw[%d]+b_sw[%d]=%f\n", i, c_sw[i], i, i, a_sw[i]+b_sw[i]);
			break;
		}
	}

	if (DELAY_FOR_POWER_MEASUREMENT!=1) {
		printf("huge nubmer of iterations for manual power measurement\n");
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				kernel_sw(a_sw, b_sw, c_sw);
			}
		}
	}

	//==================================================================


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
