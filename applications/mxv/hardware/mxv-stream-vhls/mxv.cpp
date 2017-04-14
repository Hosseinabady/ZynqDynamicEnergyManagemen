#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "mxv.h"

#include <hls_stream.h>

#define NUMBER_OF_THREADS  4


inline void work_group( DATA_TYPE *memory_1,
				 DATA_TYPE *memory_2,
				 u32    a_offset_address,
				 u32    b_offset_address,
				 DATA_TYPE *c
				);

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
				  ) {

#pragma HLS INTERFACE s_axilite port=return bundle=control_bus

#pragma HLS INTERFACE s_axilite port=a_offset_address bundle=control_bus
#pragma HLS INTERFACE s_axilite port=b_offset_address bundle=control_bus
#pragma HLS INTERFACE s_axilite port=c_offset_address bundle=control_bus
#pragma HLS INTERFACE m_axi port=memory_0
#pragma HLS INTERFACE m_axi port=memory_1
#pragma HLS INTERFACE m_axi port=memory_2
#pragma HLS INTERFACE m_axi port=memory_3

	DATA_TYPE c_1[M];
#pragma HLS ARRAY_PARTITION variable=c_1 cyclic factor=8 dim=1
	DATA_TYPE c_2[M];
#pragma HLS ARRAY_PARTITION variable=c_2 cyclic factor=8 dim=1
	DATA_TYPE c_3[M];
#pragma HLS ARRAY_PARTITION variable=c_3 cyclic factor=8 dim=1
	DATA_TYPE c_4[M];
#pragma HLS ARRAY_PARTITION variable=c_4 cyclic factor=8 dim=1
	DATA_TYPE c_5[M];
#pragma HLS ARRAY_PARTITION variable=c_5 cyclic factor=8 dim=1
	DATA_TYPE c_6[M];
#pragma HLS ARRAY_PARTITION variable=c_6 cyclic factor=8 dim=1
	DATA_TYPE c_7[M];
#pragma HLS ARRAY_PARTITION variable=c_7 cyclic factor=8 dim=1
	DATA_TYPE c_8[M];
#pragma HLS ARRAY_PARTITION variable=c_8 cyclic factor=8 dim=1


	u32 n = N;
	u32 m = M;


	for (int i = 0; i < m; i++) {
#pragma HLS PIPELINE
		DATA_TYPE tmp = *(memory_0+c_offset_address+i);
		c_1[i] = tmp;
		c_2[i] = tmp;

		c_3[i] = tmp;
		c_4[i] = tmp;

		c_5[i] = tmp;
		c_6[i] = tmp;

		c_7[i] = tmp;
		c_8[i] = tmp;
	}
  	work_group(memory_0, memory_1, a_offset_address+0*(m/NUMBER_OF_THREADS), b_offset_address+0*(m/NUMBER_OF_THREADS)*n, c_1);
  	work_group(memory_2, memory_3, a_offset_address+1*(m/NUMBER_OF_THREADS), b_offset_address+1*(m/NUMBER_OF_THREADS)*n, c_2);

  	work_group(memory_4, memory_5, a_offset_address+2*(m/NUMBER_OF_THREADS), b_offset_address+2*(m/NUMBER_OF_THREADS)*n, c_3);
  	work_group(memory_6, memory_7, a_offset_address+3*(m/NUMBER_OF_THREADS), b_offset_address+3*(m/NUMBER_OF_THREADS)*n, c_4);


}



inline void work_group(DATA_TYPE* memory_1,
				DATA_TYPE* memory_2,
				u32        a_offset_address,
				u32        b_offset_address,
				DATA_TYPE* c) {

	u32 n = N;
	u32 m = M;


	DATA_TYPE a[M];
#pragma HLS ARRAY_PARTITION variable=a cyclic factor=8 dim=1

	loop1: for(int k = 0; k < m/NUMBER_OF_THREADS; k++) {
#pragma HLS DATAFLOW
		hls::stream<DATA_TYPE> b_1;
#pragma HLS STREAM variable=b_1 depth=8 dim=1


		loop2: for (int i = 0; i < n; i=i+1) {
#pragma HLS PIPELINE
				b_1 <<  *(DATA_TYPE *)(memory_1+b_offset_address+k*m+i+0);
		}


	 loop3: for (int i = 0; i < n; i=i+8) {
#pragma HLS PIPELINE
			DATA_TYPE b_data_1 = b_1.read();
			DATA_TYPE b_data_2 = b_1.read();
			DATA_TYPE b_data_3 = b_1.read();
			DATA_TYPE b_data_4 = b_1.read();
			DATA_TYPE b_data_5 = b_1.read();
			DATA_TYPE b_data_6 = b_1.read();
			DATA_TYPE b_data_7 = b_1.read();
			DATA_TYPE b_data_8 = b_1.read();

			DATA_TYPE mult_1 = b_data_1*c[i+0];
			DATA_TYPE mult_2 = b_data_2*c[i+1];
			DATA_TYPE mult_3 = b_data_3*c[i+2];
			DATA_TYPE mult_4 = b_data_4*c[i+3];
			DATA_TYPE mult_5 = b_data_5*c[i+4];
			DATA_TYPE mult_6 = b_data_6*c[i+5];
			DATA_TYPE mult_7 = b_data_7*c[i+6];
			DATA_TYPE mult_8 = b_data_8*c[i+7];

			if (i == 0)
				a[k] = mult_1 + mult_2 + mult_3 + mult_4 + mult_5 + mult_6 + mult_7 + mult_8;
			else
				a[k] += mult_1 + mult_2 + mult_3 + mult_4 + mult_5 + mult_6 + mult_7 + mult_8;
		}

	}

  	loop4: for(int k = 0; k < m/NUMBER_OF_THREADS; k++) {
#pragma HLS PIPELINE
  		*(memory_2+a_offset_address+k) = a[k];
  	}
}





