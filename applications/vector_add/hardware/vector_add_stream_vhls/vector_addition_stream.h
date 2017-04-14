typedef unsigned long int u32;
typedef float DATA_TYPE;
#define  n (1024*1024)

void vector_addition_stream( DATA_TYPE* memory_1_1,
							 DATA_TYPE* memory_1_2,
							 DATA_TYPE* memory_1_3,

							 DATA_TYPE* memory_2_1,
							 DATA_TYPE* memory_2_2,
							 DATA_TYPE* memory_2_3,


							 u32        a_offset,
							 u32        b_offset,
							 u32        c_offset
							);
