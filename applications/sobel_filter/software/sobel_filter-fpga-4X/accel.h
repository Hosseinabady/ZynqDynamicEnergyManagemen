#ifndef __ACCEL_H__
#define __ACCEL_H__
#include "sobel_filter.h"
#include "xsobel_filter_hw.h"
#define ACCELERATOR                                       0x43C00000


//#define ITERATION_NUM 1


void accel_prologue();
void accel_epilogue();

//void  accel_hp0_write(	u32 image_in_address, u32 image_out_address, u32 image_hight, u32 image_width);

void  accel_write(	DATA_TYPE *  input_image,
					DATA_TYPE *  output_image,
					u32          hight,
					u32          width
				 );

void  accel_start( );

void  accel_wait();
void  accel_ready();
double getTimestamp();
#endif //__ACCEL_H__
