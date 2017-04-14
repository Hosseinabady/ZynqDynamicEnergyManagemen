#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pr.h>
#include <sys/time.h>
#include <time.h>



double software_start;
double software_end;
double software_execution_time;

double getTimestamp();

#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM 10

void pr_init( float *tXBuf,  float *tYBuf)
{

  int i, j;

  for (i = 0; i < DATA_LENGTH; i++) {
	  tXBuf[i] = (1.0*i)/DATA_LENGTH;
  }
  for (i = 0; i < DATA_LENGTH; i++) {
	  tYBuf[i ] = (3.56*(tXBuf[i]*tXBuf[i])+1.23*(tXBuf[i])+2.5);
  }

}


float determinant3By3(	float a1, float b1, float c1,
						float a2, float b2, float c2,
						float a3, float b3, float c3 ) {
	float det = a1*b2*c3 - a1*b3*c2;
	det += a3*b1*c2 - a2*b1*c3;
	det += a2*b3*c1 - a3*b2*c1;
	return det;
}


void findParabola(
		//Output parameters
		float* pA0,
		float* pA1,
		float* pA2,
		//Input parameters
		int N,
		float sumX,
		float sumXX,
		float sumXXX,
		float sumXXXX,
		float sumY,

		float sumXY,
		float sumXXY,
		int* resultValid ) {

	//compute detA
	float detA = determinant3By3((float)N, sumX, sumXX,
			sumX, sumXX, sumXXX,
			sumXX, sumXXX, sumXXXX);
	if( 0.f == detA) {
		*resultValid = 0;
		return;
	}

	float detA0 = determinant3By3(sumY, sumX, sumXX,
			sumXY, sumXX, sumXXX,
			sumXXY, sumXXX, sumXXXX);
	float detA1 = determinant3By3((float)N, sumY, sumXX,
			sumX, sumXY, sumXXX,
			sumXX, sumXXY, sumXXXX);
	float detA2 = determinant3By3((float)N, sumX, sumY,
			sumX, sumXX, sumXY,
			sumXX, sumXXX, sumXXY);
	*pA0 = detA0/detA;
	*pA1 = detA1/detA;
	*pA2 = detA2/detA;
}



void pr_software(
		size_t N,
		float* pX,
		float* pY,
		float* pA0,
		float* pA1,
		float* pA2) {

	float sumX = 0.f;
	float sumY = 0.f;
	float sumXY = 0.f;
	float sumXX = 0.f;
	float sumXXY = 0.f;
	float sumXXX = 0.f;
	float sumXXXX = 0.f;
	float cX = 0.f;
	float cY = 0.f;
	float cXY = 0.f;
	float cXX = 0.f;
	float cXXY = 0.f;
	float cXXX = 0.f;
	float cXXXX = 0.f;



	float XX = 0.f;
	float XXX = 0.f;

	DATA_TYPE y, t;
#pragma omp parallel for reduction(+:sumX, sumY, sumXY, sumXX, sumXXY, sumXXX, sumXXXX, cX,   cY,   cXY,   cXX,   cXXY,   cXXX,   cXXXX, t, y)
	for(int i=0; i < N; ++i) {
		y = *(pX+i) - cX;
		t = sumX + y;
		cX = (t - sumX) - y;
		sumX = t ;


		y = *(pY+i) - cY;
		t = sumY + y;
		cY = (t - sumY) - y;
		sumY = t ;


		y = ( *(pX+i) )*( *(pY+i)) - cXY;
		t = sumXY + y;
		cXY = (t - sumXY) - y;
		sumXY = t ;


		XX = ( *(pX+i) )*( *(pX+i)) ;
		XXX = ( *(pX+i) ) * ( *(pX+i) )*( *(pX+i)) ;

		y = XX * *(pY+i) - cXXY;
		t = sumXXY + y;
		cXXY = (t - sumXXY) - y;
		sumXXY = t ;


		y = XX - cXX;
		t = sumXX + y;
		cXX = (t - sumXX) - y;
		sumXX = t ;

		y = ( *(pX+i) )*XX - cXXX;
		t = sumXXX + y;
		cXXX = (t - sumXXX) - y;
		sumXXX = t ;

		y = XX*XX - cXXXX;
		t = sumXXXX + y;
		cXXXX = (t - sumXXXX) - y;
		sumXXXX = t ;


//		sumX += *(pX+i); // *(pX+i) is same as pX[i] in meaning
//		sumY += *(pY+i);
//		sumXY += ( *(pX+i) )*( *(pY+i)) ;
//		sumXXY   += XX * *(pY+i);
//		sumXX += XX;
//		sumXXX += ( *(pX+i) )*XX ;
//		sumXXXX += XX*XX;
	}

	//compute *pA0, *pA1, *pA2
	int result = 1;
	findParabola(pA0, pA1, pA2, N, sumX,sumXX,sumXXX,sumXXXX,sumY,
	sumXY, sumXXY, &result);
	}





int main() {


	DATA_TYPE *X_sw = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));
	DATA_TYPE *Y_sw = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));

	DATA_TYPE *X_hw;
	DATA_TYPE *Y_hw;

	pr_init(X_sw, Y_sw);

	DATA_TYPE  a0_sw;
	DATA_TYPE  a1_sw;
	DATA_TYPE  a2_sw;


	software_start = getTimestamp();
	for (int i = 0; i < EXE_TIME_MONITORING_ITERATION_NUM; i++) {
		pr_software(DATA_LENGTH, X_sw, Y_sw, &a0_sw, &a1_sw, &a2_sw);
	}

	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);


	printf("a0_sw=%f, a1_sw=%f, a2_sw=%f\n", a0_sw, a1_sw, a2_sw);



	if(DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("huge number of iteration for manual monitoring\n");
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				pr_software(DATA_LENGTH, X_sw, Y_sw, &a0_sw, &a1_sw, &a2_sw);
			}
		}
	}
	printf("a0_sw=%f, a1_sw=%f, a2_sw=%f\n", a0_sw, a1_sw, a2_sw);

	free(X_sw);
	free(Y_sw);

	return 0;
}



double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}
