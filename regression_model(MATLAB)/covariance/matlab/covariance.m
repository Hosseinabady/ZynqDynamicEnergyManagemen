inputFiles = dir('log_*.txt');

%===serial_implementation====
software_energy(1)  = 6.60;
software_exetime(1) = 66.9;

%===openmp_implementation====
software_energy(2)  = 11.84;
software_exetime(2) = 52.5;

%===openmp+neon_implementation====
software_energy(3)  = 7.073;
software_exetime(3) = 51.51;


%==============================================
period_min      = 1;
period_max      = 66*2400;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;
