#ifndef __ACCEL_H__
#define __ACCEL_H__
#include "icp.h"
#include "xruniteration_hw_hw.h"
#include <unistd.h>

#define ACCELERATOR                                       0x43C00000
typedef unsigned long long int u64;
typedef unsigned long u32;
typedef union {
	float f;
	u32   u;
}u32_float_conversion;


typedef union {
	int   i;
	u32   u;
}u32_int_uint_conversion;

//#define ITERATION_NUM 1

void accel_prologue();
void accel_epilogue();
void  accel_ready();
//void  accel_hp0_write(	u32 image_in_address, u32 image_out_address, u32 image_hight, u32 image_width);

void  accel_write(
				unsigned char 	*map_sw,
				int             *p_x,
				int             *p_y,

				int   			*robotPose_sw_dx,
				int   			*robotPose_sw_dy,
				float   		*robotPose_sw_theta,

				int             *old_sw_dx,
				int             *old_sw_dy,
				float           *old_sw_theta,


				int             *bestTransformation_sw_dx,
				int             *bestTransformation_sw_dy,
				float           *bestTransformation_sw_theta
		)
;
void  accel_read(
		int            *robotPose_dx,
		int            *robotPose_dy,
		float          *robotPose_theta,
		int            *bestTransformation_dx,
		int            *bestTransformation_dy,
		float          *bestTransformation_theta
		)
;
void  accel_start( );
void  accel_wait();
double getTimestamp();


void* fpgacl_malloc(unsigned long int size);
void fpgacl_free(void* user_var);

#endif //__ACCEL_H__
