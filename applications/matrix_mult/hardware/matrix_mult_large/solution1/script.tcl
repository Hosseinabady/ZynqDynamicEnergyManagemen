############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
############################################################
open_project matrix_mult_large_vhls
set_top matrix_mult_large
add_files matrix_mult_large_vhls/matrix_mult.h
add_files matrix_mult_large_vhls/matrix_mult.cpp
add_files -tb matrix_mult_large_vhls/matrix_mult_tb.cpp
open_solution "solution1"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
#source "./matrix_mult_large_vhls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
