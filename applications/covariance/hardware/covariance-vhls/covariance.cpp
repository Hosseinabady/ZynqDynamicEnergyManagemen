#include <string.h>
#include <hls_stream.h>
#include "covariance.h"

#define NUMBER_OF_THREAD 1
inline void accumulate_column(DATA_TYPE* memory_1, u32 data_offset, DATA_TYPE data_matrix[N][M], DATA_TYPE float_n, DATA_TYPE* mean);
inline void cov(DATA_TYPE data_matrix[N][M], DATA_TYPE cov_matrix[M][M], u32 n, u32 m, DATA_TYPE *mean );


void covariance(
		DATA_TYPE* memory_1,

		u32 data_offset,
		u32 cov_offset,
		u32 n,
		u32 m) {

#pragma HLS INTERFACE s_axilite port=return bundle=control_bus
#pragma HLS INTERFACE m_axi  port=memory_1

#pragma HLS INTERFACE s_axilite port=data_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=cov_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=n bundle=control_bus
#pragma HLS INTERFACE s_axilite port=m bundle=control_bus



	n=N;
	m=M;


    float float_n_tmp=1.0*n;
    float tmp;
	int i, j, k;

	DATA_TYPE float_n = 1.0*n;
	DATA_TYPE  mean[M/NUMBER_OF_THREAD];


	DATA_TYPE cov_matrix[M][M];
#pragma HLS ARRAY_PARTITION variable=cov_matrix cyclic factor=64 dim=1
	DATA_TYPE data_matrix[N][M];


	accumulate_column(memory_1, data_offset, data_matrix, float_n, mean);
	cov(data_matrix, cov_matrix, n, m, mean);


	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
#pragma HLS PIPELINE
			*(memory_1+cov_offset+i*m+j) = cov_matrix[i][j]/(float_n-1);
		}
	}

}




inline void cov(DATA_TYPE data_matrix[N][M], DATA_TYPE cov_matrix[M][M], u32 n, u32 m, DATA_TYPE* mean) {



	DATA_TYPE data_buffer[M];
#pragma HLS ARRAY_PARTITION variable=data_buffer complete dim=1

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
#pragma HLS PIPELINE
			for (int k = 0; k < M; k++) {
				if (i==0)
					cov_matrix[k][j] = 0;

				if (k==0)
					data_buffer[j] = data_matrix[i][j]-mean[j];
				cov_matrix[k][j]  += data_buffer[j]*data_buffer[k];

			}
		}
	}


}


inline void accumulate_column(DATA_TYPE* memory_1, u32 data_offset,  DATA_TYPE data_matrix[N][M], DATA_TYPE float_n, DATA_TYPE* mean) {

#pragma HLS DATAFLOW

	hls::stream<DATA_TYPE> data_i_j_fifo;
	DATA_TYPE  mean_tmp[M/NUMBER_OF_THREAD];
	hls::stream<DATA_TYPE> means_fifo;


	DATA_TYPE  tmp;

	LOOP0:for (int i = 0; i < N; i++) {
		LOOP1:for (int j = 0; j < M/NUMBER_OF_THREAD; j++) {
#pragma HLS PIPELINE
			DATA_TYPE tmp = *(memory_1+data_offset+(i+0)*M+j);
			data_i_j_fifo << tmp;
			data_matrix[i][j] = tmp;
		}
	}

	LOOP2: for (int i = 0; i < N; i++) {
		LOOP3: for (int j = 0; j < M/NUMBER_OF_THREAD; j++) {
#pragma HLS PIPELINE
	    	DATA_TYPE d = data_i_j_fifo.read();
	    	if (i == 0)
	    		mean_tmp[j] = d;
	    	else
	    		mean_tmp[j] += d;

	    	if (i == N-1) {
	    		means_fifo << mean_tmp[j];
	    	}
	    }
	}

		LOOP4: for (int i = 0; i < M/NUMBER_OF_THREAD; i++) {
	#pragma HLS PIPELINE
			DATA_TYPE mean_tmp_1 = means_fifo.read();

			mean_tmp_1 /= float_n;
			mean[0*M/NUMBER_OF_THREAD+i] =  mean_tmp_1; //;

		}

}

