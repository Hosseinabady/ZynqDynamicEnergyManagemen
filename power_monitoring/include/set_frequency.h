/*
 * frequency_scaling.h
 *
 *  Created on: May 19, 2015
 *      Author: csxmh
 */

#ifndef __SET__FREQUENCY_H_
#define __SET__FREQUENCY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef unsigned long int u32;
#define SLCR_BASE_ADDRESS 0xF8000000

#define FPGA0_CLK  0x00000001
#define FPGA1_CLK  0x00000002
#define FPGA2_CLK  0x00000004
#define FPGA3_CLK  0x00000008


#define FPGA0_CLK_CTRL  0xF8000170
#define FPGA1_CLK_CTRL  0xF8000180
#define FPGA2_CLK_CTRL  0xF8000190
#define FPGA3_CLK_CTRL  0xF80001A0

#define FPGA0_THR_STA   0xF800017C
#define FPGA1_THR_STA   0xF800018C
#define FPGA2_THR_STA   0xF800019C
#define FPGA3_THR_STA   0xF80001AC


#define FPGA0_THR_CTRL  0xF8000174
#define FPGA1_THR_CTRL  0xF8000184
#define FPGA2_THR_CTRL  0xF8000194
#define FPGA3_THR_CTRL  0xF80001A4


#define FPGA0_THR_CNT   0xF8000178
#define FPGA1_THR_CNT   0xF8000188
#define FPGA2_THR_CNT   0xF8000198
#define FPGA3_THR_CNT   0xF80001A8


u32 pl_frequency_set(int pl_clock, int divisor0, int divisor1);
u32 pl_disable_clock(int pl_clock);
u32 pl_enable_clock(int pl_clock);

u32 ps_frequency_set(int divisor);
#endif /* __SET__FREQUENCY_H_ */
