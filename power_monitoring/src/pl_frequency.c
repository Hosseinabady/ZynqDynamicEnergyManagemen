/*
 * frequency.c
 *
 *  Created on: May 19, 2015
 *      Author: csxmh
 */




#include "set_frequency.h"
#include <string.h>

int main(int argc, char *argv[]) {
	int divisor0;
	int divisor1;

	if (argc == 3) {
	  divisor0 = atoi(argv[1]);
	  divisor1 = atoi(argv[2]);
	  printf("new frequency is 1000/(%d*%d) = %f\n", divisor0, divisor1,  1000.0/(divisor0*divisor1));
    } else {
    	printf("The command had no other arguments.\n");
    	return -1;
	}



	pl_frequency_set(FPGA0_CLK, divisor0, divisor1);
	pl_frequency_set(FPGA1_CLK, divisor0, divisor1);
	pl_frequency_set(FPGA2_CLK, divisor0, divisor1);
	pl_frequency_set(FPGA3_CLK, divisor0, divisor1);

}
