#ifndef __NBODY_H__
#define __NBODY_H__




#define  NUM_BODIES (2*2048)

typedef unsigned long int u32;
typedef float DATA_TYPE;

#define ITERATIONS          1
#define DELAY_FOR_POWER_MEASUREMENT 1


#define SOFTENING 0.001f
#define DELTA     0.005f

void nbody(volatile float* memory,
		   volatile u32 positionsIn_offset,
		   volatile u32 positionsOut_offset,
		   volatile u32 velocitiesIn_offset,
		   volatile u32 velocitiesOut_offset);
#endif //__NBODY_H__
