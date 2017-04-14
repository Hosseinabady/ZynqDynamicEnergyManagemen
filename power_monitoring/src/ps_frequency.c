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
	if (argc == 2) {
	  divisor0 = atoi(argv[1]);
	  printf("new frequency is 1000/(%d) ?? = %f\n", divisor0,  1000.0/(divisor0));
    } else {
    	printf("The command had no other arguments.\n");
    	return -1;
	}
	ps_frequency_set(divisor0);

	return 0;
}
