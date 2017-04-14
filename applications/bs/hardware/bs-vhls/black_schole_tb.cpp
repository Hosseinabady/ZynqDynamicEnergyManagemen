
#include "black_schole.h"
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>
#include <math.h>
#include <time.h>

extern "C" void BlackScholesCPU(
    float *h_Call, //Call option price
    float *h_Put,  //Put option price
    float *h_S,    //Current stock price
    float *h_X,    //Option strike price
    float *h_T,    //Option years
    float R,       //Riskless rate of return
    float V,       //Stock volatility
    unsigned int optionCount
);


int validate(float* data_sw, float* data_hw, int optionCount) {
	int i;

	for (i = 0; i < optionCount; i++) {
		float hw = data_hw[i];
		float sw = data_sw[i];

		float diff = fabs(hw - sw);
		if(diff > 0.001 || diff != diff){
			printf("Error in out_data at c_hw[%d] = %f != c_sw[%d] = %f\n", i, hw, i,  sw);
		}
	}
	return 0;
}

float randFloat(float low, float high){
    float t = (float)rand() / (float)RAND_MAX;
    return (1.0f - t) * low + t * high;
}

int main(int argc, char **argv) {
	float	*h_CallCPU,
	        *h_PutCPU,
	        *h_CallFPGA,
	        *h_PutFPGA,
	        *h_S,
	        *h_X,
	        *h_T;


	const unsigned int   optionCount = OPT_N;
	const float                    R = 0.02f;
	const float                    V = 0.30f;

	h_CallCPU = (float *)malloc(optionCount * sizeof(float));
	h_PutCPU = (float *)malloc(optionCount * sizeof(float));

	float	*memory = (float *)malloc(5*optionCount * sizeof(float));
	h_CallFPGA = memory + 0 * optionCount;
	h_PutFPGA  = memory + 1 * optionCount;
	h_S        = memory + 2 * optionCount;
	h_X        = memory + 3 * optionCount;
	h_T        = memory + 4 * optionCount;

	srand(time(NULL));
	for(unsigned int i = 0; i < optionCount; i++){
		h_CallCPU[i]  = -1.0f;
	    h_PutCPU[i]   = -1.0f;
		h_CallFPGA[i] = -1.0f;
	    h_PutFPGA[i]  = -1.0f;
	    h_S[i]        = randFloat(5.0f, 30.0f);
	    h_X[i]        = randFloat(1.0f, 100.0f);
	    h_T[i]        = randFloat(0.25f, 10.0f);
	}


	bs_stream (memory, memory, memory, memory, memory,  0 * optionCount, 1 * optionCount, 2 * optionCount, 3 * optionCount, 4 * optionCount);


	BlackScholesCPU(h_CallCPU, h_PutCPU, h_S, h_X, h_T, R, V, optionCount);

	int status = validate(h_CallCPU, h_CallFPGA, optionCount);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
		printf("Validation FAILED!\n");
	}

	return 0;
}







