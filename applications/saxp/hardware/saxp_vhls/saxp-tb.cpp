#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saxp.h"
#include <math.h>

void saxp_sw(float*        a,
		float*        b
		          );
int validate(float* c_sw, float* c_hw, u32 n) {
	int i;

	for (i = 0; i < n; i++) {
		float hw = c_hw[i];
		float sw = c_sw[i];

		float diff = fabs(hw - sw);
		if(diff > 0.001 || diff != diff){
			printf("Error in out_data at c_hw[%d] = %f != c_sw[%d] = %f\n", i, hw, i,  sw);
		}
	}
	return 0;
}
int main() {

	float *a =(float *)malloc(DATA_LENGTH*sizeof(float));

	float *b_sw =(float *)malloc(DATA_LENGTH*sizeof(float));
	float *b_hw =(float *)malloc(DATA_LENGTH*sizeof(float));

	float* memory = 0;
	saxp_stream( memory, memory, memory, memory, memory, memory, memory, memory, (u32)a/4, (u32)b_hw/4, DATA_LENGTH);
	saxp_sw( a, b_sw);

	int status = validate(b_sw, b_hw,DATA_LENGTH);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
		printf("Validation FAILED!\n");
	}

    return status;

}


void saxp_sw(float*        a,
		float*        b
		          ) {
	for (int i = 0; i < DATA_LENGTH; i++)
		b[i] = 2.34*a[i] + 5.2355;
}
