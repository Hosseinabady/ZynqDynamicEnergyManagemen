/*
 * lr.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: csxmh
 */


#include <stdio.h>
#include <stdlib.h>
#include "ap_axi_sdata.h"
#include <hls_stream.h>
#include "histogram.h"






static void histogram_init(DATA_TYPE *data,
		                   u32  histogram_sw[BIN_LENGTH],
						   u32  histogram_hw[BIN_LENGTH]
					)

{

  int i, j;

  for (i = 0; i < DATA_LENGTH; i++) {
	  data[i] = ((float)rand()/(float)(RAND_MAX)) * 255;
  }
  for (int i = 0; i < BIN_LENGTH; i++) {
	  histogram_sw[i] = 0;
	  histogram_hw[i] = 0;
  }

}

void histogram_golden(DATA_TYPE *data,  u32  hist[BIN_LENGTH])
{

	for (int i = 0; i < DATA_LENGTH; i++) {
		u32 index =  (u32)data[i];
		if (index > 255) {
			printf("Error in input data at data[%d]=%f is greater than 255\n", i,data[i]);
			return;
		}
		hist[index]++;
	}

}

static int histogram_result_check(u32 histogram_sw[BIN_LENGTH], u32 histogram_hw[BIN_LENGTH])
{

	for(int i = 0; i < BIN_LENGTH; i++) {
		u32 sw = histogram_sw[i];
		u32 hw = histogram_hw[i];
		if (hw != sw ) {
			printf("histogram_sw[%d]=%d != histogram_hw[%d]=%d", i, histogram_sw[i], i, histogram_hw[i]);
		  return 1;
		}
	}
	return 0;
}

int histogram_test(DATA_TYPE data[DATA_LENGTH], u32 histogram_sw[BIN_LENGTH], u32 histogram_hw[BIN_LENGTH])
{
  int i;

  printf("Testing histogram ...\n");

  histogram_init(data, histogram_sw, histogram_hw);


  histogram_golden(data, histogram_sw);


  DATA_TYPE  *memory_0=0;
  u32        *memory_1=0;
  u32        inputdata_offset=(u32)data/4;
  u32        hitogram_offset=(u32)histogram_hw/4;

  histogram(memory_0, memory_0, memory_0, memory_0, memory_1, inputdata_offset, hitogram_offset);

  return histogram_result_check(histogram_sw, histogram_hw);
}


int main(int argc, char* argv[]){
  int test_passed = 0;


  DATA_TYPE *data = (DATA_TYPE *)malloc(DATA_LENGTH* sizeof(DATA_TYPE));
  u32 histogram_sw[BIN_LENGTH], histogram_hw[BIN_LENGTH];


  printf("Testing with DATA_LENGTH = %d\n", DATA_LENGTH);
  test_passed = histogram_test(data, histogram_sw, histogram_hw);
  printf("TEST %s\n", test_passed ?  "FAILED" : "PASSED");



  free(data);


  return test_passed;
}
