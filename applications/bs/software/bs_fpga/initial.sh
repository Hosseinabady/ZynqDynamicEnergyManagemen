#!/bin/bash

current_path=$PWD
cd /opt/Mohammad/bristol_projects/linux_drivers/zynq_opencl_pattern_based/dev-final
insmod fpgacl_device_driver_mem_alloc.ko
insmod fpgacl_device_driver.ko
cd $current_path


