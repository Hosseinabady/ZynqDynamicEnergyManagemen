
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/ioctl.h>		/* ioctl */
#include <sys/mman.h>
#include <signal.h>
#include <fpgacl_device_driver.h>
#include <set_frequency.h>
#include "accel.h"

#define DEVICE_NAME_WITH_PATH    "/dev/fpga_dev"




FILE *file;
FILE *fp;
int file_desc;

register_control_status_command_type *rd_command;

u32 device_kernel_address;


static void
accelerator_finished(int sig, siginfo_t *siginfo, void *context)		/* argument is signal number */
{
//	double tc = getTimestamp();
//	printf ("Sending PID: %ld, UID: %ld at %f\n", (long)siginfo->si_pid, (long)siginfo->si_uid, tc);
//	printf ("accelerator_finished:\n");
	return;
}

void accel_prologue() {
//	printf("accel_prologue ceck point 1\n");

	struct sigaction act;
	memset (&act, '\0', sizeof(act));
	act.sa_sigaction = &accelerator_finished;
	act.sa_flags = SA_SIGINFO;


	if (sigaction(SIGUSR1, &act, NULL) < 0)
		printf("can't catch SIGUSR1\n");


	file_desc = open(DEVICE_NAME_WITH_PATH, O_RDWR);
    if (file_desc < 0) {
        printf("Can't open device file :%s\n", DEVICE_NAME_WITH_PATH);
        exit(-1);
    }



    rd_command = (register_control_status_command_type*)malloc(sizeof(register_control_status_command_type));
    u32 process_id = getpid();

    printf("accel_prologue: process_id = %d\n", process_id);
    printf("accel_prologue: process_id = %d\n", (u32)rd_command);

	rd_command->device_physical_base_address = ACCELERATOR;
	rd_command->irq_num = 61;
	rd_command->process_id = process_id;
	device_kernel_address = ioctl (file_desc, FPGACL_REGISTER_DEVICE, rd_command);


    printf("accel_prologue ceck point 3\n");

}

void accel_epilogue() {
	printf("check point accel_epilogue 1\n");

	free(rd_command);

	close(file_desc);

}

void  accel_write(
				unsigned char 	*map_sw,
				int             *p_x,
				int             *p_y,

				int   			*robotPose_sw_dx,
				int   			*robotPose_sw_dy,
				float   		*robotPose_sw_theta,

				int             *old_sw_dx,
				int             *old_sw_dy,
				float           *old_sw_theta,


				int             *bestTransformation_sw_dx,
				int             *bestTransformation_sw_dy,
				float           *bestTransformation_sw_theta
		)
{

//	printf("accel_write: ceck point 1\n");

	u32_int_uint_conversion robotPose_sw_dx_value;
	robotPose_sw_dx_value.i = *robotPose_sw_dx;

	u32_int_uint_conversion robotPose_sw_dy_value;
	robotPose_sw_dy_value.i = *robotPose_sw_dy;

	u32_float_conversion  robotPose_sw_theta_value;
	robotPose_sw_theta_value.f = *robotPose_sw_theta;



	u32_int_uint_conversion old_sw_dx_value;
	old_sw_dx_value.i = *old_sw_dx;

	u32_int_uint_conversion old_sw_dy_value;
	old_sw_dy_value.i = *old_sw_dy;

	u32_float_conversion  old_sw_theta_value;
	old_sw_theta_value.f = *old_sw_theta;


	u32_int_uint_conversion bestTransformation_sw_dx_value;
	bestTransformation_sw_dx_value.i = *bestTransformation_sw_dx;

	u32_int_uint_conversion bestTransformation_sw_dy_value;
	bestTransformation_sw_dy_value.i = *bestTransformation_sw_dy;

	u32_float_conversion  bestTransformation_sw_theta_value;
	bestTransformation_sw_theta_value.f = *bestTransformation_sw_theta;

  	//=======================HP0-0 write command========================================================
  	//---------------------------------------
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_MAP_SW_DATA;
	rd_command->value = (u32)(map_sw);
	rd_command->pointer = 1;
	rd_command->direction=1;
	//rd_command->size_type = sizeof(unsigned char);
	rd_command->size_type = sizeof(unsigned char);


	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_P_X_DATA;
	rd_command->value = (u32)(p_x);
	rd_command->pointer = 1;
	rd_command->direction=1;
	//rd_command->size_type = sizeof(unsigned char);
	rd_command->size_type = sizeof(int);


	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_P_Y_DATA;
	rd_command->value = (u32)(p_y);
	rd_command->pointer = 1;
	rd_command->direction=1;
	//rd_command->size_type = sizeof(unsigned char);
	rd_command->size_type = sizeof(int);


	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------




	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_ROBOTPOSE_DX_I_DATA;
	rd_command->value = (u32)(robotPose_sw_dx_value.u);
	rd_command->pointer = 0;
	rd_command->direction=0;
	rd_command->size_type = sizeof(int);


	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_ROBOTPOSE_DY_I_DATA;
	rd_command->value = (u32)(robotPose_sw_dy_value.u);
	rd_command->pointer = 0;
	rd_command->direction=0;
	rd_command->size_type = sizeof(int);


	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_ROBOTPOSE_THETA_I_DATA;
	rd_command->value = (u32)(robotPose_sw_theta_value.u);
	rd_command->pointer = 0;
	rd_command->direction=0;
	rd_command->size_type = sizeof(float);


	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_BESTTRANSFORMATION_DX_I_DATA;
	rd_command->value = (u32)(bestTransformation_sw_dx_value.u);
	rd_command->pointer = 0;
	rd_command->direction=0;
	rd_command->size_type = sizeof(float);


	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_BESTTRANSFORMATION_DY_I_DATA;
	rd_command->value = (u32)(bestTransformation_sw_dy_value.u);
	rd_command->pointer = 0;
	rd_command->direction=0;
	rd_command->size_type = sizeof(int);

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_BESTTRANSFORMATION_THETA_I_DATA;
	rd_command->value = (u32)(bestTransformation_sw_theta_value.u);
	rd_command->pointer = 0;
	rd_command->direction=0;
	rd_command->size_type = sizeof(int);

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_OLD_SW_DX_DATA;
	rd_command->value = (u32)(old_sw_dx_value.u);
	rd_command->pointer = 0;
	rd_command->direction=0;
	rd_command->size_type = sizeof(int);

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------


	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_OLD_SW_DY_DATA;
	rd_command->value = (u32)(old_sw_dy_value.u);
	rd_command->pointer = 0;
	rd_command->direction=0;
	rd_command->size_type = sizeof(int);

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_OLD_SW_THETA_DATA;
	rd_command->value = (u32)(old_sw_theta_value.u);
	rd_command->pointer = 0;
	rd_command->direction=0;
	rd_command->size_type = sizeof(int);

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------


}


void  accel_read(
		int            *robotPose_dx,
		int            *robotPose_dy,
		float          *robotPose_theta,
		int            *bestTransformation_dx,
		int            *bestTransformation_dy,
		float          *bestTransformation_theta
		)
{


	u32_int_uint_conversion   robotPose_dx_value;
	u32_int_uint_conversion   robotPose_dy_value;
	u32_float_conversion      robotPose_theta_value;


	u32_int_uint_conversion   bestTransformation_dx_value;
	u32_int_uint_conversion   bestTransformation_dy_value;
	u32_float_conversion      bestTransformation_theta_value;


  	//=======================read command========================================================
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_ROBOTPOSE_DX_O_DATA;

	robotPose_dx_value.u = ioctl ( file_desc, FPGACL_DEVICE_IOREAD, rd_command);
	*robotPose_dx = robotPose_dx_value.i;
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_ROBOTPOSE_DY_O_DATA;

	robotPose_dy_value.u = ioctl ( file_desc, FPGACL_DEVICE_IOREAD, rd_command);
	*robotPose_dy = robotPose_dy_value.i;
  	//---------------------------------------


	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_ROBOTPOSE_THETA_O_DATA;

	robotPose_theta_value.u = ioctl ( file_desc, FPGACL_DEVICE_IOREAD, rd_command);
	*robotPose_theta = robotPose_theta_value.f;
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_BESTTRANSFORMATION_DX_O_DATA;

	bestTransformation_dx_value.u = ioctl ( file_desc, FPGACL_DEVICE_IOREAD, rd_command);
	*bestTransformation_dx = bestTransformation_dx_value.i;
  	//---------------------------------------

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_BESTTRANSFORMATION_DY_O_DATA;

	bestTransformation_dy_value.u = ioctl ( file_desc, FPGACL_DEVICE_IOREAD, rd_command);
	*bestTransformation_dy = bestTransformation_dy_value.i;
  	//---------------------------------------


	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_BESTTRANSFORMATION_THETA_O_DATA;

	bestTransformation_theta_value.u = ioctl ( file_desc, FPGACL_DEVICE_IOREAD, rd_command);
	*bestTransformation_theta = bestTransformation_theta_value.f;
  	//---------------------------------------

}


void  accel_start( ) {
//	printf("accel_start: ceck point 1\n");
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_GIE;
	rd_command->value = 0;
  	ioctl ( file_desc, FPGACL_INTERRUPT_ENABLE, rd_command);

  	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_AP_CTRL;
	rd_command->value = 0;
	ioctl ( file_desc, FPGACL_START, rd_command);
}



void  accel_ready() {
	printf("accel_wait: ceck point 1\n");
	u32 isIdle = 0;
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_AP_CTRL;
	rd_command->value = 0;
	isIdle  =  ioctl ( file_desc, FPGACL_CTRL_READY, rd_command);

	while (!isIdle) {
		printf("accel_wait: ceck point 2\n");
		sleep(1);
		isIdle  =   ioctl ( file_desc, FPGACL_CTRL_READY, rd_command);
	}

}


void  accel_wait() {
//	printf("accel_wait: ceck point 1\n");
	u32 isIdle = 0;
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XRUNITERATION_HW_BUS_CONTROL_ADDR_AP_CTRL;
	rd_command->value = 0;
	isIdle  =  ioctl ( file_desc, FPGACL_CTRL_DONE, rd_command);

	while (!isIdle) {
		isIdle  =   ioctl ( file_desc, FPGACL_CTRL_DONE, rd_command);
	}

}

double getTimestamp() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}


void* fpgacl_malloc(unsigned long int size) {
	void* user_var;

	user_var = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED| MAP_LOCKED, file_desc, 0);
	if (user_var == MAP_FAILED)	{
		perror("file_desc:--");
		exit(-1);
	}

	return user_var;
}

void fpgacl_free(void* user_var) {

	ioctl ( file_desc, FPGACL_MEMFREE, user_var);
}



