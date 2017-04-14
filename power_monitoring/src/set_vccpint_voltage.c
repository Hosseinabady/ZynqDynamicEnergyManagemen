/*
 * set_vcc_voltage.c
 *
 *  Created on: May 29, 2015
 *      Author: csxmh
 */



#include "stdio.h"
#include <stdlib.h>
#include "measurement.h"




int main(int argc, char *argv[]) {


	float target_value;
	if (argc == 2) {
		target_value = atof(argv[1]);
		if (target_value < 0.85 || target_value > 1) {
		  printf("target voltage should be less than 1 v and greater than 0.85 v\n");
	  	  return -1;
		}
    } else {
    	printf("The command had no other arguments.\n");
    	return -1;
	}
	printf("target voltage would be = %f v\n", target_value);
	set_VCCPINT_voltage(target_value);
	return 0;
}



