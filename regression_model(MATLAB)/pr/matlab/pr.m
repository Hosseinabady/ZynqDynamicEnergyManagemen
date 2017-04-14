inputFiles = dir('log_*.txt');

%===serial_implementation====
software_energy(1)  = 20.26;
software_exetime(1) = 234.02;

%===openmp_implementation====
software_energy(2)  = 30.89;
software_exetime(2) = 149.56;

%===openmp+neon_implementation====
software_energy(3)  = 31.31;
software_exetime(3) = 133.07;


%==============================================
period_min      = 10;
period_max      =  234*1000; %240000;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;





