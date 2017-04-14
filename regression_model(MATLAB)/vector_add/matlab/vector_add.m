inputFiles = dir('log_*.txt');


%===serial_implementation====
software_energy(1)  = 8.215;
software_exetime(1) = 21.20;

%===openmp_implementation====
software_energy(2)  = 8.945;
software_exetime(2) = 13.51;

%===openmp+neon_implementation====
software_energy(3)  = 10.13;
software_exetime(3) = 16.34;


%==============================================

period_min      = 10;
period_max      = 21*24000;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;
