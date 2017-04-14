/*
 * measurement.c
 *
 *  Created on: 15 Jan 2015
 *      Author: csxmh
 */




#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <strings.h>

#include "measurement.h"


int open_device() {



	int iic_fd = open("/dev/i2c-8", O_RDWR);
	if (iic_fd < 0) {
		printf("ERROR: Unable to open /dev/i2c-8 for PMBus access: %d\n", iic_fd);
		return -1;
	}

	return iic_fd;
}


int fpgacl_read_VCP(unsigned char device, unsigned char page, float *voltage, double *current, double *power) {

  int iic_fd = open_device();
  int status = 0;
  int k = 0;
  float v;
  double c;
  double p;

  v= readVoltage(iic_fd, device, page);

  if (v < 0 || v > 5) {
//	  printf("fpgacl_read_VCP: Error reading voltage, voltage= %f\n", v);
//	  exit(1);
	  return -1;
  }

  *voltage = v;
  k = 0;

  c = readCurrent(iic_fd, device, page);

  if (c < 0 || c > 10) {
//	  printf("fpgacl_read_VCP: Error reading current, current = %f\n", c);
//	  exit(1);
  	  return -1;
  }
  *current = c;
   p = v*c;
  *power = p;

  close(iic_fd);
  return status;
}

int fpgacl_write_voltage(unsigned char device, unsigned char page, float voltage) {

  int iic_fd = open_device();
  int status = 0;

  scale_voltage(iic_fd, device, page, voltage);

  close(iic_fd);
  return status;
}


int set_VCCINT_voltage(float target_voltage) {
	if (target_voltage > VCCINT_VOLTAGE_MAX || target_voltage < VCCINT_VOLTAGE_MIN) {
		printf("VCCINT voltage should be between %f and %f\n", VCCINT_VOLTAGE_MAX, VCCINT_VOLTAGE_MIN);
		return -1;
	}
	fpgacl_write_voltage(VCCINT_DEVICE, VCCINT_PAGE, target_voltage);
}


int set_VCCPINT_voltage(float target_voltage) {
	if (target_voltage > VCCPINT_VOLTAGE_MAX || target_voltage < VCCPINT_VOLTAGE_MIN) {
		printf("set_VCCPINT_voltage:VCCPINT target = %f that should be between %f and %f\n", target_voltage, VCCPINT_VOLTAGE_MAX, VCCPINT_VOLTAGE_MIN);
		return -1;
	}
	fpgacl_write_voltage(VCCPINT_DEVICE, VCCPINT_PAGE, target_voltage);
}

int set_VCC1V5_voltage(float target_voltage) {
	if (target_voltage > VCC1V5_VOLTAGE_MAX || target_voltage < VCC1V5_VOLTAGE_MIN) {
		printf("set_VCC1V5_voltage:VCC1V5 target = %f that should be between %f and %f\n", target_voltage, VCC1V5_VOLTAGE_MAX, VCC1V5_VOLTAGE_MIN);
		return -1;
	}
	fpgacl_write_voltage(VCC1V5_DEVICE, VCC1V5_PAGE, target_voltage);
}

/*
int fpgacl_write_sample(char *lane, char* value_buffer) {

  int dev_id = open_device(lane,O_WRONLY);

//  printf("from write = %s , size of buffer = %d\n", value_buffer, sizeof(value_buffer));
  if(write(dev_id, value_buffer, sizeof(value_buffer)) < 0) {
    fprintf(stderr, "%s:%d write\n", __FILE__, __LINE__);
  }


  close(dev_id);
  return 0;
}


int set_VCCINT_voltage(int target_voltage) {

	int vout_max         =(target_voltage*1.2);

    int vout_over_fault_limit   =(target_voltage*1.1);
    int vout_over_warn_limit   =(target_voltage*1.075);
    int vout_margin_high =(target_voltage*1.05);
    int vout_power_good_on =(target_voltage*0.925);

    int vout_command     =(target_voltage);

    int vout_under_fault_limit   =(target_voltage*0.9);
    int vout_under_warn_limit   =(target_voltage*0.925);
    int vout_margin_low =(target_voltage*0.95);
    int vout_power_good_off =(target_voltage*0.9);

    int iout_oc_low_fault_limit =(target_voltage*0.9);

    char vout_max_str[100];

    char vout_over_fault_limit_str[100];
    char vout_over_warn_limit_str[100];
    char vout_margin_high_str[100];
    char vout_power_good_on_str[100];

    char vout_command_str[100];

    char vout_under_fault_limit_str[100];
    char vout_under_warn_limit_str[100];
    char vout_margin_low_str[100];
    char vout_power_good_off_str[100];

    char iout_oc_low_fault_limit_str[100];


    sprintf(vout_max_str, "%d", vout_max);

    sprintf(vout_over_fault_limit_str, "%d", vout_over_fault_limit);
    sprintf(vout_over_warn_limit_str, "%d", vout_over_warn_limit);
    sprintf(vout_margin_high_str, "%d", vout_margin_high);
    sprintf(vout_power_good_on_str, "%d", vout_power_good_on);

    sprintf(vout_command_str, "%d", vout_command);

    sprintf(vout_under_fault_limit_str, "%d", vout_under_fault_limit);
    sprintf(vout_under_warn_limit_str, "%d", vout_under_warn_limit);
    sprintf(vout_margin_low_str, "%d", vout_margin_low);
    sprintf(vout_power_good_off_str, "%d", vout_power_good_off);

    sprintf(iout_oc_low_fault_limit_str, "%d", iout_oc_low_fault_limit);


	char value_buffer[100];
	fpgacl_read_sample(VCCINT_VOLTAGE, value_buffer);
//	printf( "sample from main = %s\n", value_buffer);
	int sample_value; sscanf(value_buffer, "%d", &(sample_value));
	int status;

	if (target_voltage < sample_value) {
//		printf("vout_power_good_off = %s\n", vout_power_good_off_str);
		status = fpgacl_write_sample(VCCINT_POWER_GOOD_OFF, vout_power_good_off_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

//		printf("iout_oc_low_fault_limit = %s\n", iout_oc_low_fault_limit_str);
		status = fpgacl_write_sample(VCCINT_IOUT_OC_LV_FAULT_LIMIT, iout_oc_low_fault_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

//		printf("vout_under_fault_limit = %s\n", vout_under_fault_limit_str);
		status = fpgacl_write_sample(VCCINT_UNDER_FAULT_LIMIT, vout_under_fault_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

//		printf("vout_under_warn_limit = %s\n", vout_under_warn_limit_str);
		status = fpgacl_write_sample(VCCINT_UNDER_WARN_LIMIT, vout_under_warn_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

//		printf("vout_power_good_on = %s\n", vout_power_good_on_str);
		status = fpgacl_write_sample(VCCINT_POWER_GOOD_ON, vout_power_good_on_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

//		printf("vout_margin_low = %s\n", vout_margin_low_str);
		status = fpgacl_write_sample(VCCINT_VOUT_MARGIN_LOW, vout_margin_low_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}


//		printf("vout_command = %s\n", vout_command_str);
		status = fpgacl_write_sample(VCCINT_VOUT_CMD, vout_command_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}


//		printf("vout_margin_high = %s\n", vout_margin_high_str);
		status = fpgacl_write_sample(VCCINT_VOUT_MARGIN_HIGH, vout_margin_high_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

//		printf("vout_over_warn_limit = %s\n", vout_over_warn_limit_str);
		status = fpgacl_write_sample(VCCINT_OVER_WARN_LIMIT, vout_over_warn_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}


//		printf("vout_over_fault_limit = %s\n", vout_over_fault_limit_str);
		status = fpgacl_write_sample(VCCINT_OVER_FAULT_LIMIT, vout_over_fault_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

	} else {

//		printf("vout_over_fault_limit = %s\n", vout_over_fault_limit_str);
		status = fpgacl_write_sample(VCCINT_OVER_FAULT_LIMIT, vout_over_fault_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

//		printf("vout_over_warn_limit = %s\n", vout_over_warn_limit_str);
		status = fpgacl_write_sample(VCCINT_OVER_WARN_LIMIT, vout_over_warn_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

//		printf("vout_margin_high = %s\n", vout_margin_high_str);
		status = fpgacl_write_sample(VCCINT_VOUT_MARGIN_HIGH, vout_margin_high_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}


//		printf("vout_command = %s\n", vout_command_str);
		status = fpgacl_write_sample(VCCINT_VOUT_CMD, vout_command_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}


//		printf("vout_margin_low = %s\n", vout_margin_low_str);
		status = fpgacl_write_sample(VCCINT_VOUT_MARGIN_LOW, vout_margin_low_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}


//		printf("vout_power_good_on = %s\n", vout_power_good_on_str);
		status = fpgacl_write_sample(VCCINT_POWER_GOOD_ON, vout_power_good_on_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}


//		printf("vout_under_warn_limit = %s\n", vout_under_warn_limit_str);
		status = fpgacl_write_sample(VCCINT_UNDER_WARN_LIMIT, vout_under_warn_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}


//		printf("vout_under_fault_limit = %s\n", vout_under_fault_limit_str);
		status = fpgacl_write_sample(VCCINT_UNDER_FAULT_LIMIT, vout_under_fault_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}


//		printf("iout_oc_low_fault_limit = %s\n", iout_oc_low_fault_limit_str);
		status = fpgacl_write_sample(VCCINT_IOUT_OC_LV_FAULT_LIMIT, iout_oc_low_fault_limit_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

//		printf("vout_power_good_off = %s\n", vout_power_good_off_str);
		status = fpgacl_write_sample(VCCINT_POWER_GOOD_OFF, vout_power_good_off_str);
		if(status != 0) {
			printf("error scaling voltage", __FILE__, __LINE__);
			return -1;
		}

	}

	return 0;
}

*/
