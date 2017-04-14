#ifndef __MATRIX_MULT_H__
#define __MATRIX_MULT_H__

#define N  512
#define M  512
#define P  256


typedef unsigned long int u32;
typedef int DATA_TYPE;


void matrix_mult(	DATA_TYPE *memory_0,
		            DATA_TYPE *memory_1_0,
					DATA_TYPE *memory_2_0,
		            DATA_TYPE *memory_1_1,
					DATA_TYPE *memory_2_1,
		            DATA_TYPE *memory_1_2,
					DATA_TYPE *memory_2_2,
		            DATA_TYPE *memory_1_3,
					DATA_TYPE *memory_2_3,
					u32        a_offset_address,
					u32        b_offset_address,
					u32        c_offset_address
				  );
#endif //__MATRIX_MULT_H__
