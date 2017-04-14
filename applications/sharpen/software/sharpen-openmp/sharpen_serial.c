#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <sched.h>        // for sched_xxx() function calls
#include <sys/types.h>    // for pid_t
#include <sys/resource.h> // for getpriority()
#include <time.h>
#include "bmpfuncs.h"
#include "sharpen.h"



extern char log_file_name[1000];

const float mask[MASK_WIDTH*MASK_HEIGHT] = {   0, -1,  0,
		                                      -1,  5, -1,
											   0, -1,  0
                                           };


double getTimestamp();
#define DELAY() 		{ volatile long long int delay_var = 0; \
for (int delay_index = 0; delay_index < 10000; delay_index++) { \
	delay_var+=2; \
} }
/* image initialization. */
void init_array(float* image, int imageWidth, int imageHeight, const char* inputFileName)
{
/*	time_t t;
	srand((unsigned) time(&t));
	readImage(inputFileName, &imageWidth, &imageHeight, image);*/
	int row, col;
	for (row = 0; row < IMAGE_HEIGHT; row++)
		for (col = 0; col < IMAGE_WIDTH; col++) {
			image[row * IMAGE_WIDTH + col] = rand()/(float)RAND_MAX;//row+col;
		}

}

void print_output(float*  image, int width, int hight) {
	int row, col;

	for (row = 0; row < hight; row++) {
		for (col = 0; col < width; col++) {
			printf("%f, ", image[row * width + col]);
		}
		printf("\n");
	}
}



void kernel_sw_serial(float* inputImage, float* outImage) {

	int row, col, r, c;
#pragma omp parallel for num_threads(2)
	for (row = 0; row < IMAGE_HEIGHT; row++) {
		for (col = 0; col < IMAGE_WIDTH; col++) {
			float sum = 0;
	        for (r = 0; r < MASK_HEIGHT; r++)
	        	for (c = 0; c < MASK_WIDTH; c++) {
	        		int rIn = row + r - (MASK_HEIGHT/2);
	        		int cIn = col + c - (MASK_WIDTH/2);

	        		if(rIn < 0) rIn = 0 ;
	        		if(rIn > IMAGE_HEIGHT - 1) rIn = IMAGE_HEIGHT - 1;

	        		if(cIn < 0) cIn = 0 ;
	        		if(cIn > IMAGE_WIDTH - 1)  cIn = IMAGE_WIDTH  - 1;

	        		sum += mask[r * MASK_WIDTH + c] * inputImage[rIn * IMAGE_WIDTH + cIn];
	        	}
	        	outImage[row * IMAGE_WIDTH + col] = sum;
			}
		}
}


double software_part_start;
double software_part_end;

int first_iteration;
double software_part_time = 0;



#define SOFTWARE_ITERATION 1

int main(int argc, char** argv)
{


	int status;

	double software_start;
   	double software_end;
   	double software_execution_time;


   	printf("main: check point 1\n");


   	/* Variable declaration/allocation. */

	int imageWidth = IMAGE_WIDTH;
	int imageHeight = IMAGE_HEIGHT;
	const char *inputFileName  = INPUT_FILE_NAME;
	const char *outputFileName_sw = OUTPUT_FILE_NAME_SW;
	const char *outputFileName_hw = OUTPUT_FILE_NAME_HW;

	//time_scale_hardware = 1 / 30.0;

	float* image_sw = (float *)malloc(sizeof(float)*IMAGE_HEIGHT*IMAGE_WIDTH);
	float* outImage_sw = (float *)malloc(sizeof(float)*IMAGE_HEIGHT*IMAGE_WIDTH);
	printf("main: check point 2-1\n");
	FILE* fp_v;
	/* Initialize array(s). */
	init_array(image_sw, imageWidth, imageHeight, inputFileName);


	/* Run kernel software. */

	software_start = getTimestamp();
	for (int i = 0; i < SOFTWARE_ITERATION; i++) {
		kernel_sw_serial(image_sw, outImage_sw);
	}
	software_end = getTimestamp();
//	POWER_MONITORING_EPILOGUE();
	software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
	printf("serial software execution time  %.6lf ms elapsed\n", software_execution_time);


	if(DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("huge iterations for manual power monitoring\n");
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				kernel_sw_serial(image_sw, outImage_sw);
			}
		}
	}


//	storeImage(outImage_sw, outputFileName_sw, IMAGE_HEIGHT, IMAGE_WIDTH, inputFileName);


	//==================================================================
	//        END:: HARDWARE ACCELERATOR
	//==================================================================


	// Be clean.
	free(image_sw);
	free(outImage_sw);
	return 0;
}


double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}

