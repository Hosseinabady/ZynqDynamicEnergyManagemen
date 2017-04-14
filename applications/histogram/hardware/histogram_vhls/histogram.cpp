
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <hls_stream.h>
#include "histogram.h"

#define NO_THREAD 1

inline void histogram_kernel(
		DATA_TYPE *memory,
		u32        inputImage_offset,
        u32       *hist_local);

void histogram( DATA_TYPE *memory_0_0,
//				DATA_TYPE *memory_0_1,
//				DATA_TYPE *memory_0_2,
//				DATA_TYPE *memory_0_3,
		        u32       *memory_1,
		        u32        inputImage_offset,
				u32        hitogram_offset) {

#pragma HLS INTERFACE s_axilite port=hitogram_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=inputImage_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=return bundle=control_bus
#pragma HLS INTERFACE m_axi     port=memory_0_0
//#pragma HLS INTERFACE m_axi     port=memory_0_1
//#pragma HLS INTERFACE m_axi     port=memory_0_2
//#pragma HLS INTERFACE m_axi     port=memory_0_3

#pragma HLS INTERFACE m_axi     port=memory_1


	u32                    hist_local_1[BIN_LENGTH];
//	u32                    hist_local_2[BIN_LENGTH];
//	u32                    hist_local_3[BIN_LENGTH];
//	u32                    hist_local_4[BIN_LENGTH];


	computaion_loop_0 : for (int i = 0; i < BIN_LENGTH; i++) {
#pragma HLS PIPELINE
		hist_local_1[i] = *(memory_1+hitogram_offset+i);
//		hist_local_2[i] = 0;
//		hist_local_3[i] = 0;
//		hist_local_4[i] = 0;
	}


	histogram_kernel(memory_0_0, inputImage_offset + 0*DATA_LENGTH/NO_THREAD, hist_local_1);
//	histogram_kernel(memory_0_1, inputImage_offset + 1*DATA_LENGTH/NO_THREAD, hist_local_2);
//	histogram_kernel(memory_0_2, inputImage_offset + 2*DATA_LENGTH/NO_THREAD, hist_local_3);
//	histogram_kernel(memory_0_3, inputImage_offset + 3*DATA_LENGTH/NO_THREAD, hist_local_4);


	computaion_loop_4 : for (int i = 0; i < BIN_LENGTH; i++) {
#pragma HLS PIPELINE
		*(memory_1+hitogram_offset+i) = hist_local_1[i];//+hist_local_2[i]+hist_local_3[i]+hist_local_4[i];
	}


}


inline void histogram_kernel(
		DATA_TYPE *memory,
		u32        inputImage_offset,
        u32        *hist_local) {


#pragma HLS DATAFLOW
	hls::stream<DATA_TYPE> input_X_fifo;

	//receive data
	receive_data_loop_1 : for (int i = 0; i < DATA_LENGTH/NO_THREAD; i++) {
#pragma HLS PIPELINE
		input_X_fifo << *(memory+inputImage_offset+i);
	}

	//computation
	computaion_loop_3 : for (int i = 0; i < DATA_LENGTH/(NO_THREAD*2); i++) {
#pragma HLS DEPENDENCE array intra RAW false
#pragma HLS PIPELINE

		DATA_TYPE value1;
		DATA_TYPE value2;

		value1 = input_X_fifo.read();
		u32 index1 = (u32)value1;

		value2 = input_X_fifo.read();
		u32 index2 = (u32)value2;

		if (value1 != value2) {
			hist_local[index1] = hist_local[index1] + 1;
			hist_local[index2] = hist_local[index2] + 1;
		} else {
			hist_local[index1] = hist_local[index1] + 2;
		}
	}
}
