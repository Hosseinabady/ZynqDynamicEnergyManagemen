#include <string.h>
#include <hls_stream.h>
#include "saxp.h"

inline void saxp_kernel(DATA_TYPE* memory_1,
                        DATA_TYPE* memory_2,
						  u32      a,
					      u32      b,
						  u32      n);

void saxp_stream( DATA_TYPE* memory_1,
		          DATA_TYPE* memory_2,
				  DATA_TYPE* memory_3,
				  DATA_TYPE* memory_4,
				  DATA_TYPE* memory_5,
				  DATA_TYPE* memory_6,
				  DATA_TYPE* memory_7,
				  DATA_TYPE* memory_8,
				  u32        a,
			      u32        b,
				  u32        n
		       ) {
#pragma HLS INTERFACE s_axilite port=return bundle=control_bus
#pragma HLS INTERFACE s_axilite port=a bundle=control_bus
#pragma HLS INTERFACE s_axilite port=b bundle=control_bus
#pragma HLS INTERFACE s_axilite port=n bundle=control_bus
#pragma HLS INTERFACE m_axi  port=memory_1
#pragma HLS INTERFACE m_axi  port=memory_2
#pragma HLS INTERFACE m_axi  port=memory_3
#pragma HLS INTERFACE m_axi  port=memory_4
#pragma HLS INTERFACE m_axi  port=memory_5
#pragma HLS INTERFACE m_axi  port=memory_6
#pragma HLS INTERFACE m_axi  port=memory_7
#pragma HLS INTERFACE m_axi  port=memory_8



	saxp_kernel(memory_1, memory_2, a+0*(n/4), b+0*(n/4), n/4);
	saxp_kernel(memory_3, memory_4, a+1*(n/4), b+1*(n/4), n/4);
	saxp_kernel(memory_5, memory_6, a+2*(n/4), b+2*(n/4), n/4);
	saxp_kernel(memory_7, memory_8, a+3*(n/4), b+3*(n/4), n/4);



}


inline void saxp_kernel(DATA_TYPE* memory_1,
                        DATA_TYPE* memory_2,
						  u32      a,
					      u32      b,
						  u32      n) {
#pragma HLS DATAFLOW
	hls::stream<DATA_TYPE> input_a_fifo;
	hls::stream<DATA_TYPE> input_b_fifo;


	for (int i = 0; i < n; i++) {
#pragma HLS PIPELINE
		input_a_fifo << *(memory_1+a+i);
	}


	for (int i = 0; i < n; i++) {
#pragma HLS PIPELINE
		DATA_TYPE a_local = input_a_fifo.read();


		DATA_TYPE  b_local = 2.34*a_local + 5.2355;

		input_b_fifo << b_local;
	}


	for (int i = 0; i < n; i++) {
#pragma HLS PIPELINE
		*(memory_2+b+i) = input_b_fifo.read();
	}

}
