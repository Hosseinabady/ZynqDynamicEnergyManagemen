
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "column-2dmean.h"



void init_data(DATA_TYPE *data, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			data[i*m+j] = rand()/(RAND_MAX*1.0);
		}
	}
}


int validate(DATA_TYPE *mean_sw, DATA_TYPE *mean_hw, int m) {
	int status;

	for (int row = 0; row < m; row++) {

		float hw = mean_hw[row];
		float sw = mean_sw[row];

		float diff = fabs(hw - sw);
		if(diff > 0.001 || diff != diff){
			printf("Error in data at mean_hw[%d] = %f != mean_sw[%d] = %f\n", row, hw, row, sw);
			return -1;
		}
	}

	printf("data at mean_hw[%d] = %f != mean_sw[%d] = %f\n", 10, mean_hw[10], 10, mean_sw[10]);
	return 0;
}


int main(int argc, char** argv)
{

	int n = N;
	int m = M;
	int status;

 	DATA_TYPE *data;
 	DATA_TYPE *mean_sw;
 	DATA_TYPE *mean_hw;

	data = (DATA_TYPE *)malloc(n*m*sizeof(DATA_TYPE));
	mean_sw = (DATA_TYPE *)malloc(m*sizeof(DATA_TYPE));
	mean_hw = (DATA_TYPE *)malloc(m*sizeof(DATA_TYPE));

	init_data(data, n, m);



	DATA_TYPE float_n = 1.0*n;

	for (int j = 0; j < m; j++)  {
		mean_sw[j] = 0.0;
		for (int i = 0; i < n; i++)
			mean_sw[j] += data[i*m+j];
		mean_sw[j] /= float_n;
    }

	DATA_TYPE* memory= 0;
	u32 data_offset = (u32)data/sizeof(DATA_TYPE);
	u32 mean_hw_offset = (u32)mean_hw/sizeof(DATA_TYPE);
	column_2dmean(	memory, memory,
					memory, memory,
					memory, memory,
					memory, memory,
					data_offset, mean_hw_offset, n);


	status = validate(mean_sw, mean_hw, m);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
	 	printf("Validation FAILED!\n");
	}

  return status;
}
