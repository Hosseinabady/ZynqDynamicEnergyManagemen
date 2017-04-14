/*
 * frequency_scaling.c
 *
 *  Created on: May 19, 2015
 *      Author: csxmh
 */


#include "set_frequency.h"


u32 pl_frequency_set(int pl_clock, int divisor0, int divisor1) {


	int fd;

	unsigned page_addr, page_offset;

	void *ptr, *ptr_sta, *ptr_ddr;
	unsigned page_size=sysconf(_SC_PAGESIZE);

	unsigned fpga_clk_ctrl;

	if (pl_clock == FPGA0_CLK)
		fpga_clk_ctrl = FPGA0_CLK_CTRL;
	if (pl_clock == FPGA1_CLK)
		fpga_clk_ctrl = FPGA1_CLK_CTRL;
	if (pl_clock == FPGA2_CLK)
		fpga_clk_ctrl = FPGA2_CLK_CTRL;
	if (pl_clock == FPGA3_CLK)
		fpga_clk_ctrl = FPGA3_CLK_CTRL;
	//	unsigned fpga0_clk_sta  = FPGA0_THR_STA;


	 /* Open /dev/mem file */
	fd = open ("/dev/mem", O_RDWR);
	if (fd < 1) {
		perror("error 1\n");
		return -1;
	}

    page_addr = (fpga_clk_ctrl & (~(page_size-1)));
    page_offset = fpga_clk_ctrl - page_addr;
    ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

    unsigned int ctrl_value_0 = *((int *)(ptr + page_offset));

    u32  reserved=0x00000000;
    divisor0 = divisor0 << 8;
    divisor1 = divisor1 << 20;

    u32 plCLKDivisor = reserved|divisor0|divisor1;

    *((int *)(ptr + page_offset)) = plCLKDivisor;//0x00102000;

//    unsigned int ctrl_value_1 = *((int *)(ptr + page_offset));

//    printf("ctrl_value_0 = 0x%08x\n", ctrl_value_0);
//    printf("ctrl_value_0 = 0x%08x\n",ctrl_value_1);


    close(fd);
   return 0;
}



u32 pl_disable_clock(int pl_clock) {

	int fd;

	unsigned page_addr, page_offset;

	void *ptr, *ptr_sta, *ptr_ddr;
	unsigned page_size=sysconf(_SC_PAGESIZE);


	unsigned long int fpga_thr_ctrl;
	unsigned long int fpga_thr_cnt;

	if (pl_clock == FPGA0_CLK) {
		fpga_thr_ctrl = FPGA0_THR_CTRL;
		fpga_thr_cnt = FPGA0_THR_CNT;
	}
	if (pl_clock == FPGA1_CLK) {
		fpga_thr_ctrl = FPGA1_THR_CTRL;
		fpga_thr_cnt  = FPGA1_THR_CNT;
	}
	if (pl_clock == FPGA2_CLK) {
		fpga_thr_ctrl = FPGA2_THR_CTRL;
		fpga_thr_cnt  = FPGA2_THR_CNT;
	}
	if (pl_clock == FPGA3_CLK) {
		fpga_thr_ctrl = FPGA3_THR_CTRL;
		fpga_thr_cnt  = FPGA3_THR_CNT;
	}



	 /* Open /dev/mem file */
	fd = open ("/dev/mem", O_RDWR);
	if (fd < 1) {
		perror("error 1\n");
		return -1;
	}

	//enable SLCR_UNLOCK
	unsigned slcr_unlock = 0xF8000008;

	page_addr = (slcr_unlock & (~(page_size-1)));
    page_offset = slcr_unlock - page_addr;
    ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

	*((int *)(ptr + page_offset)) = 0xDF0D;


	//enable LVL_SHIFT_EN
	unsigned lvl_shiftr_en = 0xF8000900;

	page_addr = (lvl_shiftr_en & (~(page_size-1)));
    page_offset = lvl_shiftr_en - page_addr;
    ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

    *((int *)(ptr + page_offset)) = 0x0F;





    //zynq_slcr_write  1-->FPGA0_THR_CNT_OFFSET
	page_addr = (fpga_thr_cnt & (~(page_size-1)));
	page_offset = fpga_thr_cnt - page_addr;
	ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

	*((int *)(ptr + page_offset)) = 1;




	//zynq_slcr_write  1-->FPGA0_THR_CTRL_OFFSET
    page_addr = (fpga_thr_ctrl & (~(page_size-1)));
    page_offset = fpga_thr_ctrl - page_addr;
    ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

    *((int *)(ptr + page_offset)) = 1;


    close(fd);
   return 0;


}


u32 pl_enable_clock(int pl_clock) {

	int fd;

	unsigned page_addr, page_offset;

	void *ptr, *ptr_sta, *ptr_ddr;
	unsigned page_size=sysconf(_SC_PAGESIZE);


	unsigned long int fpga_thr_ctrl;
	unsigned long int fpga_thr_cnt;

	if (pl_clock == FPGA0_CLK) {
		fpga_thr_ctrl = FPGA0_THR_CTRL;
		fpga_thr_cnt = FPGA0_THR_CNT;
	}
	if (pl_clock == FPGA1_CLK) {
		fpga_thr_ctrl = FPGA1_THR_CTRL;
		fpga_thr_cnt  = FPGA1_THR_CNT;
	}
	if (pl_clock == FPGA2_CLK) {
		fpga_thr_ctrl = FPGA2_THR_CTRL;
		fpga_thr_cnt  = FPGA2_THR_CNT;
	}
	if (pl_clock == FPGA3_CLK) {
		fpga_thr_ctrl = FPGA3_THR_CTRL;
		fpga_thr_cnt  = FPGA3_THR_CNT;
	}



	 /* Open /dev/mem file */
	fd = open ("/dev/mem", O_RDWR);
	if (fd < 1) {
		perror("error 1\n");
		return -1;
	}

	//enable SLCR_UNLOCK
	unsigned slcr_unlock = 0xF8000008;

	page_addr = (slcr_unlock & (~(page_size-1)));
    page_offset = slcr_unlock - page_addr;
    ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

	*((int *)(ptr + page_offset)) = 0xDF0D;


	//enable LVL_SHIFT_EN
	unsigned lvl_shiftr_en = 0xF8000900;

	page_addr = (lvl_shiftr_en & (~(page_size-1)));
    page_offset = lvl_shiftr_en - page_addr;
    ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

    *((int *)(ptr + page_offset)) = 0x0F;



    //zynq_slcr_write  0-->FPGA0_THR_CNT_OFFSET
	page_addr = (fpga_thr_cnt & (~(page_size-1)));
	page_offset = fpga_thr_cnt - page_addr;
	ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

	*((int *)(ptr + page_offset)) = 0;




	//zynq_slcr_write  0-->FPGA0_THR_CTRL_OFFSET
    page_addr = (fpga_thr_ctrl & (~(page_size-1)));
    page_offset = fpga_thr_ctrl - page_addr;
    ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

    *((int *)(ptr + page_offset)) = 0;

    close(fd);

   return 0;


}



u32 ps_frequency_set(int divisor) {
	int fd;

	unsigned page_addr, page_offset;

	void *ptr, *ptr_sta, *ptr_ddr;
	unsigned page_size=sysconf(_SC_PAGESIZE);


	 /* Open /dev/mem file */
	fd = open ("/dev/mem", O_RDWR);
	if (fd < 1) {
		perror("error 1\n");
		return -1;
	}

	if (divisor > 63) {
		printf("The PS frequncy divider cannot be divided by %d\n", divisor);
		divisor = 62;
		printf("The PS frequncy divider is set to the maximum which is 62\n");
	}
	if (divisor < 2) {
		printf("The PS frequncy cannot divided by %d\n", divisor);
		divisor = 2;
		printf("The PS frequncy divider is set to default which  is 2\n");
	}

	//enable SLCR_UNLOCK
	unsigned slcr_unlock = 0xF8000008;

	page_addr = (slcr_unlock & (~(page_size-1)));
    page_offset = slcr_unlock - page_addr;
    ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

    *((int *)(ptr + page_offset)) = 0xDF0D;



	unsigned long arm_clk_ctrl = 0xF8000120;

    page_addr = (arm_clk_ctrl & (~(page_size-1)));
    page_offset = arm_clk_ctrl - page_addr;
    ptr = mmap(NULL, page_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

    unsigned int arm_clk_ctrl_value = *((int *)(ptr + page_offset));

    printf("original arm_clk_ctrl_value = 0x%08x\n", arm_clk_ctrl_value);

    u32  divisor_MASK = 0xFFFFC0FF;
    arm_clk_ctrl_value = arm_clk_ctrl_value&divisor_MASK;

    divisor = divisor << 8;

    arm_clk_ctrl_value = arm_clk_ctrl_value|divisor;

    *((int *)(ptr + page_offset)) = arm_clk_ctrl_value;//0x00102000;

    printf("updated arm_clk_ctrl_value = 0x%08x\n", arm_clk_ctrl_value);
//    unsigned int ctrl_value_1 = *((int *)(ptr + page_offset));

//    printf("ctrl_value_0 = 0x%08x\n", ctrl_value_0);
//    printf("ctrl_value_0 = 0x%08x\n",ctrl_value_1);


    close(fd);
   return 0;

}
