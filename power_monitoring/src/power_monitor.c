/******************************************************************************
*
* (c) Copyright 2010-13 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
******************************************************************************/
/**
*
* @file power_monitor.c

* The Power Monitor Application reads the voltage and current information
* of the power supply regulators monitored by the UCD9248 Power controllers,
* calculates the average power of individual supply and finally calculates the 
* total power consumed by the ZC702 board. These values are updated for every 1s.
* <pre>
* MODIFICATION HISTORY:
*
* Ver          Who                Date     Changes
* ----- ----------------------    ----     ---------------------------------------------------------------
* 1.00a Rob ArmStrong JR           --       Inital Release
* 2.00a Srikanth Erusalagandi    12/16/13   Made modifications to calculate average current and be able to display in on UART Console.
*
* </pre>
******************************************************************************/

/***************************** Include Files *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "i2c-dev.h"
#include "measurement.h"
/* PMBUS Commands */
#define CMD_PAGE                   0x00
#define CMD_READ_VOUT       0x8B
#define CMD_READ_IOUT        0x8C

struct voltage_rail {
	char *name;
	unsigned char device;
	unsigned char page;
	double average_current;
	double average_power;
};

struct voltage_rail zc702_rails[] = {
			{ name			: "VccInt   ",
					device			: 52,
					page			: 0,
					average_current	: 0.0,
					average_power	: 0.0
			},
			{
					name	: "VccPInt  ",
					device	: 52,
					page	: 1,
					average_current	: 0.0,
					average_power	: 0.0
			},
			{
					name	: "VccAux   ",
					device	: 52,
					page	: 2,
					average_current	: 0.0,
					average_power	: 0.0
			},
			{
					name	: "VccPAux  ",
					device	: 52,
					page : 3,
					average_current	: 0.0,
					average_power	: 0.0
			},
			{
					name	: "Vadj     ",
					device	: 53,
					page	: 0,
					average_current	: 0.0,
					average_power	: 0.0
			},
			{
					name	: "Vcc1V5_PS",
					device	: 53,
					page	: 1,
					average_current	: 0.0,
					average_power	: 0.0
			},
			{
					name	: "VccMIO_PS",
					device	: 53,
					page	: 2,
					average_current	: 0.0,
					average_power	: 0.0
			},
			{
					name	: "VccBRAM  ",
					device	: 53,
					page	: 3,
					average_current	: 0.0,
					average_power	: 0.0
			},
			{
					name	: "Vcc3V3   ",
					device	: 54,
					page	: 0,
					average_current	: 0.0,
					average_power	: 0.0
			},
			{
					name	: "Vcc2V5   ",
					device	: 54,
					page	: 1,
					average_current	: 0.0,
					average_power	: 0.0
			}
};

double linear11ToFloat(unsigned char highByte, unsigned char lowByte) {
	unsigned short combinedWord;
	signed char exponent;
	signed short mantissa;
	double current;

	combinedWord = highByte;
	combinedWord <<= 8;
	combinedWord += lowByte;

	exponent = combinedWord >> 11;
	mantissa = combinedWord & 0x7ff;

	/* Sign extend the exponent and the mantissa */
	if(exponent > 0x0f) {
		exponent |= 0xe0;
	}
	if(mantissa > 0x03ff) {
		mantissa |= 0xf800;
	}

	int exp_v = 1;
    int i;

	for (i=0;i<exponent;i++)
		exp_v = exp_v * 2;

	current = mantissa * (float)exp_v;

	return (float)current;
}



float convert_pmbus_reading(uint16_t pmbus_reading)
{
	uint8_t x_e_u;
	int x_e,exp_v;
	int i;
	float x_p;
	int16_t x_m;

	/* TODO: Handle negative mantissa:
		It will never happen since current and power can't be negative */

	/* Extract the mantissa and exponent. See Section 7.1 in PMBus Spec. - Part 2*/
	x_m = (pmbus_reading & 0x07FF);
	x_e_u = ((pmbus_reading & 0xF800) >> 11);

	//printf ("mantisa is %d ,exponent is %d\n",x_m,x_e_u);

	/* Convert from 2's complement */
	if (x_e_u > 15) {
		x_e_u = ((x_e_u ^ 255) + 1) & 0x1F;
		x_e = -x_e_u;
	}
	else {
		x_e = x_e_u;
	}

	x_e = -x_e;

	//printf ("Exponent after adjustment %d  \n",x_e);

	exp_v = 1;
	//x_p = 1/exp2((float)x_e);
	for (i=0;i<x_e;i++)
		exp_v = exp_v * 2;

	x_p = 1.0/(float)exp_v;
	//printf ("x_p is %f  \n",x_p);
	return ((float)x_m)*x_p;
}



float readVoltage(int iic_fd, unsigned char deviceAddress, unsigned char pageAddress) {
	float voltage;
	int status;

	if (ioctl(iic_fd, I2C_SLAVE, deviceAddress) < 0) {
		printf("ERROR 01: Unable to set I2C slave address 0x%02X\n", deviceAddress);
		exit(1);
		//usleep(100);
		return -1;
	}

	status = i2c_smbus_write_byte_data(iic_fd, CMD_PAGE, pageAddress);
	if (status < 0) {
		printf("ERROR 02: Unable to write page address to I2C slave at 0x%02X: %d\n", deviceAddress, status);
		exit(1);
		//usleep(100);
		return -1;
	}

	/* Read in the voltage value */
	status = i2c_smbus_read_word_data(iic_fd, CMD_READ_VOUT);
	if(status < 0) {
		printf("ERROR 03: Unable to read VOUT on I2C slave at 0x%02X: %d\n", deviceAddress, status);
		exit(1);
//		usleep(100);
		return -1;
	}

	voltage = status / 4096.0f;
	return voltage;
}

float readCurrent(int iic_fd, unsigned char deviceAddress, unsigned char pageAddress) {
	double current;
	int status;

	if (ioctl(iic_fd, I2C_SLAVE, deviceAddress) < 0) {
		printf("ERROR 04: Unable to set I2C slave address 0x%02X\n", deviceAddress);
		exit(1);
//		usleep(100);
		return -1;
	}

	status = i2c_smbus_write_byte_data(iic_fd, CMD_PAGE, pageAddress);
	if (status < 0) {
		printf("ERROR 05: Unable to write page address to I2C slave at 0x%02X: %d\n", deviceAddress, status);
		exit(1);
	//	usleep(100);
		return -1;
	}

	/* Read in the voltage value */
	status = i2c_smbus_read_word_data(iic_fd, CMD_READ_IOUT);
	if(status < 0) {
		printf("ERROR 06: Unable to read IOUT on I2C slave at 0x%02X: %d\n", deviceAddress, status);
		exit(1);
		//usleep(100);
		return -1;
	}

	/* We have to decode the LINEAR11 format. The format is composed of a 16-bit
	 * value with an 11-bit mantissa and a 5-bit exponent. The mantissa has 10
	 * significant bits with a sign bit allowing for values between -1024 and +1023.
	 * The exponent has four significant bits plus one sign bit allowing for exponent
	 * values between -16 to +15, or a full range of 2^-16 to 1023*2^15
	 */
	//current = linear11ToFloat((unsigned char)((status >> 8) & 0xff), (unsigned char)(status & 0xff));
	current = convert_pmbus_reading((uint16_t)status);
	return current;
}

float scale_voltage(int iic_fd, unsigned char device_address, unsigned char page, float desired_voltage) {

	int status;
    float sample_voltage;
    int k = 0;
    __u16 VOUT_MAX,VOUT_OV_FAULT_LIMIT,VOUT_OV_WARN_LIMIT,VOUT_MARGIN_HIGH,VOUT_COMMAND,
              VOUT_MARGIN_LOW,POWER_GOOD_ON,VOUT_UV_WARN_LIMIT,VOUT_UV_FAULT_LIMIT,POWER_GOOD_OFF, IOUT_OC_LV_FAULT_LIMIT;
    float voltage_min;
    float voltage_max;

    if (device_address ==  VCCINT_DEVICE && page == VCCINT_PAGE) {
    	voltage_min =  VCCINT_VOLTAGE_MIN;
		voltage_max =  VCCINT_VOLTAGE_MAX;
    } else if (device_address ==  VCCPINT_DEVICE && page == VCCPINT_PAGE) {
    	voltage_min =  VCCPINT_VOLTAGE_MIN;
		voltage_max =  VCCPINT_VOLTAGE_MAX;
    } else if (device_address ==  VCC1V5_DEVICE && page == VCC1V5_PAGE) {
    	voltage_min =  VCC1V5_VOLTAGE_MIN;
		voltage_max =  VCC1V5_VOLTAGE_MAX;
    } else  {
    	printf("scale_voltage: voltage of the selected rail cannot be changed\n");
    	return 0;
    }
	if (desired_voltage <= voltage_max && desired_voltage >= voltage_min) {
        VOUT_MAX =(__u16)(desired_voltage*1.6*4096);
        VOUT_OV_FAULT_LIMIT =(__u16)(desired_voltage*1.1*4096);
        VOUT_OV_WARN_LIMIT=(__u16)(desired_voltage*1.075*4096);
        VOUT_MARGIN_HIGH=(__u16)(desired_voltage*1.05*4096);
        VOUT_COMMAND=(__u16)(desired_voltage*4096);
        VOUT_MARGIN_LOW=(__u16)(desired_voltage*0.95*4096);
        POWER_GOOD_ON=(__u16)(desired_voltage*0.925*4096);
        VOUT_UV_WARN_LIMIT=(__u16)(desired_voltage*0.925*4096);
        VOUT_UV_FAULT_LIMIT=(__u16)(desired_voltage*0.9*4096);
        POWER_GOOD_OFF=(__u16)(desired_voltage*0.9*4096);
	    IOUT_OC_LV_FAULT_LIMIT = (__u16)(desired_voltage*0.9*4096);
        //printf("scale_voltage:Desired Voltage is %f\n", desired_voltage,'v');


        sample_voltage=readVoltage(iic_fd, device_address, page);

        while(k++ < 10 && sample_voltage < 0) {
        	sample_voltage=readVoltage(iic_fd, device_address, page);
        }

        if(sample_voltage < 0) {
        	printf("scale_voltage: ERROR 07-00: cannot read voltage\n");
        	exit(1);
        }

        if (ioctl(iic_fd, I2C_SLAVE, device_address) < 0) {
        	printf("scale_voltage: ERROR 07: Unable to set I2C slave address 0x%02X\n", device_address);
        	exit(1);
        }


        status = i2c_smbus_write_byte_data(iic_fd, CMD_PAGE, page);
        if (status < 0) {
        	printf("scale_voltage: ERROR 08: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        	exit(1);
        }

        /* Write in the voltage value */
        if (sample_voltage > desired_voltage){
        	// SET POWER MANAGER: POWER_GOOD_OFF = 0x0CF5
        	status = i2c_smbus_write_word_data(iic_fd,0x5F,POWER_GOOD_OFF);
        	if (status < 0) {
        		printf("ERROR 09: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
//        	usleep(1000);
        	// SET POWER MANAGER: IOUT_OC_LV_FAULT_LIMIT = 0x0CF5
        	status = i2c_smbus_write_word_data(iic_fd,0x48,IOUT_OC_LV_FAULT_LIMIT);
        	if (status < 0) {
        		printf("ERROR 10: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_UV_FAULT_LIMIT = 0x0CF5
        	status = i2c_smbus_write_word_data(iic_fd,0x44,VOUT_UV_FAULT_LIMIT);
        	if (status < 0) {
        		printf("ERROR 11: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_UV_WARN_LIMIT = 0x0D53
        	status = i2c_smbus_write_word_data(iic_fd,0x43,VOUT_UV_WARN_LIMIT);
        	if (status < 0) {
        		printf("ERROR 12: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: POWER_GOOD_ON = 0x0D53
        	status = i2c_smbus_write_word_data(iic_fd,0x5E,POWER_GOOD_ON);
        	if (status < 0) {
        		printf("ERROR 13: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_MARGINE_LOW = 0x0DAE
        	status = i2c_smbus_write_word_data(iic_fd,0x26,VOUT_MARGIN_LOW);
        	if (status < 0) {
        		printf("ERROR 14: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_COMMAND = 0x0E66
        	status = i2c_smbus_write_word_data(iic_fd,0x21,VOUT_COMMAND);
        	if (status < 0) {
        		printf("ERROR 15: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	usleep(4000);

        	// SET POWER MANAGER: VOUT_MARGIN_HIGH = 0x0F1E
        	status = i2c_smbus_write_word_data(iic_fd,0x25,VOUT_MARGIN_HIGH);
        	if (status < 0) {
        		printf("ERROR 16: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_OV_WARN_LIMIT = 0x0F7C
        	status = i2c_smbus_write_word_data(iic_fd,0x42,VOUT_OV_WARN_LIMIT);
        	if (status < 0) {
        		printf("ERROR 17: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_OV_FAULT_LIMIT = 0x0FD7
        	status = i2c_smbus_write_word_data(iic_fd,0x40,VOUT_OV_FAULT_LIMIT);
        	if (status < 0) {
        		printf("ERROR 18: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_MAX = 0x170A
        	status = i2c_smbus_write_word_data(iic_fd,0x24,VOUT_MAX);
        	if (status < 0) {
        		printf("ERROR 19: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        } else {
        	// SET POWER MANAGER: VOUT_MAX = 0x170A
        	status = i2c_smbus_write_word_data(iic_fd,0x24,VOUT_MAX);
        	if (status < 0) {
        		printf("ERROR 20: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_OV_FAULT_LIMIT = 0x0FD7
        	status = i2c_smbus_write_word_data(iic_fd,0x40,VOUT_OV_FAULT_LIMIT);
        	if (status < 0) {
        		printf("ERROR 21: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_OV_WARN_LIMIT = 0x0F7C
        	status = i2c_smbus_write_word_data(iic_fd,0x42,VOUT_OV_WARN_LIMIT);
        	if (status < 0) {
        		printf("ERROR 22: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_MARGIN_HIGH = 0x0F1E
        	status = i2c_smbus_write_word_data(iic_fd,0x25,VOUT_MARGIN_HIGH);
        	if (status < 0) {
        		printf("ERROR 23: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_COMMAND = 0x0E66
        	status = i2c_smbus_write_word_data(iic_fd,0x21,VOUT_COMMAND);
        	if (status < 0) {
        		printf("ERROR 24: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	usleep(4000);
        	// SET POWER MANAGER: VOUT_MARGINE_LOW = 0x0DAE
        	status = i2c_smbus_write_word_data(iic_fd,0x26,VOUT_MARGIN_LOW);
        	if (status < 0) {
        		printf("ERROR 25: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: POWER_GOOD_ON = 0x0D53
        	status = i2c_smbus_write_word_data(iic_fd,0x5E,POWER_GOOD_ON);
        	if (status < 0) {
        		printf("ERROR 26: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_UV_WARN_LIMIT = 0x0D53
        	status = i2c_smbus_write_word_data(iic_fd,0x43,VOUT_UV_WARN_LIMIT);
        	if (status < 0) {
        		printf("ERROR 27: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: IOUT_OC_LV_FAULT_LIMIT = 0x0CF5
        	status = i2c_smbus_write_word_data(iic_fd,0x48,IOUT_OC_LV_FAULT_LIMIT);
        	if (status < 0) {
        		printf("ERROR 28: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: VOUT_UV_FAULT_LIMIT = 0x0CF5
        	status = i2c_smbus_write_word_data(iic_fd,0x44,VOUT_UV_FAULT_LIMIT);
        	if (status < 0) {
        		printf("ERROR 29: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        	// SET POWER MANAGER: POWER_GOOD_OFF = 0x0CF5
        	status = i2c_smbus_write_word_data(iic_fd,0x5F,POWER_GOOD_OFF);
        	if (status < 0) {
        		printf("ERROR 30: Unable to write page address to I2C slave at 0x%02X: %d\n", device_address, status);
        		exit(1);
        	}
        	//usleep(1000);
        }
	}
}

/*
float scale_voltage_back(int iic_fd, unsigned char device, unsigned char page, float desired_voltage) {

	int status;
        float sample_voltage;
        __u16 VOUT_MAX,VOUT_OV_FAULT_LIMIT,VOUT_OV_WARN_LIMIT,VOUT_MARGIN_HIGH,VOUT_COMMAND,
              VOUT_MARGIN_LOW,POWER_GOOD_ON,VOUT_UV_WARN_LIMIT,VOUT_UV_FAULT_LIMIT,POWER_GOOD_OFF, IOUT_OC_LV_FAULT_LIMIT;

        if (desired_voltage <=1 && desired_voltage >=0.6) {
//		  if (desired_voltage <=1 && desired_voltage >=0.0) {
           VOUT_MAX =(__u16)(desired_voltage*1.6*4096);
           VOUT_OV_FAULT_LIMIT =(__u16)(desired_voltage*1.1*4096);
           VOUT_OV_WARN_LIMIT=(__u16)(desired_voltage*1.075*4096);
           VOUT_MARGIN_HIGH=(__u16)(desired_voltage*1.05*4096);
           VOUT_COMMAND=(__u16)(desired_voltage*4096);
           VOUT_MARGIN_LOW=(__u16)(desired_voltage*0.95*4096);
           POWER_GOOD_ON=(__u16)(desired_voltage*0.925*4096);
           VOUT_UV_WARN_LIMIT=(__u16)(desired_voltage*0.925*4096);
           VOUT_UV_FAULT_LIMIT=(__u16)(desired_voltage*0.9*4096);
           POWER_GOOD_OFF=(__u16)(desired_voltage*0.9*4096);
	   IOUT_OC_LV_FAULT_LIMIT = (__u16)(desired_voltage*0.9*4096);
           printf("Desired Voltage is %f\n", desired_voltage,'v');

        sample_voltage=readVoltage(iic_fd, 52, 0);


	if (ioctl(iic_fd, I2C_SLAVE, 52) < 0) {
		printf("ERROR: Unable to set I2C slave address 0x%02X\n", 52);
		exit(1);
	}

	status = i2c_smbus_write_byte_data(iic_fd, CMD_PAGE, 0);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}

        // Write in the voltage value
        if (sample_voltage > desired_voltage){


	// SET POWER MANAGER: POWER_GOOD_OFF = 0x0CF5
	status = i2c_smbus_write_word_data(iic_fd,0x5F,POWER_GOOD_OFF);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
	// SET POWER MANAGER: IOUT_OC_LV_FAULT_LIMIT = 0x0CF5
	status = i2c_smbus_write_word_data(iic_fd,0x48,IOUT_OC_LV_FAULT_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_UV_FAULT_LIMIT = 0x0CF5
	status = i2c_smbus_write_word_data(iic_fd,0x44,VOUT_UV_FAULT_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_UV_WARN_LIMIT = 0x0D53
	status = i2c_smbus_write_word_data(iic_fd,0x43,VOUT_UV_WARN_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: POWER_GOOD_ON = 0x0D53
	status = i2c_smbus_write_word_data(iic_fd,0x5E,POWER_GOOD_ON);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_MARGINE_LOW = 0x0DAE
	status = i2c_smbus_write_word_data(iic_fd,0x26,VOUT_MARGIN_LOW);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_COMMAND = 0x0E66
   	status = i2c_smbus_write_word_data(iic_fd,0x21,VOUT_COMMAND);
   	if (status < 0) {
   		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
   		exit(1);
   	}
        // SET POWER MANAGER: VOUT_MARGIN_HIGH = 0x0F1E
	status = i2c_smbus_write_word_data(iic_fd,0x25,VOUT_MARGIN_HIGH);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
       // SET POWER MANAGER: VOUT_OV_WARN_LIMIT = 0x0F7C
	status = i2c_smbus_write_word_data(iic_fd,0x42,VOUT_OV_WARN_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_OV_FAULT_LIMIT = 0x0FD7
	status = i2c_smbus_write_word_data(iic_fd,0x40,VOUT_OV_FAULT_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_MAX = 0x170A
	status = i2c_smbus_write_word_data(iic_fd,0x24,VOUT_MAX);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        }
        else {
        // SET POWER MANAGER: VOUT_MAX = 0x170A
	status = i2c_smbus_write_word_data(iic_fd,0x24,VOUT_MAX);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_OV_FAULT_LIMIT = 0x0FD7
	status = i2c_smbus_write_word_data(iic_fd,0x40,VOUT_OV_FAULT_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
       // SET POWER MANAGER: VOUT_OV_WARN_LIMIT = 0x0F7C
	status = i2c_smbus_write_word_data(iic_fd,0x42,VOUT_OV_WARN_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_MARGIN_HIGH = 0x0F1E
	status = i2c_smbus_write_word_data(iic_fd,0x25,VOUT_MARGIN_HIGH);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_COMMAND = 0x0E66
	status = i2c_smbus_write_word_data(iic_fd,0x21,VOUT_COMMAND);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_MARGINE_LOW = 0x0DAE
	status = i2c_smbus_write_word_data(iic_fd,0x26,VOUT_MARGIN_LOW);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: POWER_GOOD_ON = 0x0D53
	status = i2c_smbus_write_word_data(iic_fd,0x5E,POWER_GOOD_ON);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_UV_WARN_LIMIT = 0x0D53
	status = i2c_smbus_write_word_data(iic_fd,0x43,VOUT_UV_WARN_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
	// SET POWER MANAGER: IOUT_OC_LV_FAULT_LIMIT = 0x0CF5
	status = i2c_smbus_write_word_data(iic_fd,0x48,IOUT_OC_LV_FAULT_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: VOUT_UV_FAULT_LIMIT = 0x0CF5
	status = i2c_smbus_write_word_data(iic_fd,0x44,VOUT_UV_FAULT_LIMIT);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}
        // SET POWER MANAGER: POWER_GOOD_OFF = 0x0CF5
	status = i2c_smbus_write_word_data(iic_fd,0x5F,POWER_GOOD_OFF);
	if (status < 0) {
		printf("ERROR: Unable to write page address to I2C slave at 0x%02X: %d\n", 52, status);
		exit(1);
	}

   	}
  }
 }
*/



int monitor(void)
{
	float voltage;
	double current;
	double power;
	double maxpower;
	int i, j,k;
	
    int iic_fd;


	double totalPower = 0;
	const int count = 50;
  
	iic_fd = open("/dev/i2c-8", O_RDWR);
	if (iic_fd < 0) {
		printf("ERROR 31: Unable to open /dev/i2c-8 for PMBus access: %d\n", iic_fd);
		exit(1);
	}  

	j = sizeof(zc702_rails) / sizeof(struct voltage_rail);




	maxpower = 0.0f;	


	printf("%c[2J",27);
	while(1){


	totalPower = 0.0f;
	power = 0.0f;
	for(i = 0; i < j; i++) {
		zc702_rails[i].average_power = 0;
		zc702_rails[i].average_current=0;
	}
	printf("\033[?1049h\033[H");
	printf("|---------------------------------------------------------------|\n");
	printf("|                          Power Monitor APP                    |\n");
	printf("|RAIL            |  Voltage(V)   |   Current(mA)  |   Power(mW) |\n");
	printf("|---------------------------------------------------------------|\n");


	for(k = 0; k < count; k++) {
	for(i = 0; i < j; i++) {
		voltage = readVoltage(iic_fd, zc702_rails[i].device, zc702_rails[i].page);
		current = readCurrent(iic_fd, zc702_rails[i].device, zc702_rails[i].page);
		power = voltage * current * 1000/count;
		totalPower += power;
		zc702_rails[i].average_current += current/count;
		zc702_rails[i].average_power += power;
		if(k == count-1)
			printf("|%s \t | %f V\t | %f \t|   %.4f \t|\n",zc702_rails[i].name,voltage,zc702_rails[i].average_current* 1000,zc702_rails[i].average_power);

		}

	    if (maxpower < totalPower ){
	       maxpower= totalPower;
	    }

	}

	    printf("|---------------------------------------------------------------|\n");
	    printf("|TOTAL POWER  %f mW\t  | MAX POWER  %f mW |\n",totalPower,maxpower);

	    fflush(stdout);
	    usleep( 500 * 1000 );
}
	close(iic_fd);

	return 0;

}






