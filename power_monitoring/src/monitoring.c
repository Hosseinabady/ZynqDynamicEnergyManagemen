#include "monitoring.h"




struct fpgacl_sample *head;

char log_file_name[1000];
void file_power_profile_create (char *file_name) {
	time_t t;
	time(&t);
	strcat(file_name, ctime(&t));
	int charIndex = 0;
	while(file_name[charIndex] != '\0') {
		if (file_name[charIndex] == ' ' || file_name[charIndex] == ':')
			file_name[charIndex]='_';
		charIndex++;
	}
	file_name[charIndex-1] = '\0';

	strcat(file_name, "_Hardware_X");
#ifdef SDEPCX
	char strX[100];
	sprintf(strX, "%d", SDEPCX);
	strcat(file_name, strX);
#endif //SDEPCX

#ifdef SDEPCX
	strcat(file_name, "_G");
	char strG[100];
	sprintf(strG, "%d", SDEPCG);
	strcat(file_name, strG);
#endif //SDEPCX

#ifdef CPUUTIL
	strcat(file_name, "_U");
	char strU[100];
	sprintf(strU, "%d", CPUUTIL);
	strcat(file_name, strU);
#endif //CPUUTIL

	strcat(file_name, ".txt");


	FILE *fp=fopen(file_name, "a");
	fclose(fp);

}




void power_monitoring_prologue () {

	struct fpgacl_sample *sample = head;
	head = (struct fpgacl_sample *)fpgacl_read_sample_pthread();

	fpgacl_read_sample_start();
}


void power_monitoring_stop() {
	fpgacl_read_sample_stop();
}
void power_monitoring_epilogue() {
	power_monitoring_stop();
	fpgacl_save_average_pthread(head, log_file_name);
	fpgacl_clear_sample_pthread(head);
}


