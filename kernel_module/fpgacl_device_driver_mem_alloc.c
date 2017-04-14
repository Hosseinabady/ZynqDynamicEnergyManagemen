/*
author: Mohamamd Hosseinabady
email:  mohammad@hosseinabady.com, m.hosseinabady@bristol.ac.uk
*/


#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <asm/page.h>
#include <linux/dma-mapping.h>
#include "fpgacl_device_driver.h"

MODULE_LICENSE("Dual BSD/GPL");

static struct class *enpower_opencl_mohammad_memalloc_cl;


struct allocated_memory_struct {
	u32   physical_address;
	void* kernel_address;
	u32   size;
	struct allocated_memory_struct* next;
};

typedef struct allocated_memory_struct allocated_memory_type;

allocated_memory_type *allocated_memory_head;
allocated_memory_type *allocated_memory_tail;

dev_t        dev_numbers_memalloc;
struct cdev* enpower_opencl_mohammad_cdev_memalloc;
static int   enpower_opencl_mohammad_device_open_memalloc = 0;


static int fpga_memalloc(u32 size);
void fpga_memfree(u32 physical_address);
//==========================================================

struct read_write_data_command_struct {
    void*    user_buffer_virtual_address;
    void*    kernel_buffer_physical_address;
    u32      size;
};
typedef struct read_write_data_command_struct read_write_data_command_type;

//==========================================================


static ssize_t  enpower_opencl_mohammad_read_memalloc(struct file * file,	// see include/linux/fs.h
                                                 char __user * buffer,	// buffer to be filled with data
                                                 size_t        length,	        // length of the buffer
                                                 loff_t *      offset) {

	unsigned long status;
	read_write_data_command_type* read_write_command = (read_write_data_command_type *)buffer;
	u32 user_buffer_virtual_address    = (u32)read_write_command->user_buffer_virtual_address;
	u32 kernel_buffer_physical_address = (u32)read_write_command->kernel_buffer_physical_address;
	u32 size                           = (u32)read_write_command->size;

	allocated_memory_type *current_allocated_memory = allocated_memory_head;

	while(current_allocated_memory !=  NULL) {
		if (current_allocated_memory->physical_address == kernel_buffer_physical_address) {
			status = copy_to_user((void *)user_buffer_virtual_address, current_allocated_memory->kernel_address, size);
			if(status){
				printk(KERN_ALERT "enpower_opencl_mohammad_read_memalloc: lengh to be read = %d, remain length = %lu \n\r", size, status);
				printk(KERN_ERR "enpower_opencl_mohammad_read_memalloc: Error: Reading bitstream from userspace failed ! \n\r");
			}

			break;
		}
		current_allocated_memory = current_allocated_memory->next;
	}

	if (current_allocated_memory == NULL)
	{
		printk(KERN_ALERT "enpower_opencl_mohammad_read_memalloc: Error: read data from kernel buffer ! \n\r");
	}

    return 0;
}



static ssize_t enpower_opencl_mohammad_write_memalloc(	struct file *file,
												const char __user * buffer,
												size_t length,
												loff_t * offset) {

	unsigned long status;
	read_write_data_command_type* read_write_command = (read_write_data_command_type *)buffer;
	u32 user_buffer_virtual_address    = (u32)read_write_command->user_buffer_virtual_address;
	u32 kernel_buffer_physical_address = (u32)read_write_command->kernel_buffer_physical_address;
	u32 size                           = (u32)read_write_command->size;

	allocated_memory_type *current_allocated_memory = allocated_memory_head;

	while(current_allocated_memory !=  NULL) {
		if (current_allocated_memory->physical_address == kernel_buffer_physical_address) {
			status = copy_from_user(current_allocated_memory->kernel_address, (void *)user_buffer_virtual_address, size);
			if(status){
				printk(KERN_ALERT "enpower_opencl_mohammad_read_memalloc: lengh to be read = %d, remain length = %lu \n\r", size, status);
				printk(KERN_ERR "enpower_opencl_mohammad_read_memalloc: Error: Reading bitstream from userspace failed ! \n\r");
			}

			break;
		}
		current_allocated_memory = current_allocated_memory->next;
	}

	if (current_allocated_memory == NULL)
	{
		printk(KERN_ALERT "enpower_opencl_mohammad_read_memalloc: Error: read data from kernel buffer ! \n\r");
	}

    return 0;
}




long  enpower_opencl_mohammad_ioctl_memalloc(struct        file *file,	// ditto
		 	                            unsigned int  ioctl_num,	// number and param for ioctl
		                                unsigned long ioctl_param) {  //ioctl_param is INLS

	u32 return_value;
	u32 physical_address;

    switch(ioctl_num) {

    case FPGACL_MEMALLOC:
    	printk(KERN_ALERT "enpower_opencl_mohammad_ioctl_memalloc: allocated memory \n");
    	physical_address = fpga_memalloc(ioctl_param);
    	return_value = physical_address;
    	printk(KERN_ALERT "allocated memory at physical_address 0x%x \n",(u32)return_value );
		break;

    case FPGACL_MEMFREE:
    	printk(KERN_ALERT "free memory at physical_address 0x%x \n",(u32)ioctl_param );
    	fpga_memfree((u32)ioctl_param);
		break;

	default:

		break;

    }

	return return_value;

}


static int enpower_opencl_mohammad_open_memalloc(struct inode *inode, struct file *file) {

    printk(KERN_ALERT "enpower_opencl_mohammad device (%p, %p) opened \n", inode, file);



    return 0;
}



static int enpower_opencl_mohammad_release_memalloc(struct inode *inode, struct file *file){

    enpower_opencl_mohammad_device_open_memalloc--;

    return 0;
}


int enpower_opencl_mohammad_mmap_memalloc(struct file *filp, struct vm_area_struct *vma){

	printk(KERN_ALERT "enpower_opencl_mohammad_mmap_memalloc\n");


	return 0;
}

struct file_operations enpower_opencl_mohammad_fops_memalloc = {
	.owner = THIS_MODULE,
	.read = enpower_opencl_mohammad_read_memalloc,
	.write = enpower_opencl_mohammad_write_memalloc,
	.unlocked_ioctl = enpower_opencl_mohammad_ioctl_memalloc,
	.open = enpower_opencl_mohammad_open_memalloc,
	.release = enpower_opencl_mohammad_release_memalloc,
	.mmap = enpower_opencl_mohammad_mmap_memalloc,
};

static int enpower_opencl_mohammad_init_memalloc(void) {

    int   state;

    char  device_name[]="fpgacl_memalloc";

    state = alloc_chrdev_region(&dev_numbers_memalloc, 0, 1, device_name);
    if(state!=0) {
        printk(KERN_ALERT "failed to register a region dynamically\n");
    } else {
        printk(KERN_ALERT "major number = %d\n", MAJOR(dev_numbers_memalloc));
    }

    if ((enpower_opencl_mohammad_memalloc_cl = class_create(THIS_MODULE, "chardrv_mem")) == NULL) {
    	unregister_chrdev_region(dev_numbers_memalloc, 1);
     return -1;
    }
    if (device_create(enpower_opencl_mohammad_memalloc_cl, NULL, dev_numbers_memalloc, NULL, "fpgacl_memalloc") == NULL) {
    	class_destroy(enpower_opencl_mohammad_memalloc_cl);
    	unregister_chrdev_region(dev_numbers_memalloc, 1);
    	return -1;
     }

    enpower_opencl_mohammad_cdev_memalloc        = cdev_alloc();
    enpower_opencl_mohammad_cdev_memalloc->ops   = &enpower_opencl_mohammad_fops_memalloc;
    enpower_opencl_mohammad_cdev_memalloc->owner = THIS_MODULE;

    cdev_init(enpower_opencl_mohammad_cdev_memalloc, &enpower_opencl_mohammad_fops_memalloc);
    state = cdev_add(enpower_opencl_mohammad_cdev_memalloc, dev_numbers_memalloc , 1);
    if(state < 0) {
        printk(KERN_ALERT "device failed to be added\n");
    }

    allocated_memory_head = NULL;
    allocated_memory_tail = NULL;

    return 0;
}




static int fpga_memalloc(u32 size) {
	void* linux_kernel_memory;
	u32 phys_add;
	allocated_memory_type *mem;
	linux_kernel_memory = dma_alloc_coherent( NULL, size, &phys_add, GFP_KERNEL );
//	linux_kernel_memory = dma_lorenzo_alloc_coherent(NULL, size, &phys_add, GFP_KERNEL);
	if (!linux_kernel_memory) {
		printk(KERN_ALERT "kernel memory allocation failed for argument \n" );
		return -ENODEV;
	} else {
		printk(KERN_ALERT "%d kernel memory allocation success for mem  at address 0x%x\n", size, (u32)phys_add);
    	mem = (allocated_memory_type *)kmalloc(sizeof(allocated_memory_type), GFP_KERNEL);

    	mem->physical_address = phys_add;
    	mem->kernel_address   = linux_kernel_memory;
    	mem->size             = size;
    	mem->next             = NULL;

    	if (allocated_memory_head == NULL) {
    		allocated_memory_head = mem;
    		allocated_memory_tail = mem;
    	} else {
    		allocated_memory_tail->next = mem;
    		allocated_memory_tail       = mem;
    	}
	}

	return phys_add;
}

void fpga_memfree(u32 physical_address) {

	allocated_memory_type *current_allocated_mem = allocated_memory_head;
	allocated_memory_type *tmp;

	if (current_allocated_mem != NULL) {
		if (current_allocated_mem->physical_address == physical_address) {
			dma_free_coherent(NULL, current_allocated_mem->size, current_allocated_mem->kernel_address, current_allocated_mem->physical_address);
			allocated_memory_head=current_allocated_mem->next;
			if (allocated_memory_head==NULL)
				allocated_memory_tail=NULL;
			kfree(current_allocated_mem);
		} else {
			while (current_allocated_mem->next != NULL) {
				if (current_allocated_mem->next->physical_address == physical_address) {
					dma_free_coherent(NULL, current_allocated_mem->next->size, current_allocated_mem->next->kernel_address, current_allocated_mem->next->physical_address);
					break;
				}
				current_allocated_mem = current_allocated_mem->next;
			}
			if (current_allocated_mem->next == NULL) {
				printk(KERN_ALERT "fpga_memfree: Error free unallocated memory! \n");
			} else {
				tmp = current_allocated_mem->next;
				current_allocated_mem->next = current_allocated_mem->next->next;
				kfree(tmp);
			}
		}
	} else {
		printk(KERN_ALERT "fpga_memfree: Error free unallocated memory! \n");
	}
}


static void enpower_opencl_mohammad_exit_memalloc(void) {

	allocated_memory_type *current_allocated_mem = allocated_memory_head;

	while(current_allocated_mem != NULL) {
		allocated_memory_type *tmp = current_allocated_mem;
		current_allocated_mem = current_allocated_mem->next;
		dma_free_coherent(NULL, tmp->size, tmp->kernel_address, tmp->physical_address);
		kfree(tmp);
	}

    cdev_del(enpower_opencl_mohammad_cdev_memalloc);
    device_destroy(enpower_opencl_mohammad_memalloc_cl, dev_numbers_memalloc);
	class_destroy(enpower_opencl_mohammad_memalloc_cl);
    unregister_chrdev_region(dev_numbers_memalloc, 1);

    printk(KERN_ALERT "Bye fpga device driver!\n");


}
module_init(enpower_opencl_mohammad_init_memalloc);
module_exit(enpower_opencl_mohammad_exit_memalloc);
