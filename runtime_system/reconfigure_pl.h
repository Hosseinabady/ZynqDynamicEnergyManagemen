
class run_time_state {
public: 
	Model    current_state;
	unsigned int thread_id;
	float        cpu_util;
	
	void thread_stat() {
		printf("thread id = %d\n", thread_id);
		float max_exe_time;

		Model new_model;
		char process_name[100];

		std::cout << "please enter max_exe_time" << std::endl;
		std::cin >> max_exe_time;
			
			
		std::ostringstream os_tid;
		os_tid << thread_id;
			
		std::string pid = os_tid.str();
		std::string command("perf stat -t ");
		command = command + pid + " sleep 1";


		redi::ipstream proc(command, redi::pstreams::pstderr);
		std::string line;
		std::cout << "command  : " <<command << '\n';
			
		cpu_util = 0;
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
				cpu_util = strtod (p, &pEnd);
				std::cout << "cpu utilization : " << cpu_util << '\n';
			} 
		}
	}
	
};

