#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix_mult.h"

void mxv_golden(int n, int m, int p, DATA_TYPE  *a, DATA_TYPE  *b, DATA_TYPE  *c);

void mxv_hw(int n, int m,  int p, DATA_TYPE  *a, DATA_TYPE  *b, DATA_TYPE  *c);

int validate(int n,
		 	 int m,
			 int p,
		     DATA_TYPE *c_golden,
		     DATA_TYPE *c_hw);
int main(int argc, char *argv[])
{
	DATA_TYPE *a_golden, *b_golden, *c_golden;
	DATA_TYPE *a_hw, *b_hw, *c_hw;


	int i, j, m, n, p;

	printf("Please give m and n: ");
	n=N;
	m=M;
	p=P;
	printf("\n");

	a_golden = (DATA_TYPE*)malloc(n*m*sizeof(DATA_TYPE));
	b_golden = (DATA_TYPE*)malloc(m*p*sizeof(DATA_TYPE));
	c_golden = (DATA_TYPE*)malloc(n*p*sizeof(DATA_TYPE));

	a_hw = (DATA_TYPE*)malloc(n*m*sizeof(DATA_TYPE));
	b_hw = (DATA_TYPE*)malloc(m*p*sizeof(DATA_TYPE));
	c_hw = (DATA_TYPE*)malloc(n*p*sizeof(DATA_TYPE));

	printf("Initializing matrix B and vector c\n");

	srand(time(NULL));
	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			DATA_TYPE t = rand();
			a_golden[i*M+j] = t;
			a_hw[i*M+j] = t;
		}
	}

	for (i=0; i<m; i++) {
		for (j=0; j<p; j++) {
			DATA_TYPE t = rand();
			b_golden[i*P+j] = t;
			b_hw[i*P+j] = t;
		}
	}


	printf("Executing mxv function for n = %d m = %d p = %d\n",n,m,p);

	(void) mxv_golden(n, m, p, a_golden, b_golden, c_golden);


	(void) mxv_hw(n, m, p, a_hw, b_hw, c_hw);


	  int status = validate(n, m, p, c_golden, c_hw);
	  if (status == 0) {
	    printf("Validation PASSED!\n");
	  } else {
	  	  printf("Validation FAILED!\n");
	  }






	  return(status);
}

void mxv_golden(int n, int m, int p, DATA_TYPE  *a, DATA_TYPE  *b, DATA_TYPE  *c)
{
   int i, j, k;

	for(i=0;i<N;i++) {
		for(j=0;j<P;j++) {
			c[i*P+j] = 0.0;
			for(k=0;k<M;k++) {
				c[i*P+j] += a[i*M+k]*b[k*P+j];
			}
		}
	}
}



void mxv_hw(int n, int m, int p, DATA_TYPE  *a, DATA_TYPE  *b,	DATA_TYPE  *c) {

	DATA_TYPE *memory = 0;

	u32    a_offset_address = (u32)(a)/4;
	u32    b_offset_address = (u32)(b)/4;
	u32    c_offset_address = (u32)c/4;

	matrix_mult_large(memory, memory, memory, memory, memory, memory, memory, memory, memory, memory, memory, memory, memory, memory, memory, memory, memory, a_offset_address, b_offset_address, c_offset_address);

}

int validate(int n,
		int m,
		int p,
		     DATA_TYPE *c_golden,
		     DATA_TYPE *c_hw) {

	int i, j;

	for(i = 0; i < n; i++) {
		for(j = 0; j < p; j++) {
			DATA_TYPE hw = c_hw[i*P+j];
			DATA_TYPE sw = c_golden[i*P+j];
			DATA_TYPE diff = hw - sw;
			if(diff != 0){
				printf("Error in out_data at C_hw[%d][%d] = %d != C_sw[%d][%d] = %d\n", i, j, hw, i, j, sw);
				return -1;
			}
		}
	}
	return 0;
}
