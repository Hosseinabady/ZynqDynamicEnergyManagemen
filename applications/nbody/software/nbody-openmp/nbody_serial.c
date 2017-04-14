#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "nbody.h"


double getTimestamp();
void runReference(const float *initialPositions,
                  const float *initialVelocities,
                  float *finalPositions);



double software_start;
double software_end;
double software_execution_time;
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


//#define	RAND_MAX	0x7FFF
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

	software_start = getTimestamp();

	for (u32 i = 0; i < SOFTWARE_INTERATION; i++) {
		for (u32 j = 0; j < 1; j++) {
			runReference(h_initialPositions, h_initialVelocities, h_reference);
		}
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(SOFTWARE_INTERATION*1000);
	printf("serial software execution time  %.6lf ms elapsed\n", software_execution_time);


	if(DELAY_FOR_POWER_MEASUREMENT != 1) {
		printf("huge number of iteration for manual monitoring\n");
		for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
			for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
				runReference(h_initialPositions, h_initialVelocities, h_reference);
			}
		}
	}

	free(h_positionsIn);
	free(h_reference);
	free(h_initialPositions);
	free(h_initialVelocities);



	return 0;
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



double getTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}
