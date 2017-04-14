
# include <omp.h>
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "BlackScholes.h"
void BlackScholesCPU_openmp_neon(
    float *h_Call, //Call option price
    float *h_Put,  //Put option price
    float *h_S,    //Current stock price
    float *h_X,    //Option strike price
    float *h_T,    //Option years
    float R,       //Riskless rate of return
    float V,       //Stock volatility
    unsigned int optionCount
);

static void BlackScholesBodyCPU(
    float *call, //Call option price
    float *put,  //Put option price
    float Sf,    //Current stock price
    float Xf,    //Option strike price
    float Tf,    //Option years
    float Rf,    //Riskless rate of return
    float Vf     //Stock volatility
);

double getTimestamp();


float randFloat(float low, float high){
    float t = (float)rand() / (float)RAND_MAX;
    return (1.0f - t) * low + t * high;
}



#define SOFTWARE_ITERATION 10

int main(int argc, char **argv) {
	float	*h_CallCPU,
	        *h_PutCPU,
	        *h_CallFPGA,
	        *h_PutFPGA,
	        *h_S,
	        *h_X,
	        *h_T,
			*h_SFPGA,
	        *h_XFPGA,
	        *h_TFPGA;


	int status;



	double software_start;
   	double software_end;
   	double software_execution_time;


	const unsigned int   optionCount = OPT_N;
	const float                    R = 0.02f;
	const float                    V = 0.30f;

	h_CallCPU = (float *)malloc(optionCount * sizeof(float));
	h_PutCPU = (float *)malloc(optionCount * sizeof(float));

	float	*memory = (float *)malloc(5*optionCount * sizeof(float));
	float	*h_CallFPGA_results = memory + 0 * optionCount;
	float	*h_PutFPGA_results  = memory + 1 * optionCount;
	h_S                = memory + 2 * optionCount;
	h_X                = memory + 3 * optionCount;
	h_T                = memory + 4 * optionCount;


	srand(time(NULL));
	for(unsigned int i = 0; i < optionCount; i++){
		h_CallCPU[i]  = -1.0f;
	    h_PutCPU[i]   = -1.0f;
	    h_S[i]        = randFloat(5.0f, 30.0f);
	    h_X[i]        = randFloat(1.0f, 100.0f);
	    h_T[i]        = randFloat(0.25f, 10.0f);
	}


	software_start = getTimestamp();
	for (int i = 0; i < SOFTWARE_ITERATION; i++) {
		BlackScholesCPU_openmp_neon(h_CallCPU, h_PutCPU, h_S, h_X, h_T, R, V, optionCount);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
	printf("parallel openmp-neon software execution time  %.6lf ms elapsed\n", software_execution_time);


	if(DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("loop for manual power monitoring!\n");
		software_start = getTimestamp();
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				BlackScholesCPU_openmp_neon(h_CallCPU, h_PutCPU, h_S, h_X, h_T, R, V, optionCount);
			}
		}
		software_end = getTimestamp();
		software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
		printf("parallel openmp-neon software execution time  %.6lf ms elapsed\n", software_execution_time);
	}



	free(h_CallCPU);
	free(h_PutCPU);
	free(memory);


	return 0;
}







double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}

///////////////////////////////////////////////////////////////////////////////
// Rational approximation of cumulative normal distribution function
///////////////////////////////////////////////////////////////////////////////
static double CND(double d){
    const double       A1 = 0.31938153;
    const double       A2 = -0.356563782;
    const double       A3 = 1.781477937;
    const double       A4 = -1.821255978;
    const double       A5 = 1.330274429;
    const double RSQRT2PI = 0.39894228040143267793994605993438;

    double
        K = 1.0 / (1.0 + 0.2316419 * fabs(d));

    double
        cnd = RSQRT2PI * exp(- 0.5 * d * d) *
        (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

    if(d > 0)
        cnd = 1.0 - cnd;

    return cnd;
}

///////////////////////////////////////////////////////////////////////////////
// Black-Scholes formula for both call and put
///////////////////////////////////////////////////////////////////////////////
static void BlackScholesBodyCPU(
    float *call, //Call option price
    float *put,  //Put option price
    float Sf,    //Current stock price
    float Xf,    //Option strike price
    float Tf,    //Option years
    float Rf,    //Riskless rate of return
    float Vf     //Stock volatility
){
    double S = Sf, X = Xf, T = Tf, R = Rf, V = Vf;

    double sqrtT = sqrt(T);
    double    d1 = (log(S / X) + (R + 0.5 * V * V) * T) / (V * sqrtT);
    double    d2 = d1 - V * sqrtT;
    double CNDD1 = CND(d1);
    double CNDD2 = CND(d2);

    //Calculate Call and Put simultaneously
    double expRT = exp(- R * T);
    *call = (float)(S * CNDD1 - X * expRT * CNDD2);
    *put  = (float)(X * expRT * (1.0 - CNDD2) - S * (1.0 - CNDD1));
}

////////////////////////////////////////////////////////////////////////////////
// Process an array of optN options
////////////////////////////////////////////////////////////////////////////////






void BlackScholesCPU_openmp_neon(
    float *h_Call, //Call option price
    float *h_Put,  //Put option price
    float *h_S,    //Current stock price
    float *h_X,    //Option strike price
    float *h_T,    //Option years
    float R,       //Riskless rate of return
    float V,       //Stock volatility
    unsigned int optionCount
){
# pragma omp parallel
# pragma omp for
    for(unsigned int i = 0; i < optionCount; i++)
        BlackScholesBodyCPU(
            &h_Call[i],
            &h_Put[i],
            h_S[i],
            h_X[i],
            h_T[i],
            R,
            V
        );
}
