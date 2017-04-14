#include "stdio.h"
#include "stdlib.h"
#include "sharpen.h"
#include "bmpfuncs.h"
#include <math.h>


	const float mask[MASK_WIDTH*MASK_HEIGHT] = {   0, -1,  0,
			                                      -1,  5, -1,
												   0, -1,  0
	                                           };


/* image initialization. */
void init_array(float* image, int imageWidth, int imageHeight, const char* inputFileName)
{
	readImage(inputFileName, &imageWidth, &imageHeight, image);
/*	int row, col;
	for (row = 0; row < IMAGE_HEIGHT; row++)
		for (col = 0; col < IMAGE_WIDTH; col++) {
			image[row * IMAGE_WIDTH + col] = row+col;
		}
*/
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

void kernel_hw(float* inImage_hw, float* outImage_hw) {


	DATA_TYPE* memory=0;

	sharpen_8DU(memory, memory, memory, memory, memory, memory, memory, memory, (u32)(inImage_hw), (u32)(outImage_hw));
}



int validate(float* outImage_sw, float* outImage_hw ) {
	int row, col;
	for (row = 0; row < IMAGE_HEIGHT; row++) {
		for (col = 0; col < IMAGE_WIDTH; col++) {

			float hw = outImage_hw[row*IMAGE_WIDTH+col];
			float sw = outImage_sw[row*IMAGE_WIDTH+col];

			float diff = fabs(hw - sw);
			if(diff > 0.001 || diff != diff){
				printf("Error in out_data at outImage_hw[%d][%d] = %f != outImage_sw[%d][%d] = %f\n", row, col, hw, row, col, sw);
				return -1;
			}
		}
	}
	return 0;
}

int main() {

	int status;
	int imageWidth = IMAGE_WIDTH;
	int imageHeight = IMAGE_HEIGHT;
	const char *inputFileName     = INPUT_FILE_NAME;
	const char *outputFileName_sw = OUTPUT_FILE_NAME_SW;
	const char *outputFileName_hw = OUTPUT_FILE_NAME_HW;


	float* image = (float *)malloc(sizeof(float)*IMAGE_HEIGHT*IMAGE_WIDTH);
	float* outImage_sw = (float *)malloc(sizeof(float)*IMAGE_HEIGHT*IMAGE_WIDTH);
	float* outImage_hw = (float *)malloc(sizeof(float)*IMAGE_HEIGHT*IMAGE_WIDTH);

	init_array(image, imageWidth, imageHeight, inputFileName);

	printf("input image!\n");
//	print_output(image, IMAGE_WIDTH, IMAGE_HEIGHT);

	kernel_sw(image, outImage_sw);
	printf("SOFTWARE OUTPUT!\n");
//	print_output(outImage_sw, IMAGE_WIDTH, IMAGE_HEIGHT);
	storeImage(outImage_sw, outputFileName_sw, IMAGE_HEIGHT, IMAGE_WIDTH, inputFileName);


	kernel_hw(image, outImage_hw);
	printf("HARDWARE OUTPUT!\n");
//	print_output(outImage_hw, IMAGE_WIDTH, IMAGE_HEIGHT);
	storeImage(outImage_hw, outputFileName_hw, IMAGE_HEIGHT, IMAGE_WIDTH, inputFileName);


	status = validate(outImage_sw, outImage_hw);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
	 	printf("Validation FAILED!\n");
	}


	return status;

}
