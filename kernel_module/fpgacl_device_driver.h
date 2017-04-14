/*
 * fpga_device_driver.h
 *
 *  Created on: 10 Nov 2014
 *      Author: csxmh
 */

#ifndef FPGACL_DEVICE_DRIVER_H_
#define FPGACL_DEVICE_DRIVER_H_





#define DEVICE_NAME                                        "fpgacl_device"

#define FPGACL_DEVICE_NO_PORT                              1024


#define FPGACL_IOC_MAGIC                                   1000
#define FPGACL_DEVICE_IOWRITE                             _IOW(FPGACL_IOC_MAGIC, 0, int)
#define FPGACL_DEVICE_IOREAD                              _IOW(FPGACL_IOC_MAGIC, 1, int)
#define FPGACL_START                                      _IOW(FPGACL_IOC_MAGIC, 2, int)
#define FPGACL_CTRL_READY								  _IOW(FPGACL_IOC_MAGIC, 3, int)
#define FPGACL_CTRL_DONE                                  _IOW(FPGACL_IOC_MAGIC, 4, int)
#define FPGACL_INTERRUPT_ENABLE                           _IOW(FPGACL_IOC_MAGIC, 5, int)
#define FPGACL_REGISTER_DEVICE                            _IOW(FPGACL_IOC_MAGIC, 6, int)

#define FPGACL_IOC_MAGIC_MEM_ALLOC                        2400
#define FPGACL_MEMALLOC                                  _IOW(FPGACL_IOC_MAGIC_MEM_ALLOC, 0, int)
#define FPGACL_MEMFREE                                   _IOW(FPGACL_IOC_MAGIC_MEM_ALLOC, 1, int)

struct argument_parameters_struct {
	unsigned int  size;
	unsigned int  type_size;
	unsigned int  register_kernel_base_address;
	unsigned int  register_physical_offset_address;
	unsigned int  index;
	long unsigned int irq_num;
	unsigned int  process_id;
};
typedef struct argument_parameters_struct argument_parameters_type;
//=========================================================================================
struct register_control_status_command_struct {
	void*             device_kernel_base_address;
	long unsigned int device_physical_base_address;
	long unsigned int register_physical_offset_address;
	long unsigned int irq_num;
	long unsigned int value;
	unsigned int  process_id;
};
typedef struct register_control_status_command_struct register_control_status_command_type;
//=============================================================





#endif /* FPGACL_DEVICE_DRIVER_H_ */
