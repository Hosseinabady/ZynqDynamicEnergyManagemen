#ifndef __ACCEL_H__
#define __ACCEL_H__
#include "histogram.h"
#include "xhistogram_hw.h"
extern "C" {
#include <measurement.h>
#include <set_frequency.h>
#include <fpgacl_memory.h>
#include <monitoring.h>
}
#define ACCELERATOR                                       0x43C00000


//#define ITERATION_NUM 1

void accel_prologue();
void accel_epilogue();
void  accel_ready();
//void  accel_hp0_write(	u32 image_in_address, u32 image_out_address, u32 image_hight, u32 image_width);

void  accel_write(	DATA_TYPE *  image_offset,
					u32 *        histogram_offset
				 );

void  accel_start( );

void  accel_wait();

double getTimestamp();
#endif //__ACCEL_H__
