#ifndef __MATRIX_MULT_H__
#define __MATRIX_MULT_H__

#define N  512
#define M  512
#define P  512


typedef unsigned long int u32;
typedef int DATA_TYPE;


void matrix_mult_large(	DATA_TYPE *memory_0,
		            DATA_TYPE *memory_1_0,
					DATA_TYPE *memory_2_0,
		            DATA_TYPE *memory_1_1,
					DATA_TYPE *memory_2_1,
		            DATA_TYPE *memory_1_2,
					DATA_TYPE *memory_2_2,
		            DATA_TYPE *memory_1_3,
					DATA_TYPE *memory_2_3,

		            DATA_TYPE *memory_1_4,
					DATA_TYPE *memory_2_4,
		            DATA_TYPE *memory_1_5,
					DATA_TYPE *memory_2_5,
		            DATA_TYPE *memory_1_6,
					DATA_TYPE *memory_2_6,
		            DATA_TYPE *memory_1_7,
					DATA_TYPE *memory_2_7,

					u32        a_offset_address,
					u32        b_offset_address,
					u32        c_offset_address
				  );
#endif //__MATRIX_MULT_H__
