#include "black_schole.h"

#include <hls_math.h>
#include <string.h>
#include <hls_stream.h>

	const float                    R = 0.02f;
	const float                    V = 0.30f;


#if(0)
    #define EXP(a) native_exp(a)
    #define LOG(a) native_log(a)
    #define SQRT(a) native_sqrt(a)
#else
//    #define EXP(a)  hls::exp(a)
//    #define LOG(a)  hls::log(a)
//    #define SQRT(a) hls::sqrt(a)
	#define EXP(a)  exp(a)
	#define LOG(a)  log(a)
	#define SQRT(a) sqrt(a)
#endif

inline DATA_TYPE CND(DATA_TYPE d);
inline void BlackScholesSDFG(
		 DATA_TYPE* memory_01,
				 DATA_TYPE* memory_02,
		         DATA_TYPE* memory_03,
		         DATA_TYPE* memory_04,
		         DATA_TYPE* memory_05,
				 u32 n,
				 u32 call_offset,
				 u32 put_offset,
				 u32 s_offset,
				 u32 x_offset,
				 u32 t_offset
		);

inline  void BlackScholesBody(

    DATA_TYPE *call, //Call option price
    DATA_TYPE *put,  //Put option price
    DATA_TYPE S,              //Current stock price
    DATA_TYPE X,              //Option strike price
    DATA_TYPE T              //Option years
//    DATA_TYPE R,              //Riskless rate of return
//    DATA_TYPE V               //Stock volatility
);




void bs_stream( DATA_TYPE* memory_01,
		 DATA_TYPE* memory_02,
         DATA_TYPE* memory_03,
         DATA_TYPE* memory_04,
         DATA_TYPE* memory_05,
		 u32 call_offset,
		 u32 put_offset,
		 u32 s_offset,
		 u32 x_offset,
		 u32 t_offset
		 ){
#pragma HLS INTERFACE s_axilite port=return      bundle=control_bus
#pragma HLS INTERFACE s_axilite port=call_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=put_offset  bundle=control_bus
#pragma HLS INTERFACE s_axilite port=s_offset    bundle=control_bus
#pragma HLS INTERFACE s_axilite port=x_offset    bundle=control_bus
#pragma HLS INTERFACE s_axilite port=t_offset    bundle=control_bus

#pragma HLS INTERFACE m_axi depth=16384 port=memory_01
#pragma HLS INTERFACE m_axi depth=16384 port=memory_02
#pragma HLS INTERFACE m_axi depth=16384 port=memory_03
#pragma HLS INTERFACE m_axi depth=16384 port=memory_04
#pragma HLS INTERFACE m_axi depth=16384 port=memory_05



#pragma HLS DATAFLOW
	hls::stream<DATA_TYPE> output_d_Call_fifo;
	hls::stream<DATA_TYPE> output_d_Put_fifo;
	hls::stream<DATA_TYPE> input_d_S_1_fifo;
	hls::stream<DATA_TYPE> input_d_X_1_fifo;
	hls::stream<DATA_TYPE> input_d_S_2_fifo;
	hls::stream<DATA_TYPE> input_d_X_2_fifo;
	hls::stream<DATA_TYPE> input_d_T_1_fifo;
	hls::stream<DATA_TYPE> input_d_T_2_fifo;
	hls::stream<DATA_TYPE> output_sqrt_fifo;


#pragma HLS STREAM variable=output_d_Call_fifo  dim=1
#pragma HLS STREAM variable=output_d_Put_fifo   dim=1
#pragma HLS STREAM variable=input_d_S_1_fifo      dim=1
#pragma HLS STREAM variable=input_d_X_1_fifo      dim=1
#pragma HLS STREAM variable=input_d_S_2_fifo      dim=1
#pragma HLS STREAM variable=input_d_X_2_fifo      dim=1
#pragma HLS STREAM variable=input_d_T_1_fifo    dim=1
#pragma HLS STREAM variable=input_d_T_2_fifo    dim=1
#pragma HLS STREAM variable=output_sqrt_fifo    dim=1


	LOOP_1: for ( int b = 0; b < OPT_N; b++) {
#pragma HLS PIPELINE
		input_d_S_1_fifo << *(memory_01+s_offset+b);
		input_d_X_1_fifo << *(memory_02+x_offset+b);
		input_d_T_1_fifo << *(memory_03+t_offset+b);
	}

	LOOP_3: for ( int b = 0; b < OPT_N; b++) {
#pragma HLS PIPELINE II=2
		DATA_TYPE d_S_local_1 = input_d_S_1_fifo.read();
		DATA_TYPE d_X_local_1 = input_d_X_1_fifo.read();
		DATA_TYPE d_T_local_1 = input_d_T_1_fifo.read();

		DATA_TYPE d_Call_local_1;
		DATA_TYPE d_Put_local_1;


		BlackScholesBody(&d_Call_local_1, &d_Put_local_1, d_S_local_1, d_X_local_1, d_T_local_1);//, R, V);

		output_d_Call_fifo << d_Call_local_1;
		output_d_Put_fifo  << d_Put_local_1;


	}
	LOOP_4: for ( int b = 0; b < OPT_N; b++) {
#pragma HLS PIPELINE
		*(memory_04+call_offset+b) = output_d_Call_fifo.read();
		*(memory_05+put_offset+b) = output_d_Put_fifo.read();
	}


}


inline void BlackScholesBody(

    DATA_TYPE *call, //Call option price
    DATA_TYPE *put,  //Put option price
    DATA_TYPE S,              //Current stock price
    DATA_TYPE X,              //Option strike price
    DATA_TYPE T              //Option years
//    DATA_TYPE R,              //Riskless rate of return
//    DATA_TYPE V               //Stock volatility
){

	DATA_TYPE sqrtT = SQRT(T);
    DATA_TYPE    d1 = (LOG(S / X) + (R + 0.5f * V * V) * T) / (V * sqrtT);
    DATA_TYPE    d2 = d1 - V * sqrtT;
    DATA_TYPE CNDD1 = CND(d1);
    DATA_TYPE CNDD2 = CND(d2);



    //Calculate Call and Put simultaneously
    DATA_TYPE expRT = EXP(- R * T);
    *call = (S * CNDD1 - X * expRT * CNDD2);
    *put  = (X * expRT * (1.0f - CNDD2) - S * (1.0f - CNDD1));

}



inline DATA_TYPE CND(DATA_TYPE d){
//#pragma HLS ALLOCATION instances=fmul limit=10 operation
    const DATA_TYPE       A1 = 0.31938153f;
    const DATA_TYPE       A2 = -0.356563782f;
    const DATA_TYPE       A3 = 1.781477937f;
    const DATA_TYPE       A4 = -1.821255978f;
    const DATA_TYPE       A5 = 1.330274429f;
    const DATA_TYPE RSQRT2PI = 0.39894228040143267793994605993438f;


    DATA_TYPE K;
    K = 1.0f / (1.0f + 0.2316419f * fabs(d));

    DATA_TYPE  cnd;
    cnd = RSQRT2PI * EXP(- 0.5f * d * d) *
        (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

    if(d > 0)
        cnd = 1.0f - cnd;

    return cnd;
}
