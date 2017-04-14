/*
 * measure_static_power.c
 *
 *  Created on: May 27, 2015
 *      Author: csxmh
 */




/*
 * main.c
 *
 *  Created on: 15 Jan 2015
 *      Author: csxmh
 */

#include "stdio.h"

#include "measurement.h"
#include "monitoring.h"

void test_read_data();
void test_monitoring_thread();
#define MEASUREMENT_LENGTH 2000000


extern char log_file_name[1000];
int main() {


//	test_read_data();

	test_monitoring_thread();


	return 0;
}

void test_read_data() {
	int i;
	float  voltage;
	double current;
	double power;


	float  voltage_average = 0;
	double current_average = 0;
	double power_average = 0;

	for ( i = 0; i < MEASUREMENT_LENGTH; i++) {
		fpgacl_read_VCP(VCCINT_DEVICE, VCCINT_PAGE, &voltage, &current, &power);
		usleep(1000);
		voltage_average += voltage;
		current_average += current;
		power_average   += power;
		printf("voltage = %f  current = %f  power = %f\n", voltage, current, power);
	}

	voltage_average /= MEASUREMENT_LENGTH;
	current_average /= MEASUREMENT_LENGTH;
	power_average   /= MEASUREMENT_LENGTH;
	printf("voltage_average = %f  current_average = %f  power_average = %f\n", voltage_average, current_average, power_average);
}


void test_monitoring_thread() {

	FILE* fp_v;

	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);
	fp_v=fopen(log_file_name, "a");

	POWER_MONITORING_PROLOGUE();
	sleep(10);
	POWER_MONITORING_EPILOGUE();



	fclose(fp_v);
}
