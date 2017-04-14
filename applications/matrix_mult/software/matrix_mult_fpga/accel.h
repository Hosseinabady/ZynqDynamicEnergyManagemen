#ifndef __ACCEL_H__
#define __ACCEL_H__
#include "matrix_mult.h"
#include "xmatrix_mult_hw.h"

#define ACCELERATOR                                       0x43C00000


//#define ITERATION_NUM 1

void accel_prologue();
void accel_epilogue();
void  accel_ready();
//void  accel_hp0_write(	u32 image_in_address, u32 image_out_address, u32 image_hight, u32 image_width);

void  accel_write(	int n,
					int m,
					int p,
					DATA_TYPE *  a,
					DATA_TYPE *  b,
					DATA_TYPE *  c
				 );

void  accel_start( );

void  accel_wait();

double getTimestamp();
#endif //__ACCEL_H__
