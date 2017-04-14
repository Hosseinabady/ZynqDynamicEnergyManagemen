#include "pr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void pr_init( float *tXBuf,  float *tYBuf)
{

  int i, j;

  for (i = 0; i < DATA_LENGTH; i++) {
	  tXBuf[i] = (1.0*i)/(DATA_LENGTH);
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
		bool* resultValid ) {

	//compute detA
	float detA = determinant3By3((float)N, sumX, sumXX,
			sumX, sumXX, sumXXX,
			sumXX, sumXXX, sumXXXX);
	if( 0.f == detA) {
		*resultValid = false;
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
	bool result = true;
	findParabola(pA0, pA1, pA2, N, sumX,sumXX,sumXXX,sumXXXX,sumY,
	sumXY, sumXXY, &result);
	}


void pr_hardware(
		    u32        N,
			DATA_TYPE* pX,
			DATA_TYPE* pY,
			DATA_TYPE* pA0,
			DATA_TYPE* pA1,
			DATA_TYPE* pA2)
{

	DATA_TYPE    *memory = 0;

	int resultValid = 0;

	u32    px_offset_address = (u32)(pX)/4;
	u32    py_offset_address = (u32)(pY)/4;


	pr(memory, memory, memory, memory, px_offset_address, py_offset_address, *pA0, *pA1, *pA2, N, resultValid);

}



int main() {


	DATA_TYPE *X = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));
	DATA_TYPE *Y = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));

	pr_init(X, Y);

	DATA_TYPE  a0_sw;
	DATA_TYPE  a1_sw;
	DATA_TYPE  a2_sw;

	DATA_TYPE  a0_hw;
	DATA_TYPE  a1_hw;
	DATA_TYPE  a2_hw;

	pr_software(DATA_LENGTH, X, Y, &a0_sw, &a1_sw, &a2_sw);

	pr_hardware(DATA_LENGTH, X, Y, &a0_hw, &a1_hw, &a2_hw);



	float diff_0 = fabs(a0_hw - a0_sw);
	float diff_1 = fabs(a1_hw - a1_sw);
	float diff_2 = fabs(a2_hw - a2_sw);
	if( (diff_0 > 0.1 || diff_0 != diff_0)
	 || (diff_1 > 0.1 || diff_1 != diff_1)
	 || (diff_2 > 0.1 || diff_2 != diff_2))
	{
		printf("Error\n");
		printf("a0_sw=%f != a0_hw=%f , a1_sw=%f != a1_hw=%f , a2_sw=%f != a2_hw=%f \n", a0_sw, a0_hw, a1_sw, a1_hw, a2_sw, a2_hw);
		return -1;
	}
	printf("OK  a0_sw=%f != a0_hw=%f , a1_sw=%f != a1_hw=%f , a2_sw=%f != a2_hw=%f \n", a0_sw, a0_hw, a1_sw, a1_hw, a2_sw, a2_hw);

	return 0;
}

