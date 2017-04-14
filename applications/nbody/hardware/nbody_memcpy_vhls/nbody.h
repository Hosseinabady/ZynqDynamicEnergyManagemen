#ifndef __NBODY_H__
#define __NBODY_H__


typedef unsigned long u32;

#define  NUM_BODIES (2*2048)
//#define  GROUP_SIZE 1
//#define  GROUP_SIZE NUM_BODIES/5

#define  GROUP_SIZE (NUM_BODIES)

#define SOFTENING 0.001f
#define DELTA     0.005f

#define ITERATIONS          1


void nbody(	volatile float* memory_0,
			volatile float* memory_1,
			volatile float* memory_2,
			volatile float* memory_3,
			volatile u32 positionsIn_offset,
			volatile u32 positionsOut_offset,
			volatile u32 velocitiesIn_offset,
			volatile u32 velocitiesOut_offset);
#endif //__NBODY_H__
