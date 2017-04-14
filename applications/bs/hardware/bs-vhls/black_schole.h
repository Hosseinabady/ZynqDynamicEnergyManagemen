#ifndef __BLACK_SCHOLE__
#define __BLACK_SCHOLE__



typedef float DATA_TYPE;
//typedef half DATA_TYPE;
typedef unsigned long u32;



#define OPT_N             (4000000)

void bs_stream( DATA_TYPE* memory_01,
		 DATA_TYPE* memory_02,
         DATA_TYPE* memory_03,
         DATA_TYPE* memory_04,
         DATA_TYPE* memory_05,
		 u32 call_offset,
		 u32 put_offset,
		 u32 s_offset,
		 u32 x_offset,
		 u32 t_offset
		 );
#endif //__BLACK_SCHOLE__
