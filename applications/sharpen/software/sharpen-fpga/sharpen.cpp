
#define POLYBENCH_USE_SCALAR_LB
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <sched.h>        // for sched_xxx() function calls
#include <sys/types.h>    // for pid_t
#include <sys/resource.h> // for getpriority()
#include <time.h>
#include "accel.h"
extern "C" {
#include <fpgacl_memory.h>
#include <measurement.h>
#include <set_frequency.h>
#include <monitoring.h>
}


#include "bmpfuncs.h"

void refresh_hardware(int *accel_status);
int run_command(char cmd[1000]);

#define EXE_TIME_MONITORING_ITERATION_NUM  10

#define DELAY_FOR_POWER_MEASUREMENT  1
extern char log_file_name[1000];

const float mask[MASK_WIDTH*MASK_HEIGHT] = {   0, -1,  0,
		                                      -1,  5, -1,
											   0, -1,  0
                                           };



#define DELAY() 		{ volatile long long int delay_var = 0; \
for (int delay_index = 0; delay_index < 10000; delay_index++) { \
	delay_var+=2; \
} }
/* image initialization. */
void init_array(float* image, int imageWidth, int imageHeight, const char* inputFileName)
{
	/*
	time_t t;
	srand((unsigned) time(&t));
	readImage(inputFileName, &imageWidth, &imageHeight, image);
	*/
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


/* Software impemented Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_sw(float* inputImage, float* outImage) {

	int row, col, r, c;
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

void kernel_sw_OpenMP(float* inputImage, float* outImage) {

	int row, col, r, c;
#pragma omp parallel for num_threads(2)
	for (row = 0; row < IMAGE_HEIGHT; row++) {
		for (col = 0; col < IMAGE_WIDTH; col++) {
			float sum = 0;
	        for (r = 0; r < MASK_HEIGHT; r++)
				#pragma ivdep
                #pragma vector aligned
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
double hardware_part_start;
double hardware_part_end;

int first_iteration;
double software_part_time = 0;
double hardware_part_time = 0;

void kernel_hw(float* image_in_address, float* image_out_address) {

	accel_write(image_in_address, image_out_address);
	accel_start();
//	accel_wait(); //polling
	sleep(10);    //interrupt



}

int validate(float* outImage_sw, float* outImage_hw ) {
	int row, col;
	int k = 0;
	for (row = 0; row < IMAGE_HEIGHT; row++) {
		for (col = 0; col < IMAGE_WIDTH; col++) {

			float hw = outImage_hw[row*IMAGE_WIDTH+col];
			float sw = outImage_sw[row*IMAGE_WIDTH+col];

			float diff = fabs(hw - sw);
			if(diff > 0.001 || diff != diff){
				printf("Error in out_data at outImage_hw[%d][%d] = %f != outImage_sw[%d][%d] = %f\n", row, col, hw, row, col, sw);
				if(k++ > 20)
					return -1;
			}
		}
	}
	return 0;
}
#define SOFTWARE_ITERATION 1

int main(int argc, char** argv)
{


	int status;
	int accel_status = 0;
	double time_scale_hardware = 1.0;
   	double hardware_start;
   	double hardware_end;
	double hardware_execution_time;

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
	float* image_hw_result = (float *)malloc(sizeof(float)*IMAGE_HEIGHT*IMAGE_WIDTH);
	printf("main: check point 2\n");
	float* outImage_sw = (float *)malloc(sizeof(float)*IMAGE_HEIGHT*IMAGE_WIDTH);
	printf("main: check point 2-1\n");
	FILE* fp_v;
	/* Initialize array(s). */
	init_array(image_sw, imageWidth, imageHeight, inputFileName);


	strcpy(log_file_name, "log_power_monitor_overhead_");
//	file_power_profile_create(log_file_name);
	printf("main: check point 3-1\n");
	/* Run kernel software. */

	software_start = getTimestamp();
	for (int i = 0; i < SOFTWARE_ITERATION; i++) {
		kernel_sw(image_sw, outImage_sw);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);


	int frequency_factor_min = 10;
	int vccint_min = 0.67;

	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);
	VOLTAGE_SCALING_PROLOGUE(vccint_min, 1.0, 0.01);
	FREQUENCY_SCALING_PROLOGUE(frequency_factor_min, 50, 1);


	refresh_hardware(&accel_status);


	DATA_TYPE *image_hw;
	DATA_TYPE *outImage_hw;
	if ( (image_hw=(DATA_TYPE *)fpgacl_malloc(IMAGE_HEIGHT*IMAGE_WIDTH*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (outImage_hw=(DATA_TYPE *)fpgacl_malloc(IMAGE_HEIGHT*IMAGE_WIDTH*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");

	init_array(image_sw, imageWidth, imageHeight, inputFileName);

	fpgacl_memwrite((void *)image_sw, (u32*)image_hw, sizeof(DATA_TYPE)*IMAGE_HEIGHT*IMAGE_WIDTH);

	kernel_sw(image_sw, outImage_sw);

	kernel_hw(image_hw, outImage_hw);

	fpgacl_memread((void*)image_hw_result, (u32 *)outImage_hw, sizeof(float)*IMAGE_HEIGHT*IMAGE_WIDTH);

	status = validate(outImage_sw, image_hw_result);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
		printf("Validation FAILED!\n");
		frequency_factor_min = freq+1;
	}

	if (status == 0) {
		//=============================================================================
		// compute the iteration_number
		//=============================================================================

		hardware_start = getTimestamp();
		for (int itr = 0; itr < EXE_TIME_MONITORING_ITERATION_NUM; itr++)  {
			kernel_hw(image_hw, outImage_hw);
		}
		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 2000/hardware_execution_time;
		//============================================================================
		fp_v=fopen(log_file_name, "a");
		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			kernel_hw(image_hw, outImage_hw);
		}
		POWER_MONITORING_EPILOGUE();

		fprintf(fp_v,"Validation PASSED!\n");

		fclose(fp_v);
	}

	fpgacl_free((u32)image_hw);
	fpgacl_free((u32)outImage_hw);


	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();

//	storeImage(outImage_sw, outputFileName_sw, IMAGE_HEIGHT, IMAGE_WIDTH, inputFileName);
//	storeImage(image_hw_result, outputFileName_hw, IMAGE_HEIGHT, IMAGE_WIDTH, inputFileName);



	//==================================================================
	//        END:: HARDWARE ACCELERATOR
	//==================================================================


	// Be clean.
	free(image_sw);
	free(outImage_sw);
	free(image_hw_result);
	return 0;
}




int run_command(char cmd[1000]) {
	FILE *pp;
	int status = 0;
	pp = popen(cmd, "r");
	if (pp != NULL) {
	    while (1) {
	      char *line;
	      char buf[1000];
	      line = fgets(buf, sizeof buf, pp);
	      if (line == NULL) break;
	      if (line[0] == 'd') printf("%s", line); /* line includes '\n' */
	    }
	    status = -1;
	}
	pclose(pp);
	return status;
}

void refresh_hardware(int *accel_status) {
	char cmd[100];

	sprintf(cmd, "chmod u+x initial.sh");
	run_command(cmd);

	sprintf(cmd, "chmod u+x clean.sh");
	run_command(cmd);

	if (*accel_status == 0) {

		printf("refresh_hardware: check point 1\n");
		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		accel_prologue();

		sprintf(cmd, "cat sharpen_8DU.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat  sharpen_8DU.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}






}
