
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
extern "C" {
#include <fpgacl_memory.h>
}
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

	return;
}

void accel_prologue() {


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
    fpgacl_open();

    rd_command = (register_control_status_command_type*)malloc(sizeof(register_control_status_command_type));
    u32 process_id = getpid();

	rd_command->device_physical_base_address = ACCELERATOR;
	rd_command->irq_num = 61;
	rd_command->process_id = process_id;
	device_kernel_address = ioctl ( file_desc, FPGACL_REGISTER_DEVICE, rd_command);



}

void accel_epilogue() {

	free(rd_command);
	fpgacl_close();

	close(file_desc);

}


void  accel_write(	DATA_TYPE *h_Call, //Call option price
		            DATA_TYPE *h_Put,  //Put option price
		            DATA_TYPE *h_S,    //Current stock price
		            DATA_TYPE *h_X,    //Option strike price
		            DATA_TYPE *h_T,    //Option years
	                u32        optionCount
				 )
{


  	//=======================HP0-0 write command========================================================

	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XBS_STREAM_CONTROL_BUS_ADDR_CALL_OFFSET_DATA;
	rd_command->value = (u32)h_Call/4;

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------
	rd_command->device_kernel_base_address = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XBS_STREAM_CONTROL_BUS_ADDR_PUT_OFFSET_DATA;
	rd_command->value = (u32)h_Put/4;

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------
	rd_command->device_kernel_base_address = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XBS_STREAM_CONTROL_BUS_ADDR_S_OFFSET_DATA;
	rd_command->value = (u32)h_S/4;

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------
	rd_command->device_kernel_base_address = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XBS_STREAM_CONTROL_BUS_ADDR_X_OFFSET_DATA;
	rd_command->value = (u32)h_X/4;

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------
	rd_command->device_kernel_base_address = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XBS_STREAM_CONTROL_BUS_ADDR_T_OFFSET_DATA;
	rd_command->value = (u32)h_T/4;

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------

	//================================================================================================
//	printf("accel_write: ceck point 2\n");
	rd_command->device_physical_base_address = device_kernel_address;
	rd_command->register_physical_offset_address = XBS_STREAM_CONTROL_BUS_ADDR_GIE;
	rd_command->value = 0;
  	ioctl ( file_desc, FPGACL_INTERRUPT_ENABLE, rd_command);

//	printf("accel_write: ceck point 3\n");

}


void  accel_start( ) {
//	printf("accel_start: ceck point 1\n");
	rd_command->device_physical_base_address = device_kernel_address;
	rd_command->register_physical_offset_address = XBS_STREAM_CONTROL_BUS_ADDR_AP_CTRL;
	rd_command->value = 0;
	ioctl ( file_desc, FPGACL_START, rd_command);
}



void  accel_ready()
{
	printf("accel_wait: ceck point 1\n");
	u32 isIdle = 0;
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XBS_STREAM_CONTROL_BUS_ADDR_AP_CTRL;
	rd_command->value = 0;
	isIdle  =  ioctl ( file_desc, FPGACL_CTRL_READY, rd_command);

	while (!isIdle) {
		printf("accel_wait: ceck point 2\n");
		sleep(1);
		isIdle  =   ioctl ( file_desc, FPGACL_CTRL_READY, rd_command);;
	}

}



void  accel_wait()
{

//	printf("accel_wait: ceck point 3\n");
	u32 isIdle = 0;
	rd_command->device_physical_base_address = device_kernel_address;
	rd_command->register_physical_offset_address = XBS_STREAM_CONTROL_BUS_ADDR_AP_CTRL;
	rd_command->value = 0;
	isIdle  =  ioctl ( file_desc, FPGACL_CTRL_DONE, rd_command);

	while (!isIdle) {
		isIdle  =   ioctl ( file_desc, FPGACL_CTRL_DONE, rd_command);
	}



}
double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}
