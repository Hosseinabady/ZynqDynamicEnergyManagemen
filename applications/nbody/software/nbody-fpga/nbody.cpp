#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "accel.h"
extern "C" {
#include <fpgacl_memory.h>
#include <measurement.h>
#include <set_frequency.h>
#include <monitoring.h>
}
#include <sys/time.h>
#include <time.h>

extern char log_file_name[1000];
#define EXE_TIME_MONITORING_ITERATION_NUM  10
#define MANUAL_POWER_MONITOR_ITERATION 1


void refresh_hardware(int *accel_status);
int run_command(char cmd[1000]);
void init_data(float* h_initialPositions, float *h_initialVelocities, float* h_positionsIn, float* h_velocitiesIn);
int validate(float *h_positionsIn, float* h_reference) ;

void nbody_hw(DATA_TYPE *  positionsIn,
					DATA_TYPE *  positionsOut,
					DATA_TYPE *  velocitiesIn,
					DATA_TYPE *  velocitiesOut);

void runReference(const float *initialPositions,
                  const float *initialVelocities,
                  float *finalPositions);


double hardware_start;
double hardware_end;
double hardware_execution_time;

double software_start;
double software_end;
double software_execution_time;
int main() {
	unsigned status = 0;
	unsigned long dataSize            = NUM_BODIES*4*sizeof(float);
	float    sphereRadius  =         128;
	float    tolerance     =      0.001f;
	FILE* fp_v;
	int accel_status = 0;


	printf("Running reference...\n");


	float *h_reference = (float *)malloc(dataSize);

	float *h_initialPositions  = (float *)malloc(dataSize);
	float *h_initialVelocities = (float *)malloc(dataSize);

	float *h_positionsIn          = (float *)malloc(4*dataSize);
	float *h_positionsOut         = h_positionsIn + 1*NUM_BODIES*4;//(float *)malloc(dataSize);
	float *h_velocitiesIn         = h_positionsIn + 2*NUM_BODIES*4;//(float *)malloc(dataSize);
	float *h_velocitiesOut        = h_positionsIn + 3*NUM_BODIES*4;//(float *)malloc(dataSize);


//#define	RAND_MAX	0x7FFF

	init_data(h_initialPositions, h_initialVelocities, h_positionsIn, h_velocitiesIn);


	software_start = getTimestamp();

	for (u32 i = 0; i < 1; i++) {
		for (u32 j = 0; j < 1; j++) {

			runReference(h_initialPositions, h_initialVelocities, h_reference);
		}
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);


	float* h_positionsIn_hw;
	float* h_positionsOut_hw;
	float* h_velocitiesIn_hw;
	float* h_velocitiesOut_hw;

	float* h_positionsOut_hw_result =  (float *)malloc(dataSize);
	float* h_velocitiesOut_hw_result =  (float *)malloc(dataSize);


	int frequency_factor_min = 5;
	int vccint_min = 0.67;


	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);
	VOLTAGE_SCALING_PROLOGUE(vccint_min, 1.0, 0.01);
	FREQUENCY_SCALING_PROLOGUE(frequency_factor_min, 50, 1);

	refresh_hardware(&accel_status);

	init_data(h_initialPositions, h_initialVelocities, h_positionsIn, h_velocitiesIn);


	if ( (h_positionsIn_hw=(DATA_TYPE *)fpgacl_malloc(dataSize)) == NULL )
		perror("memory allocation for h_positionsIn");
	if ( (h_positionsOut_hw=(DATA_TYPE *)fpgacl_malloc(dataSize)) == NULL )
			perror("memory allocation for h_positionsIn");
	if ( (h_velocitiesIn_hw=(DATA_TYPE *)fpgacl_malloc(dataSize)) == NULL )
			perror("memory allocation for h_positionsIn");
	if ( (h_velocitiesOut_hw=(DATA_TYPE *)fpgacl_malloc(dataSize)) == NULL )
			perror("memory allocation for h_positionsIn");



	fpgacl_memwrite((void *)h_positionsIn, (u32*)h_positionsIn_hw, dataSize);
	fpgacl_memwrite((void *)h_positionsOut, (u32*)h_positionsOut_hw, dataSize);
	fpgacl_memwrite((void *)h_velocitiesIn, (u32*)h_velocitiesIn_hw, dataSize);
	fpgacl_memwrite((void *)h_velocitiesOut, (u32*)h_velocitiesOut_hw, dataSize);


	runReference(h_initialPositions, h_initialVelocities, h_reference);
	nbody_hw(h_positionsIn_hw, h_positionsOut_hw, h_velocitiesIn_hw, h_velocitiesOut_hw);


	fpgacl_memread((void*)h_positionsOut_hw_result, (u32 *)h_positionsOut_hw, dataSize);
	fpgacl_memread((void*)h_velocitiesOut_hw_result, (u32 *)h_velocitiesOut_hw, dataSize);


	status = validate(h_positionsOut_hw_result, h_reference);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
		printf("Validation FAILED!\n");
		frequency_factor_min = freq+1;
	}
	if (status == 0) {
		//=============================================================================
		// compute the iteration_number
		//=============================================================================

		hardware_start = getTimestamp();
		for (int itr = 0; itr < EXE_TIME_MONITORING_ITERATION_NUM; itr++)  {
			nbody_hw(h_positionsIn_hw, h_positionsOut_hw, h_velocitiesIn_hw, h_velocitiesOut_hw);
		}
		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 4000/hardware_execution_time;
		//============================================================================



		fp_v=fopen(log_file_name, "a");


		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			nbody_hw(h_positionsIn_hw, h_positionsOut_hw, h_velocitiesIn_hw, h_velocitiesOut_hw);
		}
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");


		if (MANUAL_POWER_MONITOR_ITERATION != 1) {
			printf("loop for manual power monitoring!\n");
			for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
				for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
					nbody_hw(h_positionsIn_hw, h_positionsOut_hw, h_velocitiesIn_hw, h_velocitiesOut_hw);
				}
			}
		}


//	memcpy(h_positionsIn, h_positionsOut_hw_result, dataSize);
//	memcpy(h_velocitiesIn, h_velocitiesOut_hw_result, dataSize);

		if(DELAY_FOR_POWER_MEASUREMENT != 1) {
			printf("huge number of iteration for manual power monitoring\n");
			for(int i = 0; i < DELAY_FOR_POWER_MEASUREMENT; i++) {
				for(int j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
					nbody_hw(h_positionsIn_hw, h_positionsOut_hw, h_velocitiesIn_hw, h_velocitiesOut_hw);
				}
			}
		}


		fclose(fp_v);
	}
	fpgacl_free((u32)h_positionsIn_hw);
	fpgacl_free((u32)h_positionsOut_hw);
	fpgacl_free((u32)h_velocitiesIn_hw);
	fpgacl_free((u32)h_velocitiesOut_hw);

	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();

	//==================================================================
	//        END:: HARDWARE ACCELERATOR
	//==================================================================

		free(h_positionsIn);
		free(h_reference);
		free(h_initialPositions);
		free(h_initialVelocities);
		free(h_positionsOut_hw_result);
		free(h_velocitiesOut_hw_result);

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


void nbody_hw(DATA_TYPE *  positionsIn,
					DATA_TYPE *  positionsOut,
					DATA_TYPE *  velocitiesIn,
					DATA_TYPE *  velocitiesOut) {



//	printf("hw started\n");
	accel_write(positionsIn, positionsOut, velocitiesIn, velocitiesOut);
	accel_start();
	//accel_wait(); //poling
	sleep(1);

//	printf("press a key\n");
//	getchar();


}



void init_data(float* h_initialPositions, float *h_initialVelocities, float* h_positionsIn, float* h_velocitiesIn) {

	unsigned long dataSize            = NUM_BODIES*4*sizeof(float);
	float    sphereRadius  =         128;
	float    tolerance     =      0.001f;

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
}

int run_command(char cmd[1000]) {
	FILE *pp;
	int status = 0;
	pp = popen(cmd, "r");
	if (pp != NULL) {
	    while (1) {
	      char *line;
	      char buf[1000];
	      line = fgets(buf, sizeof buf, pp);
	      if (line == NULL) break;
	      if (line[0] == 'd') printf("%s", line); /* line includes '\n' */
	    }
	    status = -1;
	}
	pclose(pp);
	return status;
}

void refresh_hardware(int *accel_status) {
	char cmd[100];

	sprintf(cmd, "chmod u+x initial.sh");
	run_command(cmd);

	sprintf(cmd, "chmod u+x clean.sh");
	run_command(cmd);

	if (*accel_status == 0) {

		printf("refresh_hardware: check point 1\n");
		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		accel_prologue();

		sprintf(cmd, "cat nbody_memcpy_II6.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat  nbody_memcpy_II6.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}






}



int validate(float *h_positionsIn, float* h_reference) {


	float    tolerance     =      0.001f;
	int errors = 0;
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

		if (dist > tolerance || isnan(dist)) {
			errors++;
		  // Only show the first 8 errors
		  if (errors < 8)
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

	  return errors;
}
