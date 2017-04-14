#ifndef __ACCEL_H__
#define __ACCEL_H__
#include "pr.h"
#include "xpr_hw.h"

#define ACCELERATOR                                       0x43C00000


//#define ITERATION_NUM 1

void accel_prologue();
void accel_epilogue();
void  accel_ready();
//void  accel_hp0_write(	u32 image_in_address, u32 image_out_address, u32 image_hight, u32 image_width);

void  accel_write(  DATA_TYPE  *X,
					DATA_TYPE  *Y,
					u32         n
				 );

void  accel_read(   DATA_TYPE *A0,
					DATA_TYPE *A1,
					DATA_TYPE *A2
				 );

void  accel_start( );

void  accel_wait();

double getTimestamp();
#endif //__ACCEL_H__
