inputFiles = dir('log_*.txt');


%===serial_implementation====
software_energy(1)  = 21.493;
software_exetime(1) = 126.4;

%===openmp_implementation====
software_energy(2)  = 27.20;
software_exetime(2) = 74.53;

%===openmp+neon_implementation====
software_energy(3)  = 26.62;
software_exetime(3) = 50.66;


%==============================================

period_min      = 1;
period_max      = 126*2000;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;


