
#ifndef _GNU_SOURCE
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#endif

#ifndef __USE_GNU
#define __USE_GNU
#endif

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include "pstream.h"
#include <sstream>

int reconf_req = 0;
int reconf_ack = 0;



pthread_mutex_t mutex;
pthread_t  thread_ID;

void check_for_reconf(unsigned int tid);
void reconfigure_pl(unsigned int tid);
void *sdepc(void *tid) ;
int system_stat(unsigned int tid);

enum {
  APP, // Indicates it’s the first person’s turn.
  SDEPC // Indicates it’s the second person’s turn.
};



int main() {
	unsigned int tid = getpid();
	printf("PID of main process: %d\n", tid);
	check_for_reconf(tid);

}


void check_for_reconf(unsigned int tid) {

	unsigned int* tidp = (unsigned int*)malloc(sizeof(unsigned int));
	*tidp = tid;

	int reconf_req_local;

	printf("==hello sdepc\n");
	pthread_mutex_init(&mutex, NULL);

	cpu_set_t cpu_set2;
	CPU_SET(1, &cpu_set2);
	pthread_create(&thread_ID, NULL, sdepc, tidp);
	sched_setaffinity(thread_ID, sizeof(cpu_set_t), &cpu_set2);


	int index = 0;
	while(1) {
//		printf("==from sdepc index = %d\n", index++);
		reconf_req_local = 0;
		pthread_mutex_lock(&mutex);
		if (reconf_req == 1) {
			reconf_req_local = 1;
			reconf_ack = 1;
		}
		pthread_mutex_unlock(&mutex);


		if(reconf_req_local == 1) {
			printf("==from sdepc request for recon\n");
			while(1) {
				sleep(1);
				printf("==from sdepc wait for reconf\n");
				pthread_mutex_lock(&mutex);
				if (reconf_req==0);
					reconf_req_local = 0;
				pthread_mutex_unlock(&mutex);

				if (reconf_req_local == 0)
					break;
			}
			pthread_mutex_lock(&mutex);
			reconf_ack = 0;
			pthread_mutex_unlock(&mutex);
			printf("==from sdepc reconf end\n");
		}



		sleep(2);

	}
}



void *sdepc(void *tid) {

	reconfigure_pl(*(unsigned int*)tid);
}

void reconfigure_pl(unsigned int tid) {
	printf("**hello reconfigure_pl\n");
	char c;
	int reconf_ack_local;



	while(1) {
		system_stat(tid);

		if (c=='r') {

			pthread_mutex_lock(&mutex);
			reconf_req = 1;
			pthread_mutex_unlock(&mutex);
			printf("**from reconfigure_pl reconf_req = 1\n");

			int index = 0;
			while(1) {
				printf("**from reconfigure_pl index = %d\n", index++);
				sleep(1);
				reconf_ack_local = 0;
				pthread_mutex_lock(&mutex);
				if (reconf_ack == 1) {
					reconf_ack_local = 1;
				}
				pthread_mutex_unlock(&mutex);

				if (reconf_ack_local == 1)
					break;
			}
			sleep(2);


			pthread_mutex_lock(&mutex);
			reconf_req = 0;
			pthread_mutex_unlock(&mutex);
		}
		sleep(2);
	}



}

int system_stat(unsigned int tid) {
	printf("thread id = %d\n", tid);
	float max_exe_time;
	float u_cpu=1;
	char process_name[100];

	std::cout << "please enter max_exe_time" << std::endl;
	std::cin >> max_exe_time;


	std::ostringstream os_tid;
	os_tid << tid;

	std::string pid = os_tid.str();
	std::string command("perf stat -t ");
	command = command + pid + " sleep 1";


	redi::ipstream proc(command, redi::pstreams::pstderr);
	std::string line;
	std::cout << "command  : " <<command << '\n';

	u_cpu = 0;
	// read child's stdout
	while (std::getline(proc.out(), line)) {
//		std::cout << "line  : " <<line << '\n';
		std::size_t found = line.find( "CPUs utilized");

		if (found!=std::string::npos) {
		//			std::cout << "stdout: " << line << '\n';

			const char* p;
			p = strtok( (char*)line.c_str(), " \t" );
			p = strtok( NULL, " \t" );
			p = strtok( NULL, " \t" );
			p = strtok( NULL, " \t" );
			p = strtok( NULL, " \t" );

			char* pEnd;
			u_cpu = strtod (p, &pEnd);
			std::cout << "cpu utilization : " << u_cpu << '\n';
		}
	}
}
