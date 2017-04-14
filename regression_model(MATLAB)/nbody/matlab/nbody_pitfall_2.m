inputFiles = dir('log_*.txt');

%===serial_implementation====
software_energy(1)  = 759.7143492;
software_exetime(1) = 2103.3;

%===openmp_implementation====
software_energy(2)  = 481.2220799;
software_exetime(2) = 1094.9;

%===openmp+neon_implementation====
software_energy(3)  = 304.7145504;
software_exetime(3) = 668.8;


%==============================================
period_min      = 10;
period_max      = 2103*300;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;
