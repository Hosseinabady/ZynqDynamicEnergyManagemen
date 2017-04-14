# include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <lr.h>
#include <sys/time.h>
#include <time.h>



double software_start;
double software_end;
double software_execution_time;

double getTimestamp();

#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM 10

void lr_init( float *tXBuf,  float *tYBuf)
{

  int i, j;

  for (i = 0; i < DATA_LENGTH; i++) {
	  tXBuf[i] = (1.0*i)/DATA_LENGTH;
  }
  for (i = 0; i < DATA_LENGTH; i++) {
	  tYBuf[i ] = (1.23*((1.0*i)/DATA_LENGTH)+2.5);
  }

}


void lr_software(float *tXBuf,  float *tYBuf, float *a0SW, float  *a1SW)
		{
			float sumX  =0;
			float sumY  =0;
			float sumXY =0;
			float sumXX =0;

			DATA_TYPE cX  =0;
			DATA_TYPE cY  =0;
			DATA_TYPE cXY =0;
			DATA_TYPE cXX =0;

			DATA_TYPE y, t;

#pragma omp parallel for reduction(+:sumX, sumY, sumXY, sumXX, cX, cY, cXY, cXX, t, y)
//#pragma omp parallel for reduction(+:sumX, sumY, sumXY, sumXX)
			for (int i = 0; i < DATA_LENGTH; i++) {
/*				sumX += *(tXBuf+i);
				sumY += *(tYBuf+i);
				sumXY += (*(tXBuf+i)) * (*(tYBuf+i));
				sumXX += (*(tXBuf+i)) * (*(tXBuf+i));
				*/

				y = *(tXBuf+i) - cX;
				t = sumX + y;
				cX = (t - sumX) - y;
				sumX = t;

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





			*a0SW = (sumY*sumXX - sumX*sumXY)/(DATA_LENGTH*sumXX-sumX*sumX);
			*a1SW = (DATA_LENGTH*sumXY-sumX*sumY)/(DATA_LENGTH*sumXX-sumX*sumX);

		}




int main() {



	DATA_TYPE *X_sw = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));
	DATA_TYPE *Y_sw = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));


	lr_init(X_sw, Y_sw);

	DATA_TYPE  a0_sw;
	DATA_TYPE  a1_sw;


	software_start = getTimestamp();
	for (int i = 0; i < EXE_TIME_MONITORING_ITERATION_NUM; i++) {
		lr_software( X_sw, Y_sw, &a0_sw, &a1_sw);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

	printf("a0_sw=%f, a1_sw=%f\n", a0_sw, a1_sw);

	if(DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("huge number of iteration for manual monitoring\n");
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				lr_software( X_sw, Y_sw, &a0_sw, &a1_sw);
			}
		}
	}
	printf("a0_sw=%f, a1_sw=%f\n", a0_sw, a1_sw);
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
