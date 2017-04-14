#include "lr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void lr_init( DATA_TYPE *tXBuf,  DATA_TYPE *tYBuf)
{

  int i, j;

  for (i = 0; i < DATA_LENGTH; i++) {
	  tXBuf[i] = (1.0*i)/DATA_LENGTH;
  }
  for (i = 0; i < DATA_LENGTH; i++) {
	  tYBuf[i ] = (1.23*((1.0*i)/DATA_LENGTH)+2.5);
  }

}


void lr_software(DATA_TYPE *tXBuf,  DATA_TYPE *tYBuf, DATA_TYPE &a0SW, DATA_TYPE  &a1SW)
		{
			DATA_TYPE sumX  =0;
			DATA_TYPE sumY  =0;
			DATA_TYPE sumXY =0;
			DATA_TYPE sumXX =0;

			DATA_TYPE cX  =0;
			DATA_TYPE cY  =0;
			DATA_TYPE cXY =0;
			DATA_TYPE cXX =0;

			DATA_TYPE y, t;
			for (int i = 0; i < DATA_LENGTH; i++) {

//				sumX  += *(tXBuf+i);
//				sumY  += *(tYBuf+i);
//				sumXY += (*(tXBuf+i)) * (*(tYBuf+i));
//				sumXX += (*(tXBuf+i)) * (*(tXBuf+i));


				y = *(tXBuf+i) - cX;
				t = sumX + y;
				cX = (t - sumX) - y;
				sumX = t ;

				y = *(tYBuf+i) - cY;
				t = sumY + y;
				cY = (t - sumY) - y;
				sumY = t ;

				y = (*(tXBuf+i)) * (*(tYBuf+i)) - cXY;
				t = sumXY + y;
				cXY = (t - sumXY) - y;
				sumXY = t ;

				y = (*(tXBuf+i)) * (*(tXBuf+i)) - cXX;
				t = sumXX + y;
				cXX = (t - sumXX) - y;
				sumXX = t ;


			}

			a0SW = (sumY*sumXX - sumX*sumXY)/(DATA_LENGTH*sumXX-sumX*sumX);
			a1SW = (DATA_LENGTH*sumXY-sumX*sumY)/(DATA_LENGTH*sumXX-sumX*sumX);

		}

void lr_hardware(
		    u32        N,
			DATA_TYPE* pX,
			DATA_TYPE* pY,
			DATA_TYPE* pA0,
			DATA_TYPE* pA1)
{

	DATA_TYPE    *memory = 0;


	u32    px_offset_address = (u32)(pX)/sizeof(DATA_TYPE);
	u32    py_offset_address = (u32)(pY)/sizeof(DATA_TYPE);

	lr(memory, memory, memory, memory, px_offset_address, py_offset_address, *pA0, *pA1, N);

}



int main() {


	DATA_TYPE *X = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));
	DATA_TYPE *Y = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));

	lr_init(X, Y);

	DATA_TYPE  a0_sw;
	DATA_TYPE  a1_sw;

	DATA_TYPE  a0_hw;
	DATA_TYPE  a1_hw;

	lr_software( X, Y, a0_sw, a1_sw);

	lr_hardware(DATA_LENGTH, X, Y, &a0_hw, &a1_hw);



	DATA_TYPE diff_0 = fabs(a0_hw - a0_sw);
	DATA_TYPE diff_1 = fabs(a1_hw - a1_sw);
	if( (diff_0 > 0.1 || diff_0 != diff_0)
	 || (diff_1 > 0.1 || diff_1 != diff_1))
	{
		printf("Error\n");
		printf("a0_sw=%f != a0_hw=%f , a1_sw=%f != a1_hw=%f\n", a0_sw, a0_hw, a1_sw, a1_hw);
		return -1;
	}

	printf("OK  a0_sw=%f != a0_hw=%f , a1_sw=%f != a1_hw=%f\n", a0_sw, a0_hw, a1_sw, a1_hw);
	return 0;
}



