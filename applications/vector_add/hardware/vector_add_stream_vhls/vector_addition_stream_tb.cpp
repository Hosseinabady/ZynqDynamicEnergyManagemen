#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector_addition_stream.h"
#include <math.h>

void vector_add_sw(float*        a,
		float*        b,
		float*        c
		          );
int validate(float* c_sw, float* c_hw ) {
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

	float *a =(float *)malloc(n*sizeof(float));
	float *b =(float *)malloc(n*sizeof(float));
	float *c_sw =(float *)malloc(n*sizeof(float));
	float *c_hw =(float *)malloc(n*sizeof(float));

	float* memory = 0;
	vector_addition_stream( memory, memory, memory, memory, memory, memory, (u32)a/4, (u32)b/4, (u32)c_hw/4);
	vector_add_sw( a, b, c_sw);

	int status = validate(c_sw, c_hw);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
		printf("Validation FAILED!\n");
	}

    return status;

}


void vector_add_sw(float*        a,
		float*        b,
		float*        c
		          ) {
	for (int i = 0; i < n; i++)
		c[i] = a[i] + b[i];
}
