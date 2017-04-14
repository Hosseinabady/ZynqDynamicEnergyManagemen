#ifndef __ACCEL_H__
#define __ACCEL_H__
#include "nbody.h"
#include "xnbody_hw.h"

#define ACCELERATOR                                       0x43C00000


//#define ITERATION_NUM 1

void accel_prologue();
void accel_epilogue();

//void  accel_hp0_write(	u32 image_in_address, u32 image_out_address, u32 image_hight, u32 image_width);

void  accel_write(	DATA_TYPE *  positionsIn,
					DATA_TYPE *  positionsOut,
					DATA_TYPE *  velocitiesIn,
					DATA_TYPE *  velocitiesOut
				 );

void  accel_start( );

void  accel_wait();
void  accel_ready();
double getTimestamp();
#endif //__ACCEL_H__
