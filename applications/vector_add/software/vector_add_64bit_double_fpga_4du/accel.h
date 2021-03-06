#ifndef __ACCEL_H__
#define __ACCEL_H__
#include "vector_add.h"
#include "xvector_add_hw.h"
#define ACCELERATOR_0                                       0x43C00000



//#define ITERATION_NUM 1

typedef double DATA_TYPE;

void accel_prologue();
void accel_epilogue();

//void  accel_hp0_write(	u32 image_in_address, u32 image_out_address, u32 image_hight, u32 image_width);

void  accel_write(	DATA_TYPE *  a,
					DATA_TYPE *  b,
					DATA_TYPE *  c
				 );

void  accel_start( );

void  accel_wait();
void  accel_ready();
double getTimestamp();
#endif //__ACCEL_H__
