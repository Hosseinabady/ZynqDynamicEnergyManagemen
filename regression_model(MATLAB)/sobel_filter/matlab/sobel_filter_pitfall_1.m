inputFiles = dir('log_power_4X_*.txt');

%===serial_implementation====
software_energy(1)  = 194.1561064;
software_exetime(1) = 539.14;

%===openmp_implementation====
software_energy(2)  = 174.1340023;
software_exetime(2) = 383.9;

%===openmp+neon_implementation====
software_energy(3)  = 153.7291375;
software_exetime(3) = 377.60;


%==============================================
period_min      = 1;
period_max      = 539*1000;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;
