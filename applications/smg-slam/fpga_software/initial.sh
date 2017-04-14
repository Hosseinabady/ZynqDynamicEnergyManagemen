#!/bin/bash

current_path=$PWD
cd /opt/Mohammad/bristol_projects/linux_drivers/zynq_opencl_pattern_based/dev-final-with-mem-cacheable
insmod fpgacl_device_driver.ko
cd $current_path

