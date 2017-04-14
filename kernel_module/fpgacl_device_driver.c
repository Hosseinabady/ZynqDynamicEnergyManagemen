/*
author: Mohamamd Hosseinabady
email:  mohammad@hosseinabady.com, m.hosseinabady@bristol.ac.uk
*/

#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/ioport.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
//#include <linux/device.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <asm/page.h>
#include <linux/dma-mapping.h>
#include <asm/siginfo.h>
#include <linux/rcupdate.h>
/* Needed for IO Read/Write Functions */
#include <linux/proc_fs.h> /* Needed for Proc File System Functions */
#include <linux/seq_file.h> /* Needed for Sequence File Operations */
//#include <linux/platform_device.h> /* Needed for Platform Driver Functions */
#include "fpgacl_device_driver.h"
#include <linux/of.h>
#include <linux/irq.h>
#include <linux/of_irq.h>
#include <linux/time.h>
#include <linux/cdev.h>




//static struct platform_device *pdev;
static struct class *enpower_opencl_mohammad_cl;

dev_t        dev_numbers;
struct cdev* enpower_opencl_mohammad_cdev;
static int   enpower_opencl_mohammad_device_open = 0;
struct device *device_fpga;

u32 user_process_pid;
struct task_struct *user_process_struct;
struct siginfo info;

void  *device_kernel_address;
//=============================================================
struct timespec ts_start;
struct timespec ts_end;
struct timespec ts_duration;



//==========================================================

static int register_userspce_process_for_sending_signal(u32 user_process_pid);
static ssize_t  enpower_opencl_mohammad_read(struct file * file, char __user * buffer,	size_t        length,  loff_t *  offset);
static ssize_t enpower_opencl_mohammad_write(	struct file *file, const char __user * buffer, size_t length, loff_t * offset) ;
long  enpower_opencl_mohammad_ioctl(struct        file *file, unsigned int  ioctl_num,	unsigned long ioctl_param);
static int enpower_opencl_mohammad_open(struct inode *inode, struct file *file);
static int enpower_opencl_mohammad_release(struct inode *inode, struct file *file);
static int enpower_register_irq(u32 device_physical_base_address, void  *device_kernel_address);
static void  *enpower_ioremap(long unsigned int device_physical_base_address);
static int enpower_opencl_mohammad_init(void);
static void enpower_opencl_mohammad_exit(void);



//===========================================================

static irqreturn_t isr(int irq,void* dev_id)
{
	u32 int_en;
	u32 state;
	volatile u32 data_cntrl;

	void* device_kernel_base_address = (void*)dev_id;

//	getnstimeofday(&ts_end);
//	ts_duration = timespec_sub(ts_end,ts_start);
//	printk(KERN_ERR "isr = started at %lu\n", ts_duration.tv_nsec);

    state = send_sig_info(SIGUSR1, &info, user_process_struct);    //send the signal
	if (state < 0) {
		printk(KERN_ERR "error sending signal\n\r");
		return -1;
	}

	data_cntrl = ioread32(device_kernel_base_address+0x0);

    int_en = ioread32(device_kernel_base_address+0x4);
    iowrite32(int_en & 0x00, device_kernel_base_address+0x4);

    int_en = ioread32(device_kernel_base_address+0x08);
    iowrite32(int_en & 0x00, device_kernel_base_address+0x08);

    iowrite32(0x01, device_kernel_base_address+0x0C); // important to clear interrupt



    return IRQ_HANDLED;
}

//==========================================================



static ssize_t  enpower_opencl_mohammad_read(struct file * file,	// see include/linux/fs.h
                                                 char __user * buffer,	// buffer to be filled with data 
                                                 size_t        length,	        // length of the buffer
                                                 loff_t *      offset) {


    return 0;
}



static ssize_t enpower_opencl_mohammad_write(	struct file *file,
												const char __user * buffer, 
												size_t length, 
												loff_t * offset) {

    return 0;
}



long  enpower_opencl_mohammad_ioctl(struct        file *file,	      // ditto
		 	                        unsigned int  ioctl_num,	  // number and param for ioctl
		                            unsigned long ioctl_param) {  //ioctl_param is INLS
	u32 int_en = 0;
	u32 data_cntrl = 0;
	u32 return_value = 0;


	register_control_status_command_type *arg_param = (register_control_status_command_type*)ioctl_param;


    switch(ioctl_num) {
    case FPGACL_DEVICE_IOWRITE:

    	iowrite32(arg_param->value, arg_param->device_kernel_base_address+arg_param->register_physical_offset_address);
    	break;

    case FPGACL_DEVICE_IOREAD:

    	return_value = ioread32(arg_param->device_kernel_base_address+arg_param->register_physical_offset_address);

    	break;
	case FPGACL_START:
		//enable accelerator

		data_cntrl = ioread32(arg_param->device_kernel_base_address+arg_param->register_physical_offset_address) & 0x80;
        iowrite32(data_cntrl | 0x01, arg_param->device_kernel_base_address+arg_param->register_physical_offset_address);
//        getnstimeofday(&ts_start);
        break;
            
	case  FPGACL_CTRL_DONE:
		data_cntrl = ioread32(arg_param->device_kernel_base_address+arg_param->register_physical_offset_address);
	    return_value = (data_cntrl >> 1)&0x1;
		break;

	case  FPGACL_CTRL_READY:
		data_cntrl = ioread32(arg_param->device_kernel_base_address+arg_param->register_physical_offset_address);
	    return_value = (data_cntrl >> 3)&0x1;
		break;

	case FPGACL_INTERRUPT_ENABLE:

        int_en = ioread32(arg_param->device_kernel_base_address+arg_param->register_physical_offset_address);
        iowrite32(int_en | 0x01, arg_param->device_kernel_base_address+arg_param->register_physical_offset_address);

        int_en = ioread32(arg_param->device_kernel_base_address+arg_param->register_physical_offset_address+0x04);
        iowrite32( int_en | 0x01, arg_param->device_kernel_base_address+arg_param->register_physical_offset_address+0x04);
        break;

	case FPGACL_REGISTER_DEVICE:
		/*
		* Register Device
		*/

		device_kernel_address = enpower_ioremap(arg_param->device_physical_base_address);
		enpower_register_irq(arg_param->irq_num, device_kernel_address);

		printk(KERN_ERR "enpower_opencl_mohammad_ioctl: process_id = %d\n", arg_param->process_id);

		register_userspce_process_for_sending_signal(arg_param->process_id);


		return_value = (u32)device_kernel_address;


	default:
	
		break;

    }
    


	return return_value;

}


static int register_userspce_process_for_sending_signal(u32 user_process_pid) {

 	rcu_read_lock();
	user_process_struct = pid_task(find_pid_ns(user_process_pid, &init_pid_ns), PIDTYPE_PID);
	if(user_process_struct == NULL){
		printk(KERN_ALERT "no such pid\n");
		rcu_read_unlock();
		return -ENODEV;
	}
	rcu_read_unlock();

	memset(&info, 0, sizeof(struct siginfo));
	info.si_signo = SIGUSR1;
	info.si_code = SI_QUEUE;
	info.si_int = 1234;



	return 0;
}


static int enpower_opencl_mohammad_open(struct inode *inode, struct file *file) {

	u32 return_value = 0;


    
    if(enpower_opencl_mohammad_device_open)
    	return_value=-EBUSY;
     
    enpower_opencl_mohammad_device_open++;




    return return_value;
}



static int enpower_opencl_mohammad_release(struct inode *inode, struct file *file){

    enpower_opencl_mohammad_device_open--;


    return 0;
}


struct file_operations enpower_opencl_mohammad_fops = {
	.owner = THIS_MODULE,
	.read = enpower_opencl_mohammad_read,
	.write = enpower_opencl_mohammad_write,
	.unlocked_ioctl = enpower_opencl_mohammad_ioctl,
	.open = enpower_opencl_mohammad_open,
	.release = enpower_opencl_mohammad_release,
};

static struct device_node *gic_node;

static struct of_device_id gic_match[] = {
	{ .compatible = "arm,cortex-a9-gic", },
	{ .compatible = "arm,cortex-a15-gic", },
	{ },
};

unsigned int enpower_kernel_irq_num(unsigned int hwirq)
{
	struct of_phandle_args irq_data;
	unsigned int irq;



	if (!gic_node)
		gic_node = of_find_matching_node(NULL, gic_match);

	if (WARN_ON(!gic_node))
		return hwirq;

	irq_data.np = gic_node;
	irq_data.args_count = 3;
	irq_data.args[0] = 0;
	irq_data.args[1] = hwirq - 32; /* GIC SPI offset */
	irq_data.args[2] = IRQ_TYPE_EDGE_RISING;//IRQ_TYPE_LEVEL_HIGH;

	irq = irq_create_of_mapping(&irq_data);
	if (WARN_ON(!irq))
		irq = hwirq;

	pr_err("%s: hwirq %d, irq %d\n", __func__, hwirq, irq);

	return irq;
}


static int enpower_register_irq(u32 irq_num, void  *device_kernel_address) {

	int err;
	int irq_hardware;
	int irq;



	irq_hardware = irq_num;

	irq = enpower_kernel_irq_num(irq_hardware);
	pr_err("get_resource for IRQ for dev %d \n", irq);
	if (irq <= 0) {
		pr_err("get_resource for IRQ for dev %d failed\n", irq);
		return -ENODEV;
	}


	err = devm_request_irq(device_fpga, irq, isr, IRQF_SHARED, "axi_timer_dev", device_kernel_address);
	if (err) {
		pr_err("devm_request_irq failed\n");
		return err;
	}


	return err;
}


static void  *enpower_ioremap(long unsigned int device_physical_base_address) {
	void *enpower_device_kernel_base_address;


	enpower_device_kernel_base_address = ioremap(device_physical_base_address, FPGACL_DEVICE_NO_PORT);

	return enpower_device_kernel_base_address;
}



static int enpower_opencl_mohammad_init(void) {

    int   state;


    char  device_name[]=DEVICE_NAME;

    state = alloc_chrdev_region(&dev_numbers, 0, 1, device_name);
    if(state!=0) {
        printk(KERN_ERR "failed to register a region dynamically\n\r");
    } else {
        printk(KERN_ERR "major number = %d\n\r", MAJOR(dev_numbers));
    }

    if ((enpower_opencl_mohammad_cl = class_create(THIS_MODULE, "chardrv")) == NULL) {
    	unregister_chrdev_region(dev_numbers, 1);
     return -1;
    }
    device_fpga = device_create(enpower_opencl_mohammad_cl, NULL, dev_numbers, NULL, "fpga_dev");
    if (device_fpga == NULL) {
    	class_destroy(enpower_opencl_mohammad_cl);
     unregister_chrdev_region(dev_numbers, 1);
     return -1;
     }



    enpower_opencl_mohammad_cdev        = cdev_alloc();
    enpower_opencl_mohammad_cdev->ops   = &enpower_opencl_mohammad_fops;
    enpower_opencl_mohammad_cdev->owner = THIS_MODULE;

    cdev_init(enpower_opencl_mohammad_cdev, &enpower_opencl_mohammad_fops);
    state = cdev_add(enpower_opencl_mohammad_cdev, dev_numbers , 1);
    if(state < 0) {
        device_destroy(enpower_opencl_mohammad_cl, dev_numbers);
        class_destroy(enpower_opencl_mohammad_cl);
        unregister_chrdev_region(dev_numbers, 1);
        printk(KERN_ERR "device failed to be added\n\r");
    }






    return 0;
}


static void enpower_opencl_mohammad_exit(void) {


//	free_irq(IRQ_NUM, NULL);
	//platform_device_unregister(pdev);
    cdev_del(enpower_opencl_mohammad_cdev);
    device_destroy(enpower_opencl_mohammad_cl, dev_numbers);
	class_destroy(enpower_opencl_mohammad_cl);
    unregister_chrdev_region(dev_numbers, 1);

    printk(KERN_ALERT "Bye fpga device driver!\n\r");

}


module_init(enpower_opencl_mohammad_init);
module_exit(enpower_opencl_mohammad_exit);
MODULE_AUTHOR ("Mohammad Hosseinabady");
MODULE_DESCRIPTION("FPGA OpenCL driver.");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("custom:fpgacl_device_driver");
