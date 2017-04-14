
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
    fpgacl_open();


    rd_command = (register_control_status_command_type*)malloc(sizeof(register_control_status_command_type));
    u32 process_id = getpid();

    printf("accel_prologue: process_id = %d\n", process_id);

	rd_command->device_physical_base_address = ACCELERATOR;
	rd_command->irq_num = 61;
	rd_command->process_id = process_id;
	device_kernel_address = ioctl ( file_desc, FPGACL_REGISTER_DEVICE, rd_command);


     //   printf("accel_prologue ceck point 3\n");

}

void accel_epilogue() {
	printf("check point accel_epilogue 1\n");

	free(rd_command);
	fpgacl_close();
	close(file_desc);

}

void  accel_write(	int n,
					int m,
					DATA_TYPE *  a,
					DATA_TYPE *  b,
					DATA_TYPE *  c
				 )
{


//	printf("accel_write: ceck point 1\n");


  	//=======================HP0-0 write command========================================================
  	//---------------------------------------
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XMXV_STREAM_CONTROL_BUS_ADDR_A_OFFSET_ADDRESS_DATA;
	rd_command->value = (u32)(a)/4;

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XMXV_STREAM_CONTROL_BUS_ADDR_B_OFFSET_ADDRESS_DATA;
	rd_command->value = (u32)(b)/4;

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XMXV_STREAM_CONTROL_BUS_ADDR_C_OFFSET_ADDRESS_DATA;
	rd_command->value = (u32)(c)/4;

	ioctl ( file_desc, FPGACL_DEVICE_IOWRITE, rd_command);
  	//---------------------------------------


	//================================================================================================
//	printf("accel_write: ceck point 2\n");


//	printf("accel_write: ceck point 3\n");

}


void  accel_start( ) {
//	printf("accel_start: ceck point 1\n");
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XMXV_STREAM_CONTROL_BUS_ADDR_GIE;
	rd_command->value = 0;
  	ioctl ( file_desc, FPGACL_INTERRUPT_ENABLE, rd_command);

  	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XMXV_STREAM_CONTROL_BUS_ADDR_AP_CTRL;
	rd_command->value = 0;
	ioctl ( file_desc, FPGACL_START, rd_command);
}



void  accel_ready()
{
	printf("accel_wait: ceck point 1\n");
	u32 isIdle = 0;
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XMXV_STREAM_CONTROL_BUS_ADDR_AP_CTRL;
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
//	printf("accel_wait: ceck point 1\n");
	u32 isIdle = 0;
	rd_command->device_kernel_base_address     = (void *)device_kernel_address;
	rd_command->register_physical_offset_address = XMXV_STREAM_CONTROL_BUS_ADDR_AP_CTRL;
	rd_command->value = 0;
	isIdle  =  ioctl ( file_desc, FPGACL_CTRL_DONE, rd_command);

	while (!isIdle) {
		isIdle  =   ioctl ( file_desc, FPGACL_CTRL_DONE, rd_command);;
	}

}

double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}
