
#include <string.h>
#include <hls_stream.h>
#include "column-2dmean.h"

inline void accumulate_column(DATA_TYPE* memory_1, DATA_TYPE* memory_2, u32 data_offset, u32        mean_offset, DATA_TYPE float_n);


#define NUMBER_OF_THREAD 4

void column_2dmean(	DATA_TYPE* memory_1,
					DATA_TYPE* memory_2,

					DATA_TYPE* memory_3,
					DATA_TYPE* memory_4,

					DATA_TYPE* memory_5,
					DATA_TYPE* memory_6,

					DATA_TYPE* memory_7,
					DATA_TYPE* memory_8,

					u32        data_offset,
					u32        mean_offset,
					int        n) {

#pragma HLS INTERFACE s_axilite port=return bundle=control_bus

#pragma HLS INTERFACE m_axi port=memory_1
#pragma HLS INTERFACE m_axi port=memory_2


#pragma HLS INTERFACE m_axi port=memory_3
#pragma HLS INTERFACE m_axi port=memory_4

#pragma HLS INTERFACE m_axi port=memory_5
#pragma HLS INTERFACE m_axi port=memory_6

#pragma HLS INTERFACE m_axi port=memory_7
#pragma HLS INTERFACE m_axi port=memory_8


#pragma HLS INTERFACE s_axilite port=data_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=mean_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=n           bundle=control_bus

//#pragma HLS DATAFLOW

	DATA_TYPE float_n = 1.0*n;

	accumulate_column(memory_1, memory_2, data_offset+0*M/NUMBER_OF_THREAD, mean_offset+0*M/NUMBER_OF_THREAD, float_n);
	accumulate_column(memory_3, memory_4, data_offset+1*M/NUMBER_OF_THREAD, mean_offset+1*M/NUMBER_OF_THREAD, float_n);
	accumulate_column(memory_5, memory_6, data_offset+2*M/NUMBER_OF_THREAD, mean_offset+2*M/NUMBER_OF_THREAD, float_n);
	accumulate_column(memory_7, memory_8, data_offset+3*M/NUMBER_OF_THREAD, mean_offset+3*M/NUMBER_OF_THREAD, float_n);

}




inline void accumulate_column(DATA_TYPE* memory_1, DATA_TYPE* memory_2, u32 data_offset,  u32        mean_offset, DATA_TYPE float_n) {

#pragma HLS DATAFLOW

	hls::stream<DATA_TYPE> data_i_j_fifo;
	DATA_TYPE  mean[M/NUMBER_OF_THREAD];
	hls::stream<DATA_TYPE> means_fifo;


	DATA_TYPE  tmp;

	LOOP0:for (int i = 0; i < N; i++) {
		LOOP1:for (int j = 0; j < M/NUMBER_OF_THREAD; j++) {
#pragma HLS PIPELINE
			data_i_j_fifo << *(memory_1+data_offset+(i+0)*M+j);
		}
	}

	LOOP2: for (int i = 0; i < N; i++) {
		LOOP3: for (int j = 0; j < M/NUMBER_OF_THREAD; j++) {
#pragma HLS PIPELINE
	    	DATA_TYPE d = data_i_j_fifo.read();
	    	if (i == 0)
	    		mean[j] = d;
	    	else
	    		mean[j] += d;

	    	if (i == N-1) {
	    		means_fifo << mean[j];
	    	}
	    }
	}

		LOOP4: for (int i = 0; i < M/NUMBER_OF_THREAD; i++) {
	#pragma HLS PIPELINE
			DATA_TYPE mean_tmp_1 = means_fifo.read();


			mean_tmp_1 /= float_n;


			*(memory_2+mean_offset+0*M/NUMBER_OF_THREAD+i) =  mean_tmp_1; //;
		}

}

