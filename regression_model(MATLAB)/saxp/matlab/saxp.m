inputFiles = dir('log_*.txt');


%===serial_implementation====
software_energy(1)  = 57.340;
software_exetime(1) = 270.85;

%===openmp_implementation====
software_energy(2)  = 57.718;
software_exetime(2) = 135.36;

%===openmp+neon_implementation====
software_energy(3)  = 62.346;
software_exetime(3) = 121.29;


%==============================================

period_min      = 5;
period_max      = 270*2000;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;



