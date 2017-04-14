/*
 * measurement_threads.c
 *
 *  Created on: May 15, 2015
 *      Author: csxmh
 */

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <sched.h>
#include <stdio.h>
#include "measurement.h"
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

int start;
pthread_mutex_t mutex;

int stop;
pthread_t  thread_ID;
void      *exit_status;
struct fpgacl_sample * head;

long long int sample_count = 0;

double   vccint_voltage_total=0;
double   vccint_current_total=0;
double   vccint_power_total=0;

double   vccpint_voltage_total=0;
double   vccpint_current_total=0;
double   vccpint_power_total=0;

double   vccaux_voltage_total=0;
double   vccaux_current_total=0;
double   vccaux_power_total=0;

double   vccpaux_voltage_total=0;
double   vccpaux_current_total=0;
double   vccpaux_power_total=0;

double   vcc1v5_voltage_total=0;
double   vcc1v5_current_total=0;
double   vcc1v5_power_total=0;

void *fpgacl_read_samples(void *head) {

	FILE *fp_log;
	float  vccint_voltage;
	double vccint_current;
	double vccint_power;


	float vccpint_voltage;
	double vccpint_current;
	double vccpint_power;

	float vccaux_voltage;
	double vccaux_current;
	double vccaux_power;

	float vccpaux_voltage;
	double vccpaux_current;
	double vccpaux_power;

	float vcc1v5_voltage;
	double vcc1v5_current;
	double vcc1v5_power;

	int i;
	struct  fpgacl_sample *t = (struct fpgacl_sample*) head;
	int start_flag = 0;
	int stop_flag = 0;
	fp_log = fopen("power_measurement_log.txt", "a");
	if (!fp_log) {
		printf("cannot open test_debug.txt file \n ");
		return;
	}


	while(1) {

		start_flag = 1;
		pthread_mutex_lock(&mutex);
		if(start == 0)
			start_flag = 0;
		pthread_mutex_unlock(&mutex);
		if(start_flag == 0)
			continue;

		int status;

//		usleep(10);

		fpgacl_read_VCP(VCCINT_DEVICE, VCCINT_PAGE,   &vccint_voltage,  &vccint_current,  &vccint_power);
		fpgacl_read_VCP(VCCPINT_DEVICE, VCCPINT_PAGE, &vccpint_voltage, &vccpint_current, &vccpint_power);
		fpgacl_read_VCP(VCCAUX_DEVICE, VCCAUX_PAGE,   &vccaux_voltage,  &vccaux_current,  &vccaux_power);
		fpgacl_read_VCP(VCCPAUX_DEVICE, VCCPAUX_PAGE, &vccpaux_voltage, &vccpaux_current, &vccpaux_power);
		fpgacl_read_VCP(VCC1V5_DEVICE, VCC1V5_PAGE,   &vcc1v5_voltage,  &vcc1v5_current,  &vcc1v5_power);


		if (   (vccint_voltage  > 0    &&   vccint_voltage  < 1.5)
			&& (vccint_current  >= 0    &&   vccint_current  < 3.0)

			&& (vccpint_voltage > 0    &&   vccpint_voltage < 1.7)
			&& (vccpint_current >= 0    &&   vccpint_current < 3.0)

			&& (vccaux_voltage  > 0    &&   vccaux_voltage  < 2.0)
			&& (vccaux_current  >= 0    &&   vccaux_current  < 3.0)

			&& (vccpaux_voltage > 0    &&   vccpaux_voltage < 2.0)
			&& (vccpaux_current >= 0    &&   vccpaux_current < 3.0)

			&& (vcc1v5_voltage  > 0    &&   vcc1v5_voltage  < 1.7)
			&& (vcc1v5_current  >= 0    &&   vcc1v5_current  < 3.0)
			) {

			vccint_voltage_total  += vccint_voltage;
			vccint_current_total  += vccint_current;
			vccint_power_total    += vccint_power;

			vccpint_voltage_total += vccpint_voltage;
			vccpint_current_total += vccpint_current;
			vccpint_power_total   += vccpint_power;

			vccaux_voltage_total  += vccaux_voltage;
			vccaux_current_total  += vccaux_current;
			vccaux_power_total    += vccaux_power;

			vccpaux_voltage_total += vccpaux_voltage;
			vccpaux_current_total += vccpaux_current;
			vccpaux_power_total   += vccpaux_power;

			vcc1v5_voltage_total  += vcc1v5_voltage;
			vcc1v5_current_total  += vcc1v5_current;
			vcc1v5_power_total    += vcc1v5_power;

			sample_count++;

//   		struct  fpgacl_sample *new_fpgacl_sample = (struct fpgacl_sample *)malloc(sizeof (struct fpgacl_sample));
//			new_fpgacl_sample->next = NULL;
//			t->next = new_fpgacl_sample;
//			t = new_fpgacl_sample;
		} else {
			fprintf(fp_log, "error  monitoring \n ================== \n");
			fprintf(fp_log,  "vccint_voltage =%f\n", vccint_voltage);
			fprintf(fp_log,  "vccint_current = %f\n", vccint_current);
			fprintf(fp_log,  "vccint_power = %f \n", vccint_power);

			fprintf(fp_log,  "vccpint_voltage =%f\n", vccpint_voltage);
			fprintf(fp_log,  "vccpint_current = %f\n", vccpint_current);
			fprintf(fp_log,  "vccpint_power = %f \n", vccpint_power);

			fprintf(fp_log,  "vccaux_voltage =%f\n", vccaux_voltage);
			fprintf(fp_log,  "vccaux_current = %f\n", vccaux_current);
			fprintf(fp_log,  "vccaux_power = %f \n", vccaux_power);

			fprintf(fp_log,  "vccpaux_voltage =%f\n", vccpaux_voltage);
			fprintf(fp_log,  "vccpaux_current = %f\n", vccpaux_current);
			fprintf(fp_log,  "vccpaux_power = %f \n", vccpaux_power);

			fprintf(fp_log,  "vcc1v5_voltage =%f\n", vcc1v5_voltage);
			fprintf(fp_log,  "vcc1v5_current = %f\n", vcc1v5_current);
			fprintf(fp_log,  "vcc1v5_power = %f \n", vcc1v5_power);


//			usleep(10);
		}

		stop_flag = 0;
		pthread_mutex_lock(&mutex);
		if (stop == 1) {
			stop_flag = 1;
		}
		pthread_mutex_unlock(&mutex);

		if(stop_flag==1) {
			break;
		}
	}
	fclose(fp_log);
}

void *fpgacl_read_sample_pthread() {

	pthread_mutex_init(&mutex, NULL);

	pthread_mutex_lock(&mutex);
	stop = 0;
	start = 0;
	pthread_mutex_unlock(&mutex);

	head = (struct fpgacl_sample *)malloc(sizeof (struct fpgacl_sample));
	head->next = NULL;


	cpu_set_t cpu_set2;
	CPU_SET(1, &cpu_set2);
	pthread_create(&thread_ID, NULL, fpgacl_read_samples, head);
	sched_setaffinity(thread_ID, sizeof(cpu_set_t), &cpu_set2);

//	pthread_join(thread_ID, &exit_status);


	return head;
}


void fpgacl_read_sample_start( ) {

	pthread_mutex_lock(&mutex);

	sample_count = 0;
	vccint_voltage_total  = 0;
	vccint_current_total  = 0;
	vccint_power_total    = 0;

	vccpint_voltage_total = 0;
	vccpint_current_total = 0;
	vccpint_power_total   = 0;

	vccaux_voltage_total  = 0;
	vccaux_current_total  = 0;
	vccaux_power_total    = 0;

	vccpaux_voltage_total = 0;
	vccpaux_current_total = 0;
	vccpaux_power_total   = 0;

	vcc1v5_voltage_total  = 0;
	vcc1v5_current_total  = 0;
	vcc1v5_power_total    = 0;
	start = 1;
	stop  = 0;
	pthread_mutex_unlock(&mutex);
}


void fpgacl_read_sample_stop( ) {

	pthread_mutex_lock(&mutex);
	stop = 1;
	start = 0;
	pthread_mutex_unlock(&mutex);
	pthread_join(thread_ID, &exit_status);
	pthread_detach(thread_ID);
}



void fpgacl_save_average_pthread(struct fpgacl_sample *head, char *file_name) {

	FILE *fp;







	struct fpgacl_sample *sample = head;

	fp=fopen(file_name, "a");



/*
	while(sample != NULL){

		vccint_voltage_total   += sample->vccint_voltage;
		vccint_current_total   += sample->vccint_current;
		vccint_power_total     += sample->vccint_power;

		vccpint_voltage_total   += sample->vccpint_voltage;
		vccpint_current_total   += sample->vccpint_current;
		vccpint_power_total     += sample->vccpint_power;

		vccaux_voltage_total    += sample->vccaux_voltage;
		vccaux_current_total    += sample->vccaux_current;
		vccaux_power_total      += sample->vccaux_power;

		vccpaux_voltage_total   += sample->vccpaux_voltage;
		vccpaux_current_total   += sample->vccpaux_current;
		vccpaux_power_total     += sample->vccpaux_power;

		vcc1v5_voltage_total    += sample->vcc1v5_voltage;
		vcc1v5_current_total    += sample->vcc1v5_current;
		vcc1v5_power_total      += sample->vcc1v5_power;


		count++;
		sample = sample->next;
	}


*/



	fprintf(fp, "vccint_voltage_average = %f count = %d\n", vccint_voltage_total/sample_count, sample_count);
	fprintf(fp, "vccint_current_average = %f count = %d\n", vccint_current_total/sample_count, sample_count);
	fprintf(fp, "vccint_power_average = %f count = %d\n",   vccint_power_total/sample_count, sample_count);

	fprintf(fp, "vccpint_voltage_average = %f count = %d\n", vccpint_voltage_total/sample_count, sample_count);
	fprintf(fp, "vccpint_current_average = %f count = %d\n", vccpint_current_total/sample_count, sample_count);
	fprintf(fp, "vccpint_power_average = %f count = %d\n",   vccpint_power_total/sample_count, sample_count);

	fprintf(fp, "vccaux_voltage_average = %f count = %d\n", vccaux_voltage_total/sample_count, sample_count);
	fprintf(fp, "vccaux_current_average = %f count = %d\n", vccaux_current_total/sample_count, sample_count);
	fprintf(fp, "vccaux_power_average = %f count = %d\n",   vccaux_power_total/sample_count, sample_count);

	fprintf(fp, "vccpaux_voltage_average = %f count = %d\n", vccpaux_voltage_total/sample_count, sample_count);
	fprintf(fp, "vccpaux_current_average = %f count = %d\n", vccpaux_current_total/sample_count, sample_count);
	fprintf(fp, "vccpaux_power_average = %f count = %d\n",   vccpaux_power_total/sample_count, sample_count);


	fprintf(fp, "vcc1v5_voltage_average = %f count = %d\n", vcc1v5_voltage_total/sample_count, sample_count);
	fprintf(fp, "vcc1v5_current_average = %f count = %d\n", vcc1v5_current_total/sample_count, sample_count);
	fprintf(fp, "vcc1v5_power_average = %f count = %d\n",   vcc1v5_power_total/sample_count, sample_count);
	fclose(fp);
}

void fpgacl_clear_sample_pthread(struct fpgacl_sample *head) {

	struct fpgacl_sample *sample = head;
	while (sample != NULL) {
		struct fpgacl_sample *next = sample->next;
		free (sample);
		sample = next;
	}
	pthread_mutex_destroy(&mutex);
}
