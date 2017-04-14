inputFiles = dir('log_*.txt');

%===serial_implementation====
software_energy(1)  =1978.622229;
software_exetime(1) = 2103.3;

%===openmp_implementation====
software_energy(2)  = 1123.487365;
software_exetime(2) = 1094.9;

%===openmp+neon_implementation====
software_energy(3)  = 689.2996943;
software_exetime(3) = 668.8;


%==============================================
period_min      = 10;
period_max      = 2103*300;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;
