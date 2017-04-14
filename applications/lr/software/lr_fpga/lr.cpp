#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "accel.h"

extern "C" {
#include <measurement.h>
#include <set_frequency.h>
#include <fpgacl_memory.h>
#include <monitoring.h>
}


#include <sys/time.h>
#include <time.h>


extern char log_file_name[1000];

double hardware_start;
double hardware_end;
double hardware_execution_time;

double software_start;
double software_end;
double software_execution_time;


void refresh_hardware(int *accel_status);
int run_command(char cmd[1000]);
int validate(DATA_TYPE a0_sw, DATA_TYPE a1_sw, DATA_TYPE a0_hw, DATA_TYPE a1_hw);
void lr_hardware(int n, DATA_TYPE *  X,
		DATA_TYPE *  Y, DATA_TYPE *A0, DATA_TYPE *A1);

#define MANUAL_POWER_MONITOR_ITERATION 1
#define EXE_TIME_MONITORING_ITERATION_NUM  10

void lr_init( float *tXBuf,  float *tYBuf)
{

  int i, j;

  for (i = 0; i < DATA_LENGTH; i++) {
	  tXBuf[i] = (1.0*i)/DATA_LENGTH;
  }
  for (i = 0; i < DATA_LENGTH; i++) {
	  tYBuf[i ] = (1.23*((1.0*i)/DATA_LENGTH)+2.5);
  }

}


void lr_software(float *tXBuf,  float *tYBuf, float &a0SW, float  &a1SW)
		{
			float sumX  =0;
			float sumY  =0;
			float sumXY =0;
			float sumXX =0;

			DATA_TYPE cX  =0;
			DATA_TYPE cY  =0;
			DATA_TYPE cXY =0;
			DATA_TYPE cXX =0;

			DATA_TYPE y, t;
			for (int i = 0; i < DATA_LENGTH; i++) {
//				sumX += *(tXBuf+i);
//				sumY += *(tYBuf+i);
//				sumXY += (*(tXBuf+i)) * (*(tYBuf+i));
//				sumXX += (*(tXBuf+i)) * (*(tXBuf+i));

				y = *(tXBuf+i) - cX;
				t = sumX + y;
				cX = (t - sumX) - y;
				sumX = t ;

				y = *(tYBuf+i) - cY;
				t = sumY + y;
				cY = (t - sumY) - y;
				sumY = t ;

				y = (*(tXBuf+i)) * (*(tYBuf+i)) - cXY;
				t = sumXY + y;
				cXY = (t - sumXY) - y;
				sumXY = t ;

				y = (*(tXBuf+i)) * (*(tXBuf+i)) - cXX;
				t = sumXX + y;
				cXX = (t - sumXX) - y;
				sumXX = t ;

			}





			a0SW = (sumY*sumXX - sumX*sumXY)/(DATA_LENGTH*sumXX-sumX*sumX);
			a1SW = (DATA_LENGTH*sumXY-sumX*sumY)/(DATA_LENGTH*sumXX-sumX*sumX);

		}




int main() {

	int accel_status = 0;
	int status;
	FILE* fp_v;
	char cmd[100];

	DATA_TYPE *X_sw = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));
	DATA_TYPE *Y_sw = (DATA_TYPE *)malloc(DATA_LENGTH*sizeof(DATA_TYPE));

	DATA_TYPE *X_hw;
	DATA_TYPE *Y_hw;

	lr_init(X_sw, Y_sw);

	DATA_TYPE  a0_sw;
	DATA_TYPE  a1_sw;

	DATA_TYPE  a0_hw;
	DATA_TYPE  a1_hw;

	software_start = getTimestamp();
	for (int i = 0; i < EXE_TIME_MONITORING_ITERATION_NUM; i++) {
		lr_software( X_sw, Y_sw, a0_sw, a1_sw);
	}
	software_end = getTimestamp();
	software_execution_time = (software_end-software_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

	printf("a0_sw=%f, a1_sw=%f\n", a0_sw, a1_sw);

	int frequency_factor_min = 5;
	int vccint_min = 0.67;


	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);
	VOLTAGE_SCALING_PROLOGUE(vccint_min, 1.0, 0.01);
	FREQUENCY_SCALING_PROLOGUE(frequency_factor_min, 50, 1);


	refresh_hardware(&accel_status);

	if ( (X_hw=(DATA_TYPE *)fpgacl_malloc(DATA_LENGTH*sizeof(DATA_TYPE))) == NULL )
			perror("memory allocation for X");
	if ( (Y_hw=(DATA_TYPE *)fpgacl_malloc(DATA_LENGTH*sizeof(DATA_TYPE))) == NULL )
			perror("memory allocation for Y");

	lr_init(X_sw, Y_sw);

	fpgacl_memwrite((void *)X_sw, (u32*)X_hw, sizeof(DATA_TYPE)*DATA_LENGTH);
	fpgacl_memwrite((void *)Y_sw, (u32*)Y_hw, sizeof(DATA_TYPE)*DATA_LENGTH);


	lr_software( X_sw, Y_sw, a0_sw, a1_sw);

	lr_hardware(DATA_LENGTH, X_hw, Y_hw, &a0_hw, &a1_hw);


	status = validate(a0_sw, a1_sw, a0_hw, a1_hw);
	if (status == 0) {
		printf("Validation PASSED!\n");
	} else {
		printf("Validation FAILED!\n");
		frequency_factor_min = freq+1;
	}
	if (status == 0) {

		hardware_start = getTimestamp();
		for (int i = 0; i < EXE_TIME_MONITORING_ITERATION_NUM; i++) {
			lr_hardware(DATA_LENGTH, X_hw, Y_hw, &a0_hw, &a1_hw);
		}

		hardware_end = getTimestamp();
		hardware_execution_time = (hardware_end-hardware_start)/(EXE_TIME_MONITORING_ITERATION_NUM*1000);
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);
		unsigned long int iteration_number = 4000/hardware_execution_time;


		fp_v=fopen(log_file_name, "a");

		POWER_MONITORING_PROLOGUE();
		for (int i = 0; i < iteration_number; i++) {
			lr_hardware(DATA_LENGTH, X_hw, Y_hw, &a0_hw, &a1_hw);
		}
		POWER_MONITORING_EPILOGUE();


		fprintf(fp_v,"Validation PASSED!\n");

		if (MANUAL_POWER_MONITOR_ITERATION != 1) {
			printf("loop for manual power monitoring!\n");
			for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
				for (int i = 0; i < MANUAL_POWER_MONITOR_ITERATION; i++) {
					lr_hardware(DATA_LENGTH, X_hw, Y_hw, &a0_hw, &a1_hw);
				}
			}
		}

		fclose(fp_v);

	}

	fpgacl_free((u32)X_hw);
	fpgacl_free((u32)Y_hw);

	FREQUENCY_SCALING_EPILOGUE(hardware_execution_time);
	VOLTAGE_SCALING_EPILOGUE();


	free(X_sw);
	free(Y_sw);

	return 0;
}


void lr_hardware(int n, DATA_TYPE *  X,
		DATA_TYPE *  Y, DATA_TYPE *A0, DATA_TYPE *A1) {


	accel_write(X, Y, n);
//	printf("mxv_hw: started\n");

	accel_start();
	sleep(1);  //interrupt

	accel_read(A0, A1);
//	accel_wait(); //polling
//	printf("mxv_hw: end\n");


}

int validate(DATA_TYPE a0_sw, DATA_TYPE a1_sw, DATA_TYPE a0_hw, DATA_TYPE a1_hw) {

	float diff_0 = fabs(a0_hw - a0_sw);
	float diff_1 = fabs(a1_hw - a1_sw);

	if( (diff_0 > 0.1 || diff_0 != diff_0)
	 || (diff_1 > 0.1 || diff_1 != diff_1))
	{
		printf("Error\n");
		printf("a0_sw=%f != a0_hw=%f , a1_sw=%f != a1_hw=%f  \n", a0_sw, a0_hw, a1_sw, a1_hw);
		return -1;
	}

	return 0;
}



void init_data(float* c_golden, float* b_golden, int n, int m) {

	int i, j;
	for (j=0; j<m; j++) {
		c_golden[j] = rand()/(1.0*RAND_MAX);
	}
	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			b_golden[i*m+j] = (1.0*RAND_MAX);
		}
	}
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

		sprintf(cmd, "cat lr_2X.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat  lr_2X.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}






}

