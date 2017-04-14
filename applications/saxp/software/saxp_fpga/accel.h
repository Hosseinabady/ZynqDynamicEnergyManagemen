#ifndef __ACCEL_H__
#define __ACCEL_H__
#include "saxp.h"
#include "xsaxp_stream_hw.h"
#define ACCELERATOR_0                                       0x43C00000




//#define ITERATION_NUM 1

typedef float DATA_TYPE;

void accel_prologue();
void accel_epilogue();

//void  accel_hp0_write(	u32 image_in_address, u32 image_out_address, u32 image_hight, u32 image_width);

void  accel_write(	DATA_TYPE *  a,
					DATA_TYPE *  b,
					u32          n
				 );

void  accel_start( );

void  accel_wait();
#endif //__ACCEL_H__
