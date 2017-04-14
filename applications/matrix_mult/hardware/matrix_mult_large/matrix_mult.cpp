#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "matrix_mult.h"

#include <hls_stream.h>

#define NUMBER_OF_THREADS  1
#define BLOCK    16  //do not change BLOCK
#define PARALLEL_MODULE    8  //do not change BLOCK


void mxv(	DATA_TYPE *memory_0,
 		 	DATA_TYPE *memory_3,
			u32        a_offset_address,
			DATA_TYPE  B[M][BLOCK],
			u32        c_offset_address);

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


#pragma HLS INTERFACE m_axi port=memory_1_4
#pragma HLS INTERFACE m_axi port=memory_2_4
#pragma HLS INTERFACE m_axi port=memory_1_5
#pragma HLS INTERFACE m_axi port=memory_2_5

#pragma HLS INTERFACE m_axi port=memory_1_6
#pragma HLS INTERFACE m_axi port=memory_2_6
#pragma HLS INTERFACE m_axi port=memory_1_7
#pragma HLS INTERFACE m_axi port=memory_2_7


//#pragma HLS DATAFLOW

	DATA_TYPE  B_0[M][BLOCK];
	DATA_TYPE  B_1[M][BLOCK];
	DATA_TYPE  B_2[M][BLOCK];
	DATA_TYPE  B_3[M][BLOCK];
	DATA_TYPE  B_4[M][BLOCK];
	DATA_TYPE  B_5[M][BLOCK];
	DATA_TYPE  B_6[M][BLOCK];
	DATA_TYPE  B_7[M][BLOCK];

	DATA_TYPE  tmp;

	int p = 0;
	for (int p = 0; p < P/(PARALLEL_MODULE*BLOCK); p++) {

		for(int i = 0; i < M; i++) {
			for(int j = 0; j < P; j++) {
	#pragma HLS PIPELINE
				tmp = *(memory_0+b_offset_address+i*P+j);

				if (j >= p*PARALLEL_MODULE*BLOCK+0*BLOCK && j < p*PARALLEL_MODULE*BLOCK+BLOCK )
					B_0[i][j-(p*PARALLEL_MODULE*BLOCK)] = tmp;

				else if ( j >= p*PARALLEL_MODULE*BLOCK+1*BLOCK &&  j < p*PARALLEL_MODULE*BLOCK+2*BLOCK)
					B_1[i][j-(p*PARALLEL_MODULE*BLOCK+1*BLOCK)] = tmp;

				else if ( j >= p*PARALLEL_MODULE*BLOCK+2*BLOCK && j < p*PARALLEL_MODULE*BLOCK+3*BLOCK)
					B_2[i][j-(p*PARALLEL_MODULE*BLOCK+2*BLOCK)] = tmp;

				else if ( j >= p*PARALLEL_MODULE*BLOCK+3*BLOCK  && j < p*PARALLEL_MODULE*BLOCK+4*BLOCK)
					B_3[i][j-(p*PARALLEL_MODULE*BLOCK+3*BLOCK)] = tmp;

				else if ( j >= p*PARALLEL_MODULE*BLOCK+4*BLOCK  && j < p*PARALLEL_MODULE*BLOCK+5*BLOCK)
					B_4[i][j-(p*PARALLEL_MODULE*BLOCK+4*BLOCK)] = tmp;

				else if ( j >= p*PARALLEL_MODULE*BLOCK+5*BLOCK  && j < p*PARALLEL_MODULE*BLOCK+6*BLOCK)
					B_5[i][j-(p*PARALLEL_MODULE*BLOCK+5*BLOCK)] = tmp;

				else if ( j >= p*PARALLEL_MODULE*BLOCK+6*BLOCK  && j < p*PARALLEL_MODULE*BLOCK+7*BLOCK)
					B_6[i][j-(p*PARALLEL_MODULE*BLOCK+6*BLOCK)] = tmp;

				else if ( j >= p*PARALLEL_MODULE*BLOCK+7*BLOCK  && j < p*PARALLEL_MODULE*BLOCK+8*BLOCK)
					B_7[i][j-(p*PARALLEL_MODULE*BLOCK+7*BLOCK)] = tmp;



			}
		}

		for(int i = 0; i < N; i=i+1) {
			mxv(memory_1_0, memory_2_0, a_offset_address+i*M, B_0, c_offset_address+i*P+p*PARALLEL_MODULE*BLOCK+0*BLOCK);
			mxv(memory_1_1, memory_2_1, a_offset_address+i*M, B_1, c_offset_address+i*P+p*PARALLEL_MODULE*BLOCK+1*BLOCK);
			mxv(memory_1_2, memory_2_2, a_offset_address+i*M, B_2, c_offset_address+i*P+p*PARALLEL_MODULE*BLOCK+2*BLOCK);
			mxv(memory_1_3, memory_2_3, a_offset_address+i*M, B_3, c_offset_address+i*P+p*PARALLEL_MODULE*BLOCK+3*BLOCK);

			mxv(memory_1_4, memory_2_4, a_offset_address+i*M, B_4, c_offset_address+i*P+p*PARALLEL_MODULE*BLOCK+4*BLOCK);
			mxv(memory_1_5, memory_2_5, a_offset_address+i*M, B_5, c_offset_address+i*P+p*PARALLEL_MODULE*BLOCK+5*BLOCK);
			mxv(memory_1_6, memory_2_6, a_offset_address+i*M, B_6, c_offset_address+i*P+p*PARALLEL_MODULE*BLOCK+6*BLOCK);
			mxv(memory_1_7, memory_2_7, a_offset_address+i*M, B_7, c_offset_address+i*P+p*PARALLEL_MODULE*BLOCK+7*BLOCK);


		}
	}
}

void mxv(	DATA_TYPE *memory_0,
 		 	DATA_TYPE *memory_3,
			u32        a_offset_address,
			DATA_TYPE  B[M][BLOCK],
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

	for(int j = 0; j < BLOCK; j++) {
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



	for(int j = 0; j < BLOCK; j++) {
#pragma HLS PIPELINE
		*(memory_3+c_offset_address+j) = c_fifo.read();
	}


}



