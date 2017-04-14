
#include "pr.h"
#include <string.h>
#include <hls_stream.h>

void pr_kernel(DATA_TYPE * memory_0,
		DATA_TYPE * memory_1,
		u32 in_X_offset,
        u32 in_Y_offset,
		hls::stream<DATA_TYPE> &SumX,
		hls::stream<DATA_TYPE> &SumY,
		hls::stream<DATA_TYPE> &SumXX,
		hls::stream<DATA_TYPE> &SumXY,
		hls::stream<DATA_TYPE> &SumXXY,
		hls::stream<DATA_TYPE> &SumXXX,
		hls::stream<DATA_TYPE> &SumXXXX,
		u32                     n);

float determinant3x3( float a1,
                      float b1,
                      float c1,
                      float a2,
                      float b2,
                      float c2,
                      float a3,
                      float b3,
                      float c3 );


#define B 8



void pr(DATA_TYPE * memory_0,
		DATA_TYPE * memory_1,
		DATA_TYPE * memory_2,
		DATA_TYPE * memory_3,
		u32 in_X_offset,
        u32 in_Y_offset,
        float &a0,
        float &a1,
		float &a2,
		u32    n,
		int   &resultValid
	) {

#pragma HLS INTERFACE m_axi port=memory_0
#pragma HLS INTERFACE m_axi port=memory_1
#pragma HLS INTERFACE m_axi port=memory_2
#pragma HLS INTERFACE m_axi port=memory_3
#pragma HLS INTERFACE s_axilite port=return bundle=control_bus
#pragma HLS INTERFACE s_axilite port=in_X_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=in_Y_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=a0 bundle=control_bus
#pragma HLS INTERFACE s_axilite port=a1 bundle=control_bus
#pragma HLS INTERFACE s_axilite port=a2 bundle=control_bus
#pragma HLS INTERFACE s_axilite port=n bundle=control_bus
#pragma HLS INTERFACE s_axilite port=resultValid bundle=control_bus




	DATA_TYPE SumX  = 0;
	DATA_TYPE SumY  = 0;
	DATA_TYPE SumXX = 0;
	DATA_TYPE SumXY = 0;
	DATA_TYPE SumXXY = 0;
	DATA_TYPE SumXXX = 0;
	DATA_TYPE SumXXXX = 0;

	hls::stream<DATA_TYPE> SumX_0;
	hls::stream<DATA_TYPE> SumY_0;
	hls::stream<DATA_TYPE> SumXX_0;
	hls::stream<DATA_TYPE> SumXY_0;
	hls::stream<DATA_TYPE> SumXXY_0;
	hls::stream<DATA_TYPE> SumXXX_0;
	hls::stream<DATA_TYPE> SumXXXX_0;

	hls::stream<DATA_TYPE> SumX_1;
	hls::stream<DATA_TYPE> SumY_1;
	hls::stream<DATA_TYPE> SumXX_1;
	hls::stream<DATA_TYPE> SumXY_1;
	hls::stream<DATA_TYPE> SumXXY_1;
	hls::stream<DATA_TYPE> SumXXX_1;
	hls::stream<DATA_TYPE> SumXXXX_1;


	pr_kernel(memory_0, memory_1, in_X_offset + 0,   in_Y_offset + 0,   SumX_0, SumY_0, SumXX_0, SumXY_0, SumXXY_0, SumXXX_0, SumXXXX_0, n/2);
	pr_kernel(memory_2, memory_3, in_X_offset + n/2, in_Y_offset + n/2, SumX_1, SumY_1, SumXX_1, SumXY_1, SumXXY_1, SumXXX_1, SumXXXX_1, n/2);



	SumX    = SumX_0.read()    + SumX_1.read();
	SumY    = SumY_0.read()    + SumY_1.read();
	SumXX   = SumXX_0.read()   + SumXX_1.read();
	SumXY   = SumXY_0.read()   + SumXY_1.read();
	SumXXY  = SumXXY_0.read()  + SumXXY_1.read();
	SumXXX  = SumXXX_0.read()  + SumXXX_1.read();
	SumXXXX = SumXXXX_0.read() + SumXXXX_1.read();

	{
		float detA = determinant3x3((float)n, SumX, SumXX, SumX, SumXX, SumXXX, SumXX, SumXXX, SumXXXX);
		if(detA == 0) {
			resultValid = 0;
			return;
		}

		float detA0 = determinant3x3(SumY, SumX,   SumXX,  SumXY,    SumXX,  SumXXX, SumXXY,  SumXXX, SumXXXX);

		float detA1 = determinant3x3((float)n, SumY,   SumXX, SumX,    SumXY,  SumXXX, SumXX,   SumXXY, SumXXXX);

		float detA2 = determinant3x3((float)n, SumX,   SumY, SumX,    SumXX,  SumXY, SumXX,   SumXXX, SumXXY);


		a0 = detA0/detA;
		a1 = detA1/detA;
		a2 = detA2/detA;

	}
}


void pr_kernel(DATA_TYPE * memory_0,
		DATA_TYPE * memory_1,
		u32 in_X_offset,
        u32 in_Y_offset,
		hls::stream<DATA_TYPE> &SumX,
		hls::stream<DATA_TYPE> &SumY,
		hls::stream<DATA_TYPE> &SumXX,
		hls::stream<DATA_TYPE> &SumXY,
		hls::stream<DATA_TYPE> &SumXXY,
		hls::stream<DATA_TYPE> &SumXXX,
		hls::stream<DATA_TYPE> &SumXXXX,
		u32                     n)
	 {



#pragma HLS DATAFLOW

	DATA_TYPE SumX_local  = 0;
	DATA_TYPE SumY_local  = 0;
	DATA_TYPE SumXX_local = 0;
	DATA_TYPE SumXY_local = 0;
	DATA_TYPE SumXXY_local = 0;
	DATA_TYPE SumXXX_local = 0;
	DATA_TYPE SumXXXX_local = 0;


	hls::stream<DATA_TYPE> input_X_fifo;
	hls::stream<DATA_TYPE> input_Y_fifo;

#pragma HLS STREAM variable=input_X_fifo depth=32
#pragma HLS STREAM variable=input_Y_fifo depth=32


	//receive data
	receive_data_loop : for (int i = 0; i < n; i++) {
#pragma HLS PIPELINE
		input_X_fifo << *(memory_0 + in_X_offset + i);
		input_Y_fifo << *(memory_1 + in_Y_offset + i);

	}


	//computation
	computaion_loop_1 : for (int i = 0; i < n/(B); i++) {
#pragma HLS PIPELINE
		float X[B];
		float Y[B];
		for (int j = 0; j < B; j++) {
#pragma HLS UNROLL
			X[j] = input_X_fifo.read();
			Y[j] = input_Y_fifo.read();
		}
		float SumX_tmp = 0;
		float SumY_tmp = 0;
		float SumXX_tmp = 0;
		float SumXY_tmp = 0;
		float SumXXY_tmp = 0;
		float SumXXX_tmp = 0;
		float SumXXXX_tmp = 0;

		int j = 0;
		for (j = 0; j < B; j++) {
#pragma HLS UNROLL
			SumX_tmp     += X[j];
			SumY_tmp     += Y[j];
			float XX      = X[j]*X[j];
			SumXX_tmp    += XX;
			SumXY_tmp    += X[j]*Y[j];
			SumXXY_tmp   += XX*Y[j];
			SumXXX_tmp   += XX*X[j];
			SumXXXX_tmp  += XX*XX;
		}

		SumX_local    += SumX_tmp;
		SumY_local    += SumY_tmp;
		SumXX_local   += SumXX_tmp;
		SumXY_local   += SumXY_tmp;
		SumXXY_local  += SumXXY_tmp;
		SumXXX_local  +=SumXXX_tmp;
		SumXXXX_local += SumXXXX_tmp;
	}
	//write back data

	SumX << SumX_local;
	SumY << SumY_local;
	SumXX << SumXX_local;
	SumXY << SumXY_local;
	SumXXY << SumXXY_local;
	SumXXX << SumXXX_local;
	SumXXXX << SumXXXX_local;


}



float determinant3x3(
                      float a1,
                      float b1,
                      float c1,
                      float a2,
                      float b2,
                      float c2,
                      float a3,
                      float b3,
                      float c3
                      )
{
    float det = a1*b2*c3 - a1*b3*c2;
    det += a3*b1*c2 - a2*b1*c3;
    det += a2*b3*c1 - a3*b2*c1;
    return det;
}
