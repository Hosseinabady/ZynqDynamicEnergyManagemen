inputFiles = dir('log_*.txt');

%===serial_implementation====
software_energy(1)  = 0.029;
software_exetime(1) = 0.29;

%===openmp_implementation====
software_energy(2)  = 0.04768;
software_exetime(2) = 0.16;

%===openmp+neon_implementation====
software_energy(3)  = 0.0303;
software_exetime(3) = 0.128;


%==============================================
period_min      = 10;
period_max      = 24000;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;



