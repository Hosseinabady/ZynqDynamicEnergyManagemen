#ifndef __PR_H__
#define __PR_H__


//typedef unsigned char u8;
typedef unsigned long int u32;

typedef float DATA_TYPE;

#define DATA_LENGTH (400000*8)



void pr(DATA_TYPE * memory_0,
		DATA_TYPE * memory_1,
		u32 in_X_offset,
        u32 in_Y_offset,
        float *a0,
        float *a1,
		float *a2,
		int   *resultValid
	);

#endif //__PR_H__
