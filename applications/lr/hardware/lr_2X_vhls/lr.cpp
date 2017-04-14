#include "lr.h"
#include <string.h>
#include <hls_stream.h>


#define B 32
inline void lr_kernel(
		  DATA_TYPE    *memory_0
		, DATA_TYPE    *memory_1
		, u32           in_X
		, u32           in_Y
		, hls::stream<DATA_TYPE>      &SumX
		, hls::stream<DATA_TYPE>      &SumY
		, hls::stream<DATA_TYPE>      &SumXX
		, hls::stream<DATA_TYPE>      &SumXY
		, u32            n
) ;

void lr(
		  DATA_TYPE    *memory_0
		, DATA_TYPE    *memory_1
		, DATA_TYPE    *memory_2
		, DATA_TYPE    *memory_3
		, u32           in_X
		, u32           in_Y
		, DATA_TYPE     &a0
		, DATA_TYPE     &a1
		, u32            n) {
#pragma HLS INTERFACE s_axilite port=return bundle=control_bus
#pragma HLS INTERFACE s_axilite port=in_X   bundle=control_bus
#pragma HLS INTERFACE s_axilite port=in_Y   bundle=control_bus
#pragma HLS INTERFACE s_axilite port=a0     bundle=control_bus
#pragma HLS INTERFACE s_axilite port=a1     bundle=control_bus
#pragma HLS INTERFACE s_axilite port=n      bundle=control_bus
#pragma HLS INTERFACE m_axi port=memory_0
#pragma HLS INTERFACE m_axi port=memory_1
#pragma HLS INTERFACE m_axi port=memory_2
#pragma HLS INTERFACE m_axi port=memory_3
#pragma HLS DATAFLOW

	hls::stream<DATA_TYPE>  SumX_0;
	hls::stream<DATA_TYPE>  SumY_0;
	hls::stream<DATA_TYPE>  SumXX_0;
	hls::stream<DATA_TYPE>  SumXY_0;


	hls::stream<DATA_TYPE>  SumX_1;
	hls::stream<DATA_TYPE>  SumY_1;
	hls::stream<DATA_TYPE>  SumXX_1;
	hls::stream<DATA_TYPE>  SumXY_1;


	DATA_TYPE SumX  = 0;
	DATA_TYPE SumY  = 0;
	DATA_TYPE SumXX = 0;
	DATA_TYPE SumXY = 0;

	lr_kernel(memory_0, memory_1, in_X + 0,   in_Y + 0,   SumX_0, SumY_0, SumXX_0, SumXY_0, n/2);
	lr_kernel(memory_2, memory_3, in_X + n/2, in_Y + n/2, SumX_1, SumY_1, SumXX_1, SumXY_1, n/2);

	SumX  = SumX_0.read()  + SumX_1.read();
	SumY  = SumY_0.read()  + SumY_1.read();
	SumXX = SumXX_0.read() + SumXX_1.read();
	SumXY = SumXY_0.read() + SumXY_1.read();

	//write back data
	a0 = (SumY*SumXX - SumX*SumXY)/(n*SumXX-SumX*SumX);
	a1 = (n*SumXY-SumX*SumY)/(n*SumXX-SumX*SumX);

}

inline void lr_kernel(
		  DATA_TYPE    *memory_0
		, DATA_TYPE    *memory_1
		, u32           in_X
		, u32           in_Y
		, hls::stream<DATA_TYPE>      &SumX
		, hls::stream<DATA_TYPE>      &SumY
		, hls::stream<DATA_TYPE>      &SumXX
		, hls::stream<DATA_TYPE>      &SumXY
		, u32            n
) {

#pragma HLS DATAFLOW

	DATA_TYPE SumX_local  = 0;
	DATA_TYPE SumY_local  = 0;
	DATA_TYPE SumXX_local = 0;
	DATA_TYPE SumXY_local = 0;

	DATA_TYPE cX_local  = 0;
	DATA_TYPE cY_local  = 0;
	DATA_TYPE cXX_local = 0;
	DATA_TYPE cXY_local = 0;

	DATA_TYPE  t, y;



	hls::stream<DATA_TYPE> input_X_fifo;
	hls::stream<DATA_TYPE> input_Y_fifo;



	//receive data
	receive_data_loop : for (int i = 0; i < n; i++) {
#pragma HLS PIPELINE
		input_X_fifo << *(memory_0 + in_X + i);
		input_Y_fifo << *(memory_1 + in_Y + i);
	}

	//computation
	computaion_loop_1 : for (int i = 0; i < n/(B); i++) {
#pragma HLS PIPELINE
		DATA_TYPE X[B];
		DATA_TYPE Y[B];
		for (int j = 0; j < B; j++) {
#pragma HLS UNROLL
			X[j] = input_X_fifo.read();
			Y[j] = input_Y_fifo.read();
		}
		DATA_TYPE SumX_tmp = 0;
		DATA_TYPE SumY_tmp = 0;
		DATA_TYPE SumXX_tmp = 0;
		DATA_TYPE SumXY_tmp = 0;
		int j = 0;
		for (j = 0; j < B; j++) {
#pragma HLS UNROLL
			SumX_tmp   += X[j];
			SumY_tmp   += Y[j];
			SumXX_tmp  += X[j]*X[j];
			SumXY_tmp  += X[j]*Y[j];
		}

		SumX_local  += SumX_tmp;
		SumY_local  += SumY_tmp;
		SumXX_local += SumXX_tmp;
		SumXY_local += SumXY_tmp;

	}


	SumX  << SumX_local;
	SumY  << SumY_local;
	SumXX << SumXX_local;
	SumXY << SumXY_local;
}
