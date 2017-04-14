#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "matrix_mult.h"

#include <hls_stream.h>

#define NUMBER_OF_THREADS  1
#define BLOCK    4  //do not change BLOCK

void mxv(	DATA_TYPE *memory_0,
 		 	DATA_TYPE *memory_3,
			u32        a_offset_address,
			DATA_TYPE  B[M][P/BLOCK],
			u32        c_offset_address);

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
				  ) {

#pragma HLS INTERFACE s_axilite port=return bundle=control_bus

#pragma HLS INTERFACE s_axilite port=a_offset_address bundle=control_bus
#pragma HLS INTERFACE s_axilite port=b_offset_address bundle=control_bus
#pragma HLS INTERFACE s_axilite port=c_offset_address bundle=control_bus
#pragma HLS INTERFACE m_axi port=memory_0
#pragma HLS INTERFACE m_axi port=memory_1_0
#pragma HLS INTERFACE m_axi port=memory_2_0
#pragma HLS INTERFACE m_axi port=memory_1_1
#pragma HLS INTERFACE m_axi port=memory_2_1

#pragma HLS INTERFACE m_axi port=memory_1_2
#pragma HLS INTERFACE m_axi port=memory_2_2
#pragma HLS INTERFACE m_axi port=memory_1_3
#pragma HLS INTERFACE m_axi port=memory_2_3
//#pragma HLS DATAFLOW

	DATA_TYPE  B_0[M][P/BLOCK];
	DATA_TYPE  B_1[M][P/BLOCK];
	DATA_TYPE  B_2[M][P/BLOCK];
	DATA_TYPE  B_3[M][P/BLOCK];

	DATA_TYPE  tmp;
#pragma HLS ARRAY_PARTITION variable=B_0 cyclic factor=32 dim=1
#pragma HLS ARRAY_PARTITION variable=B_1 cyclic factor=32 dim=1
#pragma HLS ARRAY_PARTITION variable=B_2 cyclic factor=32 dim=1
#pragma HLS ARRAY_PARTITION variable=B_3 cyclic factor=32 dim=1

	for(int i = 0; i < M; i++) {
		for(int j = 0; j < P; j++) {
#pragma HLS PIPELINE
			tmp = *(memory_0+b_offset_address+i*P+j);
			if (j < 1* P/BLOCK)
				B_0[i][j-0* P/BLOCK] = tmp;
			else if (j < 2*P/BLOCK)
				B_1[i][j-1*P/BLOCK] = tmp;
			else if (j < 3*P/BLOCK)
				B_2[i][j-2*P/BLOCK] = tmp;
			else
				B_3[i][j-3*P/BLOCK] = tmp;

		}
	}

	for(int i = 0; i < N; i=i+1) {
		mxv(memory_1_0, memory_2_0, a_offset_address+i*M,     B_0, c_offset_address+i*P+0*P/BLOCK);
		mxv(memory_1_1, memory_2_1, a_offset_address+i*M,     B_1, c_offset_address+i*P+1*P/BLOCK);
		mxv(memory_1_2, memory_2_2, a_offset_address+i*M,     B_2, c_offset_address+i*P+2*P/BLOCK);
		mxv(memory_1_3, memory_2_3, a_offset_address+i*M,     B_3, c_offset_address+i*P+3*P/BLOCK);
	}

}

void mxv(	DATA_TYPE *memory_0,
 		 	DATA_TYPE *memory_3,
			u32        a_offset_address,
			DATA_TYPE  B[M][P/BLOCK],
			u32        c_offset_address
			) {
#pragma HLS DATAFLOW
	DATA_TYPE a[M];
#pragma HLS ARRAY_PARTITION variable=a cyclic factor=32 dim=1


	hls::stream<DATA_TYPE> a_fifo;
	hls::stream<DATA_TYPE> c_fifo;
	for(int j = 0; j < M; j++) {
#pragma HLS PIPELINE II=1
		a_fifo << *(memory_0 + a_offset_address+j);
	}

	DATA_TYPE tmp;

	for(int j = 0; j < P/BLOCK; j++) {
		for(int k = 0; k < M; k++) {
#pragma HLS PIPELINE
			if (k == 0) tmp = 0;
			if (j==0) {
				a[k] = a_fifo.read();
			}
			tmp += a[k]*B[k][j];

			if (k == M-1) c_fifo << tmp;
		}
	}



	for(int j = 0; j < P/BLOCK; j++) {
#pragma HLS PIPELINE
		*(memory_3+c_offset_address+j) = c_fifo.read();
	}


}



