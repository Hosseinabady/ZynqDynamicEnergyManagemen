#include "nbody.h"
#include <hls_math.h>
#include <string.h>

inline void nbody_kernel(	float positionsIn[4*NUM_BODIES],
					float velocitiesIn[4*NUM_BODIES],
					float positionsOut[4*GROUP_SIZE],
					float velocitiesOut[4*GROUP_SIZE],
					u32 index );
using namespace hls;

void nbody(	volatile float* memory_0,
			volatile float* memory_1,
			volatile float* memory_2,
			volatile float* memory_3,
			volatile u32 positionsIn_offset,
			volatile u32 positionsOut_offset,
			volatile u32 velocitiesIn_offset,
			volatile u32 velocitiesOut_offset){
#pragma HLS INTERFACE s_axilite port=return bundle=control_bus
#pragma HLS INTERFACE s_axilite port=positionsIn_offset   bundle=control_bus
#pragma HLS INTERFACE s_axilite port=positionsOut_offset  bundle=control_bus
#pragma HLS INTERFACE s_axilite port=velocitiesIn_offset  bundle=control_bus
#pragma HLS INTERFACE s_axilite port=velocitiesOut_offset bundle=control_bus


#pragma HLS INTERFACE m_axi port=memory_0
#pragma HLS INTERFACE m_axi port=memory_1
#pragma HLS INTERFACE m_axi port=memory_2
#pragma HLS INTERFACE m_axi port=memory_3



	float positionsIn[4*NUM_BODIES];
	float velocitiesIn[4*NUM_BODIES];

	float positionsOut[4*NUM_BODIES];
	float velocitiesOut[4*NUM_BODIES];

#pragma HLS ARRAY_PARTITION variable=positionsIn   cyclic   factor=32   dim=1
#pragma HLS ARRAY_PARTITION variable=velocitiesIn  cyclic   factor=32   dim=1
#pragma HLS ARRAY_PARTITION variable=positionsOut  cyclic   factor=32   dim=1
#pragma HLS ARRAY_PARTITION variable=velocitiesOut cyclic   factor=32   dim=1

#pragma HLS DATAFLOW

	memcpy(positionsIn,(float *)(memory_0+positionsIn_offset),(NUM_BODIES)*4*sizeof(float));
	memcpy(velocitiesIn,(float *)(memory_1+velocitiesIn_offset),(NUM_BODIES)*4*sizeof(float));


	nbody_kernel(positionsIn, velocitiesIn, positionsOut, velocitiesOut, 0*GROUP_SIZE);


	memcpy((float *)(memory_2+positionsOut_offset),positionsOut,(NUM_BODIES)*4*sizeof(float));
	memcpy((float *)(memory_3+velocitiesOut_offset),velocitiesOut,(NUM_BODIES)*4*sizeof(float));

}

inline void nbody_kernel(	float   positionsIn[4*NUM_BODIES],
					float  velocitiesIn[4*NUM_BODIES],
					float  positionsOut[4*NUM_BODIES],
					float velocitiesOut[4*NUM_BODIES],
					u32 index )
{
#pragma HLS DATAFLOW

	float ipos[4];
	float force[4];
	float velocity[4];

	mainloop: for (int i = 0; i < GROUP_SIZE; i++) {
		ipos[0] = positionsIn[(i+index)*4+0];
		ipos[1] = positionsIn[(i+index)*4+1];
		ipos[2] = positionsIn[(i+index)*4+2];
		ipos[3] = positionsIn[(i+index)*4+3];

		force[0] = 0.0f;
		force[1] = 0.0f;
		force[2] = 0.0f;
		force[3] = 0.0f;


		innerloop:for (int j = 0; j < (NUM_BODIES); j++) {
#pragma HLS PIPELINE
#pragma HLS UNROLL factor=16


			float d[4];
			float f[4];
			float jpos[4];

			jpos[0] = positionsIn[j*4+0];
			jpos[1] = positionsIn[j*4+1];
			jpos[2] = positionsIn[j*4+2];
			jpos[3] = positionsIn[j*4+3];

			d[0] = jpos[0] - ipos[0];
			d[1] = jpos[1] - ipos[1];
			d[2] = jpos[2] - ipos[2];
			d[3]    = 0;

			float  distSq = d[0]*d[0] + d[1]*d[1] + d[2]*d[2] + SOFTENING*SOFTENING;
			float  dist   = hls::sqrt(distSq);
			float  coeff  = jpos[3] / (dist*dist*dist);
			f[0] = coeff*d[0];
			f[1] = coeff*d[1];
			f[2] = coeff*d[2];
			f[3] = coeff*d[3];

			force[0] += f[0];
			force[1] += f[1];
			force[2] += f[2];
			force[3] += f[3];

		}
		velocity[0] = velocitiesIn[(i+index)*4+0];
		velocity[1] = velocitiesIn[(i+index)*4+1];
		velocity[2] = velocitiesIn[(i+index)*4+2];
		velocity[3] = velocitiesIn[(i+index)*4+3];

		velocity[0]       += force[0] * DELTA;
		velocity[1]       += force[1] * DELTA;
		velocity[2]       += force[2] * DELTA;
		velocity[3]       += force[3] * DELTA;

		velocitiesOut[(i+index)*4+0]   = velocity[0];
		velocitiesOut[(i+index)*4+1]   = velocity[1];
		velocitiesOut[(i+index)*4+2]   = velocity[2];
		velocitiesOut[(i+index)*4+3]   = velocity[3];

		// Update position
		positionsOut[(i+index)*4+0] = ipos[0] + velocity[0] * DELTA;
		positionsOut[(i+index)*4+1] = ipos[1] + velocity[1] * DELTA;
		positionsOut[(i+index)*4+2] = ipos[2] + velocity[2] * DELTA;
		positionsOut[(i+index)*4+3] = ipos[3] + velocity[3] * DELTA;


	}
}
