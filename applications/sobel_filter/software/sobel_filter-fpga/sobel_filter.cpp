
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

extern "C" {
#include <fpgacl_memory.h>
#include <measurement.h>
#include <set_frequency.h>
#include <monitoring.h>

}
#include "ap_bmp.h"
#include "accel.h"


void refresh_hardware(int *accel_status);

//Arrays to send and receive data from the accelerator
AXI_PIXEL in_pix[MAX_HEIGHT][MAX_WIDTH];
AXI_PIXEL out_pix[MAX_HEIGHT][MAX_WIDTH];

#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM  10

#define DELAY_FOR_POWER_MEASUREMENT  1
extern char log_file_name[1000];





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
	for (row = 0; row < imageHeight; row++)
		for (col = 0; col < imageWidth; col++) {
			image[row * imageWidth + col] = rand()/(float)RAND_MAX;//row+col;
		}

}




double software_part_start;
double software_part_end;
double hardware_part_start;
double hardware_part_end;

int first_iteration;
double software_part_time = 0;
double hardware_part_time = 0;

void sobel_filter_hw(DATA_TYPE* image_in_address, DATA_TYPE* image_out_address, u32 hight, u32 width) {

	accel_write(image_in_address, image_out_address, hight, width);
	accel_start();
//	accel_wait(); //polling
	sleep(10);    //interrupt



}

int validate(float* outImage_sw, float* outImage_hw ) {
	int row, col;
	int k = 0;
	for (row = 0; row < MAX_HEIGHT; row++) {
		for (col = 0; col < MAX_WIDTH; col++) {

			float hw = outImage_hw[row*MAX_WIDTH+col];
			float sw = outImage_sw[row*MAX_WIDTH+col];

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

	int accel_status = 0;
	int status;
	FILE* fp_v;
	char cmd[100];
	double time_scale_hardware = 1.0;
   	double hardware_start;
   	double hardware_end;
	double hardware_execution_time;

	double software_start;
   	double software_end;
   	double software_execution_time;


   	printf("main: check point 1\n");


    int           	x,y;
    int			width, height;
    char tempbuf[2000] = INPUT_IMAGE;
    char tempbuf_golden[2000] = INPUT_IMAGE_GOLDEN;
    char tempbuf1[2000] = OUTPUT_IMAGE;
    int check_results = 0;


    AXI_PIXEL* in_pix_hw;
    AXI_PIXEL* out_pix_hw;

    unsigned char *R;
    unsigned char *G;
    unsigned char *B;

    unsigned char *R_golden;
    unsigned char *G_golden;
    unsigned char *B_golden;

    R = (unsigned char *)malloc(MAX_HEIGHT * MAX_WIDTH * sizeof(unsigned char));
    G = (unsigned char *)malloc(MAX_HEIGHT * MAX_WIDTH * sizeof(unsigned char));
    B = (unsigned char *)malloc(MAX_HEIGHT * MAX_WIDTH * sizeof(unsigned char));

    R_golden = (unsigned char *)malloc(MAX_HEIGHT * MAX_WIDTH * sizeof(unsigned char));
    G_golden = (unsigned char *)malloc(MAX_HEIGHT * MAX_WIDTH * sizeof(unsigned char));
    B_golden = (unsigned char *)malloc(MAX_HEIGHT * MAX_WIDTH * sizeof(unsigned char));

    AXI_PIXEL* out_pix_hw_result = (AXI_PIXEL *)malloc(sizeof(AXI_PIXEL)*MAX_HEIGHT*MAX_WIDTH);

    // Fill a frame with data
    int read_tmp = BMP_Read(tempbuf, MAX_HEIGHT, MAX_WIDTH, R, G, B);
    if(read_tmp != 0) {
      printf("%s Loading image failed\n", tempbuf);
      exit (1);
    }

    read_tmp = BMP_Read(tempbuf_golden, MAX_HEIGHT, MAX_WIDTH, R_golden, G_golden, B_golden);
    if(read_tmp != 0) {
       printf("%s Loading image failed\n", tempbuf);
        exit (1);
    }

    // Copy Input Image to pixel data structure
    // Hardware accelerator works on video pixel streams
     for(x = 0; x < MAX_HEIGHT; x++){
      for(y = 0; y < MAX_WIDTH; y++){
        RGB pixel;
        pixel.R = R[x*MAX_WIDTH + y];
        pixel.G = G[x*MAX_WIDTH + y];
        pixel.B = B[x*MAX_WIDTH + y];
        in_pix[x][y] = pixel.R;
        in_pix[x][y] = in_pix[x][y] << 8;
        in_pix[x][y] = in_pix[x][y] | pixel.G;
        in_pix[x][y] = in_pix[x][y] << 8;
        in_pix[x][y] = in_pix[x][y] | pixel.B;

      }
     }


 	int frequency_factor_min = 9;
 	int vccint_min = 0.67;


 	strcpy(log_file_name, "log_power_monitor_overhead_");
 	file_power_profile_create(log_file_name);
 	VOLTAGE_SCALING_PROLOGUE(vccint_min, 0.80, 0.01);
 	FREQUENCY_SCALING_PROLOGUE(frequency_factor_min, 50, 1);

    refresh_hardware(&accel_status);



	if ( (in_pix_hw=(AXI_PIXEL *)fpgacl_malloc(MAX_HEIGHT*MAX_WIDTH*sizeof(AXI_PIXEL))) == NULL )
			perror("memory allocation for in_pix_hw");
	if ( (out_pix_hw=(AXI_PIXEL *)fpgacl_malloc(MAX_HEIGHT*MAX_WIDTH*sizeof(AXI_PIXEL))) == NULL )
			perror("memory allocation for out_pix_hw");


	fpgacl_memwrite((void *)in_pix, (u32*)in_pix_hw, sizeof(DATA_TYPE)*MAX_HEIGHT*MAX_WIDTH);
	fpgacl_memwrite((void *)in_pix, (u32*)out_pix_hw, sizeof(DATA_TYPE)*MAX_HEIGHT*MAX_WIDTH); //to change the output for each iteration


	hardware_start = getTimestamp();

	sobel_filter_hw(in_pix_hw, out_pix_hw, 1080, 1920);

    hardware_end = getTimestamp();
	hardware_execution_time = (hardware_end-hardware_start)/(1000);
	printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);


    fpgacl_memread((void*)out_pix_hw_result, (u32 *)out_pix_hw, sizeof(float)*MAX_HEIGHT*MAX_WIDTH);


    for(x =0; x < MAX_HEIGHT; x++){
      for(y = 0; y < MAX_WIDTH; y++){
        RGB pixel;
        pixel.B = out_pix_hw_result[x*MAX_WIDTH + y] & 0x000000FF;
        pixel.G = (out_pix_hw_result[x*MAX_WIDTH + y] & 0x0000FF00) >> 8;
        pixel.R = (out_pix_hw_result[x*MAX_WIDTH + y] & 0x00FF0000) >> 16;

        R[x*MAX_WIDTH + y] = pixel.R;
        G[x*MAX_WIDTH + y] = pixel.G;
        B[x*MAX_WIDTH + y] = pixel.B;
      }
     }

    //Write the image back to disk
    //sprintf(tempbuf1, "%s.bmp", OUTPUT_IMAGE_BASE);
    int write_tmp = BMP_Write(tempbuf1, MAX_HEIGHT, MAX_WIDTH, R, G, B);
    if(write_tmp != 0){
      printf("WriteBMP %s failed\n", tempbuf);
      exit(1);
    }
    printf("Simulation Complete\n");

    check_results = 0;
    for(x =0; x < MAX_HEIGHT; x++){
    	if (check_results == 1) break;
      for(y = 0; y < MAX_WIDTH; y++){
        RGB pixel;
        pixel.B = out_pix_hw_result[x*MAX_WIDTH + y] & 0x000000FF;
        pixel.G = (out_pix_hw_result[x*MAX_WIDTH + y] & 0x0000FF00) >> 8;
        pixel.R = (out_pix_hw_result[x*MAX_WIDTH + y] & 0x00FF0000) >> 16;

        if (  pixel.R != R_golden[x*MAX_WIDTH + y]
           || pixel.G != G_golden[x*MAX_WIDTH + y]
  		 || pixel.B != B_golden[x*MAX_WIDTH + y]) {
        	printf ("error at (%d, %d) R=%d should be %d, G=%d should be %d, B=%d should be %d \n", x, y, pixel.R,  R_golden[x*MAX_WIDTH + y], pixel.G,  G_golden[x*MAX_WIDTH + y], pixel.B,  B_golden[x*MAX_WIDTH + y]);
      	  check_results = 1;
      	  break;
        }
      }
    }

    if(check_results != 0){
      printf("Output image has mismatches with reference output image!\n");
      printf("Validation FAILED!\n");
      check_results = 1;
      frequency_factor_min = freq+1;
    }
    else{
      printf("Output image matches the reference output image\n");
      printf("Validation PASSED!\n");

    }





    if(check_results == 0){
		//=============================================================================
		// compute the iteration_number
		//=============================================================================

		hardware_start = getTimestamp();
		for (int i = 0; i < EXE_TIME_MONITORING_ITERATION_NUM; i++) {
			sobel_filter_hw(in_pix_hw, out_pix_hw, 1080, 1920);
		}

		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 4000/hardware_execution_time;
		//============================================================================
		fp_v=fopen(log_file_name, "a");
		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			sobel_filter_hw(in_pix_hw, out_pix_hw, 1080, 1920);
		}
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");

		if (MANUAL_POWER_MONITOR_ITERATION != 1) {
			printf("loop for manual power monitoring!\n");
			for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
				for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
					sobel_filter_hw(in_pix_hw, out_pix_hw, 1080, 1920);
				}
			}
		}
		fclose(fp_v);

	}

    fpgacl_free((u32)out_pix_hw);
    fpgacl_free((u32)in_pix_hw);

	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();



    free(R);
    free(G);
    free(B);
    free(R_golden);
    free(G_golden);
    free(B_golden);

    free(out_pix_hw_result);


    return check_results;

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

		sprintf(cmd, "cat  sobel_filter_stream.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat   sobel_filter_stream.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}





}
