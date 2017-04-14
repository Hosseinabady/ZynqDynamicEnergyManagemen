#ifndef __SHARPEN__H__
#define __SHARPEN__H__

#include <string.h>
#include "hls_half.h"

#define IMAGE_HEIGHT   1080
#define IMAGE_WIDTH    1920


#define MASK_HEIGHT    3
#define MASK_WIDTH     3

typedef unsigned long	u32;

//typedef half   DATA_TYPE;
typedef float   DATA_TYPE;

#define INPUT_FILE_NAME  "image-1(1920x1080).bmp";
#define OUTPUT_FILE_NAME_SW "out_image-1-SW(1920x1080).bmp";
#define OUTPUT_FILE_NAME_HW "out_image-1-HW(1920x1080).bmp";


void sharpen_8DU(  volatile DATA_TYPE*   memory_0,
		           volatile DATA_TYPE*   memory_1,
				   volatile DATA_TYPE*   memory_2,
				   volatile DATA_TYPE*   memory_3,

				   volatile DATA_TYPE*   memory_4,
				   volatile DATA_TYPE*   memory_5,
				   volatile DATA_TYPE*   memory_6,
				   volatile DATA_TYPE*   memory_7,

		           volatile u32      input_image_offset,
				   volatile u32      output_image_offset
				);

#define MAX_COMPUTE_DEVICE 12


#endif //__SHARPEN__H__
