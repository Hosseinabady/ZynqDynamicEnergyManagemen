#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__


typedef unsigned int  u32;
typedef unsigned char u8;
typedef float         DATA_TYPE;


#define DATA_LENGTH (1024*1024)
#define BIN_LENGTH   256

void histogram( DATA_TYPE *memory_0_0,
				DATA_TYPE *memory_0_1,
				DATA_TYPE *memory_0_2,
				DATA_TYPE *memory_0_3,
		        u32       *memory_1,
		        u32        inputImage_offset,
				u32        hitogram_offset);

#endif //__HISTOGRAM_H__
