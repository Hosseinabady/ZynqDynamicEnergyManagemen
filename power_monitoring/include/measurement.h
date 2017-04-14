/*
 * measurement.h
 *
 *  Created on: 15 Jan 2015
 *      Author: csxmh
 */

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_
#include <sys/time.h>
#include <pthread.h>



#define VCCINT_DEVICE   52
#define VCCINT_PAGE     0

#define VCCPINT_DEVICE  52
#define VCCPINT_PAGE    1

#define VCCAUX_DEVICE   52
#define VCCAUX_PAGE     2


#define VCCPAUX_DEVICE   52
#define VCCPAUX_PAGE     3

//--------------------------------

#define VCCADJ_DEVICE   53
#define VCCADJ_PAGE     0

#define VCC1V5_DEVICE   53
#define VCC1V5_PAGE     1
//=============================================================================================================
#define VCCINT_VOLTAGE_MAX   1.0
#define VCCINT_VOLTAGE_MIN   0.65

#define VCCPINT_VOLTAGE_MAX   1.0
#define VCCPINT_VOLTAGE_MIN   0.85


#define VCC1V5_VOLTAGE_MAX   1.5
#define VCC1V5_VOLTAGE_MIN   1.2
//=============================================================================================================

struct fpgacl_sample {

	struct timeval start_time;
	struct timeval end_time;

	float   vccint_voltage;
	double  vccint_current;
	double  vccint_power;

	float   vccpint_voltage;
	double  vccpint_current;
	double  vccpint_power;

	float   vccaux_voltage;
	double  vccaux_current;
	double  vccaux_power;

	float   vccpaux_voltage;
	double  vccpaux_current;
	double  vccpaux_power;

	float   vcc1v5_voltage;
	double  vcc1v5_current;
	double  vcc1v5_power;

	struct fpgacl_sample *next;
};





int open_device();
int fpgacl_read_VCP(unsigned char device, unsigned char page, float *voltage, double *current, double *power);
int fpgacl_write_voltage(unsigned char device, unsigned char page, float voltage);
float scale_voltage(int iic_fd, unsigned char device, unsigned char page, float desired_voltage);
int set_VCCINT_voltage(float target_voltage);
int set_VCCPINT_voltage(float target_voltage);
int set_VCC1V5_voltage(float target_voltage);


float readVoltage(int iic_fd, unsigned char deviceAddress, unsigned char pageAddress);
float readCurrent(int iic_fd, unsigned char deviceAddress, unsigned char pageAddress);


int fpgacl_read_sample(char *lane, char* value_buffer);
int fpgacl_write_sample(char *lane, char* value_buffer);
int read_current(int dev_id, char* current_buffer);
int read_power(int dev_id, char* power_buffer);



void *fpgacl_read_samples(void *tail);
void *fpgacl_read_sample_pthread();
void fpgacl_print_sample_pthread(struct fpgacl_sample *head);
void fpgacl_save_sample_pthread(struct fpgacl_sample *head, char *file_name);
void fpgacl_clear_sample_pthread(struct fpgacl_sample *head);
void fpgacl_save_average_pthread(struct fpgacl_sample *head, char *file_name) ;


void fpgacl_read_sample_start( );
void fpgacl_read_sample_stop( );




#define LENGTH 20


#define  VCC_INT_VOLTAGE                 1
#define  VCC_INT_CURRENT                 2




#endif /* MEASUREMENT_H_ */
