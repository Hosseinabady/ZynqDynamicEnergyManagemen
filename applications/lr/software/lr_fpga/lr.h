#ifndef __LR_H__
#define __LR_H__



typedef float DATA_TYPE;
typedef unsigned long int u32;


#define DATA_LENGTH 400000*8

void lr(
		  DATA_TYPE    *memory_0
		, DATA_TYPE    *memory_1
		, u32           in_X
		, u32           in_Y
		, DATA_TYPE     *a0
		, DATA_TYPE     *a1);

#endif //__LR_H__
