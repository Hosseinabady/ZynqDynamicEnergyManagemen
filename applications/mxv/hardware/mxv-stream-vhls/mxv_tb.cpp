#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mxv.h"

void mxv_golden(int n, int m, DATA_TYPE *  a,
		DATA_TYPE *  b, DATA_TYPE *  c);

void mxv_hw(int n, int m, DATA_TYPE *  a,
		DATA_TYPE *  b, DATA_TYPE *  c);

int validate(int n,
		     DATA_TYPE *a_golden,
		     DATA_TYPE *a_hw);
int main(int argc, char *argv[])
{
	DATA_TYPE *a_golden,*b_golden,*c_golden;
	DATA_TYPE *a_hw,*b_hw,*c_hw;

	int i, j, m, n;

	printf("Please give m and n: ");
	n=N;
	m=M;
	printf("\n");

	if ( (a_golden=(DATA_TYPE *)malloc(n*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (b_golden=(DATA_TYPE *)malloc(m*n*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for b");
	if ( (c_golden=(DATA_TYPE *)malloc(m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for c");


	if ( (a_hw=(DATA_TYPE *)malloc(n*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for a");
	if ( (b_hw=(DATA_TYPE *)malloc(m*n*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for b");
	if ( (c_hw=(DATA_TYPE *)malloc(m*sizeof(DATA_TYPE))) == NULL )
		perror("memory allocation for c");


	printf("Initializing matrix B and vector c\n");

	srand(time(NULL));
	for (j=0; j<m; j++) {
		float t = rand()/(1.0*RAND_MAX);
		c_golden[j] = t;
		c_hw[j] = t;
	}
	for (i=0; i<n; i++)
		for (j=0; j<m; j++) {
			float t = rand()/(1.0*RAND_MAX);
			b_golden[i*m+j] = t;
			b_hw[i*m+j] = t;
		}

	printf("Executing mxv function for n = %d m = %d\n",n,m);

	(void) mxv_golden(n, m, a_golden, b_golden, c_golden);


	(void) mxv_hw(n, m, a_hw, b_hw, c_hw);


	  int status = validate(n, a_golden, a_hw);
	  if (status == 0) {
	    printf("Validation PASSED!\n");
	  } else {
	  	  printf("Validation FAILED!\n");
	  }



	  free(a_golden);
	  free(b_golden);
	  free(c_golden);
	  free(a_hw);
	  free(b_hw);
	  free(c_hw);


	  return(status);
}

void mxv_golden(int n, int m, DATA_TYPE *  a, DATA_TYPE *  b,
		DATA_TYPE *  c)
{
   int i, j;

   for (i=0; i<n; i++)
   {
      a[i] = 0.0;
      for (j=0; j<m; j++)
         a[i] += b[i*m+j]*c[j];
   }
}



void mxv_hw(int n, int m, DATA_TYPE *  a,
		DATA_TYPE *  b, DATA_TYPE *  c) {

	DATA_TYPE *memory = 0;

	u32    a_offset_address = (u32)(a)/4;
	u32    b_offset_address = (u32)(b)/4;
	u32    c_offset_address = (u32)c/4;

	mxv_stream(memory, memory, memory, memory, memory, memory, memory, memory, a_offset_address, b_offset_address, c_offset_address);


}

int validate(int n,
		     DATA_TYPE *a_golden,
		     DATA_TYPE *a_hw) {
	int i, j, k = 0, p = 0;
	for(i = 0; i < n; i++) {
		DATA_TYPE hw = a_hw[i];
		DATA_TYPE sw = a_golden[i];
		DATA_TYPE diff = hw - sw;
		if(fabs(diff) > 0.01){
			printf("Error in out_data at A_hw[%d] = %f != A_sw[%d] = %f\n", i, hw, i, sw);
			return -1;
		}
	}
	return 0;
}
