#!/bin/bash

current_path=$PWD
cd /opt/Mohammad/bristol_projects/linux_drivers/zynq_opencl_pattern_based/dev-final
rmmod fpgacl_device_driver_mem_alloc
rmmod fpgacl_device_driver
cd $current_path


