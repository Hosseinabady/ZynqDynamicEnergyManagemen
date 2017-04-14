#ifndef __COLUMN_2DMEAN__
#define __COLUMN_2DMEAN__

typedef unsigned int u32;
#define M 2600
#define N 3000

#define DATA_TYPE float

void column_2dmean(	DATA_TYPE* memory_1,
					DATA_TYPE* memory_2,

					DATA_TYPE* memory_3,
					DATA_TYPE* memory_4,

					DATA_TYPE* memory_5,
					DATA_TYPE* memory_6,

					DATA_TYPE* memory_7,
					DATA_TYPE* memory_8,

					u32        data_offset,
					u32        mean_offset,
					int        n);

#endif //__COLUMN_2DMEAN__
