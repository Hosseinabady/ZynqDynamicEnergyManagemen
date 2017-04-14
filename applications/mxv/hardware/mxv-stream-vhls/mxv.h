#ifndef __OPENCL_DEVICE_H__
#define __OPENCL_DEVICE_H__

#define N 2000
#define M 2000






typedef unsigned long int u32;
typedef float DATA_TYPE;


void mxv_stream(	DATA_TYPE *memory_0,
		            DATA_TYPE *memory_1,
					DATA_TYPE *memory_2,
					DATA_TYPE *memory_3,
					DATA_TYPE *memory_4,
					DATA_TYPE *memory_5,

					DATA_TYPE *memory_6,
					DATA_TYPE *memory_7,

					u32        a_offset_address,
					u32        b_offset_address,
					u32        c_offset_address
				  );
#endif //__OPENCL_DEVICE_H__
