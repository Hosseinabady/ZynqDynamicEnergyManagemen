inputFiles = dir('log_*.txt');


%===serial_implementation====
software_energy(1)  = 509.75;
software_exetime(1) = 6763.75;

%===openmp_implementation====
software_energy(2)  = 614.93;
software_exetime(2) = 3420.3;

%===openmp+neon_implementation====
software_energy(3)  = 524.67;
software_exetime(3) = 3216.7;


%==============================================

period_min      = 10;
period_max      = 6763*100; %240000;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;


