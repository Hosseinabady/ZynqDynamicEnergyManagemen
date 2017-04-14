#ifndef __ACCEL_H__
#define __ACCEL_H__
#include "BlackScholes.h"
#include "xbs_stream_hw.h"
#define ACCELERATOR                                       0x43C00000


//#define ITERATION_NUM 1

typedef float DATA_TYPE;


void accel_prologue();
void accel_epilogue();

//void  accel_hp0_write(	u32 image_in_address, u32 image_out_address, u32 image_hight, u32 image_width);

void  accel_write(	DATA_TYPE *h_Call, //Call option price
		            DATA_TYPE *h_Put,  //Put option price
		            DATA_TYPE *h_S,    //Current stock price
		            DATA_TYPE *h_X,    //Option strike price
		            DATA_TYPE *h_T,    //Option years
	                u32        optionCount
				 );

void  accel_start( );

void  accel_wait();
void  accel_ready();
double getTimestamp();
#endif //__ACCEL_H__
