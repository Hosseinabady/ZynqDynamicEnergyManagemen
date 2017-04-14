#ifndef __FPGACL_MEMORY__
#define __FPGACL_MEMORY__


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/ioctl.h>		/* ioctl */
#include <sys/mman.h>
#include <fpgacl_device_driver.h>


#define DEVICE_NAME_MEMALLOC    "/dev/fpgacl_memalloc"

typedef unsigned long int u32;



void fpgacl_close();
void fpgacl_open();
long int fpgacl_malloc(unsigned long int size);
void fpgacl_free(unsigned long int physical_address);
long int fpgacl_memwrite(void *src, u32 *dst, unsigned long int size);
long int fpgacl_memread(void *dst, u32 *src, unsigned long int size);

u32 getVirtualAddress(u32 physical_address, u32 size) ;

#endif //__FPGACL_MEMORY__
