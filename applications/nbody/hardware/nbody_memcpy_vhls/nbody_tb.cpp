#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nbody.h"




void runReference(const float *initialPositions,
                  const float *initialVelocities,
                  float *finalPositions);

int main() {

	unsigned long dataSize            = NUM_BODIES*4*sizeof(float);
	float    sphereRadius  =         128;
	float    tolerance     =      0.001f;

	printf("Running reference...\n");

	float *h_reference = (float *)malloc(dataSize);

	float *h_initialPositions  = (float *)malloc(dataSize);
	float *h_initialVelocities = (float *)malloc(dataSize);

	float *h_positionsIn          = (float *)malloc(4*dataSize);
	float *h_positionsOut         = h_positionsIn + 1*NUM_BODIES*4;//(float *)malloc(dataSize);
	float *h_velocitiesIn         = h_positionsIn + 2*NUM_BODIES*4;//(float *)malloc(dataSize);
	float *h_velocitiesOut        = h_positionsIn + 3*NUM_BODIES*4;//(float *)malloc(dataSize);


#define	RAND_MAX	0x7FFF
	for (int i = 0; i < NUM_BODIES; i++) {
		// Generate a random point on the edge of a sphere
	    float longitude             = 2.f * M_PI * (rand() / (float)RAND_MAX);
	    float latitude              = acos((2.f * (rand() / (float)RAND_MAX)) - 1);
	    h_initialPositions[i*4 + 0] = sphereRadius * sin(latitude) * cos(longitude);
	    h_initialPositions[i*4 + 1] = sphereRadius * sin(latitude) * sin(longitude);
	    h_initialPositions[i*4 + 2] = sphereRadius * cos(latitude);
	    h_initialPositions[i*4 + 3] = 1;
	}
	memset(h_initialVelocities, 0, dataSize);

	memcpy(h_positionsIn, h_initialPositions, dataSize);
	memcpy(h_velocitiesIn, h_initialVelocities, dataSize);

	runReference(h_initialPositions, h_initialVelocities, h_reference);


	for (int itr = 0; itr < ITERATIONS; itr++)  {
		nbody(h_positionsIn, h_positionsIn, h_positionsIn, h_positionsIn,  0*NUM_BODIES*4, 1*NUM_BODIES*4+0*GROUP_SIZE*4, 2*NUM_BODIES*4, 3*NUM_BODIES*4);

		memcpy(h_positionsIn, h_positionsOut, dataSize);
		memcpy(h_velocitiesIn, h_velocitiesOut, dataSize);
	}


	// Verify final positions
	unsigned errors = 0;
	for (int i = 0; i < NUM_BODIES; i++)  {
	    float ix = h_positionsIn[i*4 + 0];
	    float iy = h_positionsIn[i*4 + 1];
	    float iz = h_positionsIn[i*4 + 2];

	    float rx = h_reference[i*4 + 0];
	    float ry = h_reference[i*4 + 1];
	    float rz = h_reference[i*4 + 2];

	    float dx    = (rx-ix);
	    float dy    = (ry-iy);
	    float dz    = (rz-iz);
	    float dist  = sqrt(dx*dx + dy*dy + dz*dz);

	    if (dist > tolerance || isnan(dist))
	    {
	      if (!errors)
	      {
	        printf("Verification failed:\n");
	      }

	      // Only show the first 8 errors
	      if (errors++ < 8)
	      {
	        printf("-> Position error at %d: %.8f x1 = %.8f  x2=%.8f\n", i, dist, rx, ix);
	      }
	    }
	  }
	  if (errors)
	  {
	    printf("Total errors: %d\n", errors);

	  }
	  else
	  {
	    printf("Verification passed.\n");

	  }
	  printf("\n");


	return errors;
}

void runReference(const float *initialPositions,
                  const float *initialVelocities,
                  float *finalPositions)
{
  size_t dataSize     = NUM_BODIES*4*sizeof(float);
  float *positionsIn  = (float *)malloc(dataSize);
  float *positionsOut = (float *)malloc(dataSize);
  float *velocities   = (float *)malloc(dataSize);

  memcpy(positionsIn, initialPositions, dataSize);
  memcpy(velocities, initialVelocities, dataSize);

  for (int itr = 0; itr < ITERATIONS; itr++)  {
    for (int i = 0; i < NUM_BODIES; i++)  {
      float ix = positionsIn[i*4 + 0];
      float iy = positionsIn[i*4 + 1];
      float iz = positionsIn[i*4 + 2];
      float iw = positionsIn[i*4 + 3];

      float fx = 0.f;
      float fy = 0.f;
      float fz = 0.f;

      for (int j = 0; j < NUM_BODIES; j++) {
        float jx    = positionsIn[j*4 + 0];
        float jy    = positionsIn[j*4 + 1];
        float jz    = positionsIn[j*4 + 2];
        float jw    = positionsIn[j*4 + 3];

        // Compute distance between bodies
        float dx    = (jx-ix);
        float dy    = (jy-iy);
        float dz    = (jz-iz);
        float dist  = sqrt(dx*dx + dy*dy + dz*dz + SOFTENING*SOFTENING);

        // Compute interaction force
        float coeff = jw / (dist*dist*dist);
        fx         += coeff * dx;
        fy         += coeff * dy;
        fz         += coeff * dz;
      }

      // Update velocity
      float vx            = velocities[i*4 + 0] + fx * DELTA;
      float vy            = velocities[i*4 + 1] + fy * DELTA;
      float vz            = velocities[i*4 + 2] + fz * DELTA;
      velocities[i*4 + 0] = vx;
      velocities[i*4 + 1] = vy;
      velocities[i*4 + 2] = vz;

      // Update position
      positionsOut[i*4 + 0] = ix + vx * DELTA;
      positionsOut[i*4 + 1] = iy + vy * DELTA;
      positionsOut[i*4 + 2] = iz + vz * DELTA;
      positionsOut[i*4 + 3] = iw;
    }

    // Swap buffers
    float *temp  = positionsIn;
    positionsIn  = positionsOut;
    positionsOut = temp;
  }

  memcpy(finalPositions, positionsIn, dataSize);

  free(positionsIn);
  free(positionsOut);
  free(velocities);
}

