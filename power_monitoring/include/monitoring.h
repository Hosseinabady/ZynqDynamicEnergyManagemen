#ifndef __MONITORING__H__
#define __MONITORING__H__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>


#include <measurement.h>
#include <set_frequency.h>

/* Include polybench common header. */

/* Include benchmark-specific header. */






void file_power_profile_create (char *file_name);
void power_monitoring_prologue();
void power_monitoring_epilogue();
void power_monitoring_stop();

#ifdef POWER_MONITORING
#define POWER_MONITORING_PROLOGUE() power_monitoring_prologue()
#define POWER_MONITORING_EPILOGUE() power_monitoring_epilogue()
#define POWER_MONITORING_STOP() power_monitoring_stop()
#else
#define POWER_MONITORING_PROLOGUE()
#define POWER_MONITORING_EPILOGUE()
#define POWER_MONITORING_STOP()
#endif //POWER_MONITORING


#ifdef VOLTAGE_SCALING
#define VOLTAGE_SCALING_PROLOGUE(V_min, V_max, V_step) \
	float volt = V_max; \
	for (volt = V_max; volt >= V_min; volt-=V_step) \
      { \
		printf("VCCINT voltage = %f\n", volt); \
		set_VCCINT_voltage(volt); \
		sleep(1); \
		FILE* fp=fopen(log_file_name, "a"); \
		fprintf(fp, "VCCINT voltage = %f\n", volt); \
		fprintf(fp, "SDEPCX = %d\n", SDEPCX);  \
		fprintf(fp, "SDEPCG = %d\n", SDEPCG); \
		fclose(fp);

#define VOLTAGE_SCALING_EPILOGUE() \
		}
#else
#define VOLTAGE_SCALING_PROLOGUE()
#define VOLTAGE_SCALING_EPILOGUE()
#endif //VOLTAGE_SCALING



#ifdef FREQUENCY_SCALING
#define FREQUENCY_SCALING_PROLOGUE(f_factor_min, f_factor_max, f_factor_step) \
	int freq = f_factor_min; \
	for (freq = f_factor_min; freq < f_factor_max; freq+=f_factor_step) \
	{ \
		double total_value = 0; \
		int count = 0; \
		pl_frequency_set(FPGA0_CLK, freq, 1); \
		FILE* fp=fopen(log_file_name, "a"); \
		fprintf(fp, "frequency factor = %d \n", freq); \
		fprintf(fp, "------------------------------\n"); \
		fclose(fp);

#define FREQUENCY_SCALING_EPILOGUE(hardware_execution_time) \
		printf("frequency factor %d \n", freq); \
		printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time); \
		fp=fopen(log_file_name, "a"); \
		fprintf(fp, "\n hardware execution time  %.6lf ms elapsed\n", hardware_execution_time); \
		fprintf(fp, "==============================================\n"); \
		fclose(fp); \
	}
#else
#define FREQUENCY_SCALING_PROLOGUE()
#define FREQUENCY_SCALING_EPILOGUE()
#endif



#ifdef MAXIMUM_FREQUENCY
#define MAXIMUM_FREQUENCY_PROLOGUE() \
if (CPUUTIL==100) {\
	char max_frequency_file_name[1000] = "max_freq.txt";\
	FILE* fpMaxFrq=fopen(max_frequency_file_name, "a");\
	float volt = 1;\
	for (volt = 1.0; volt > 0.85; volt -= 0.01) {\
		printf("VCCINT voltage = %f\n", volt);\
		set_VCCINT_voltage(volt);\
		sleep(1);\
	\
		int freq = 9;\
		int max_frequency_factor = freq;\
		for (freq = 10; freq < 40; freq=freq+1)\
		{\
			double total_value = 0;\
			int count = 0;\
			pl_frequency_set(FPGA0_CLK, freq, 1);\
			printf( "frequency factor = %d \n", freq);\

	\


#define MAXIMUM_FREQUENCY_EPILOGUE() \
			status = validate(POLYBENCH_ARRAY(A_hw),POLYBENCH_ARRAY(A_sw));\
	\
			if (status == 0) {\
				printf("Validation PASSED!\n");\
			} else {\
				printf("Validation FAILED!\n");\
				max_frequency_factor = freq;\
			}\
	\
		}\
		fprintf(fpMaxFrq, "SDEPCX = %d , SDEPCG = %d , VCCINT-voltage = %f , max-frequency-factor = %d\n",  SDEPCX, SDEPCG, volt, max_frequency_factor+1);\
	}\
	\
	fclose(fpMaxFrq);\
}
#else
#define MAXIMUM_FREQUENCY_PROLOGUE()
#define MAXIMUM_FREQUENCY_EPILOGUE()
#endif
#endif //__MONITORING__H__
