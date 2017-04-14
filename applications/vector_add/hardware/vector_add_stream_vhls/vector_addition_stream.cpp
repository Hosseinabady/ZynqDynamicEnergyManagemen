#include <string.h>
#include <hls_stream.h>
#include "vector_addition_stream.h"

#define NUMBER_OF_THREAD 2

void vector_add( DATA_TYPE* memory_1,
		 DATA_TYPE* memory_2,
		 DATA_TYPE* memory_3,
		 u32        a_offset,
		 u32        b_offset,
		 u32        c_offset);

void vector_addition_stream( DATA_TYPE* memory_1_1,
							 DATA_TYPE* memory_1_2,
							 DATA_TYPE* memory_1_3,

							 DATA_TYPE* memory_2_1,
							 DATA_TYPE* memory_2_2,
							 DATA_TYPE* memory_2_3,



							 u32        a_offset,
							 u32        b_offset,
							 u32        c_offset
							) {
#pragma HLS INTERFACE s_axilite port=return bundle=control_bus
#pragma HLS INTERFACE s_axilite port=a_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=b_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=c_offset bundle=control_bus
#pragma HLS INTERFACE m_axi  port=memory_1_1
#pragma HLS INTERFACE m_axi  port=memory_1_2
#pragma HLS INTERFACE m_axi  port=memory_1_3
#pragma HLS INTERFACE m_axi  port=memory_2_1
#pragma HLS INTERFACE m_axi  port=memory_2_2
#pragma HLS INTERFACE m_axi  port=memory_2_3


	vector_add(memory_1_1, memory_1_2, memory_1_3, a_offset+0*n/NUMBER_OF_THREAD, b_offset+0*n/NUMBER_OF_THREAD, c_offset+0*n/NUMBER_OF_THREAD);
	vector_add(memory_2_1, memory_2_2, memory_2_3, a_offset+1*n/NUMBER_OF_THREAD, b_offset+1*n/NUMBER_OF_THREAD, c_offset+1*n/NUMBER_OF_THREAD);


}




void vector_add( DATA_TYPE* memory_1,
		 DATA_TYPE* memory_2,
		 DATA_TYPE* memory_3,
		 u32        a_offset,
		 u32        b_offset,
		 u32        c_offset) {
#pragma HLS DATAFLOW

	hls::stream<DATA_TYPE> input_a_fifo;
#pragma HLS STREAM variable=input_a_fifo  dim=1
	hls::stream<DATA_TYPE> input_b_fifo;
#pragma HLS STREAM variable=input_b_fifo  dim=1
	hls::stream<DATA_TYPE> input_c_fifo;
#pragma HLS STREAM variable=input_c_fifo  dim=1


	for (int i = 0; i < n/NUMBER_OF_THREAD; i++) {
#pragma HLS PIPELINE
		input_a_fifo << *(memory_1+a_offset+i);
		input_b_fifo << *(memory_2+b_offset+i);
	}


	for (int i = 0; i < n/NUMBER_OF_THREAD; i++) {
#pragma HLS PIPELINE
		DATA_TYPE a_local = input_a_fifo.read();
		DATA_TYPE b_local = input_b_fifo.read();

		DATA_TYPE  c_local = a_local + b_local;

		input_c_fifo << c_local;
	}


	for (int i = 0; i < n/NUMBER_OF_THREAD; i++) {
#pragma HLS PIPELINE
		*(memory_3+c_offset+i) = input_c_fifo.read();
	}

}
