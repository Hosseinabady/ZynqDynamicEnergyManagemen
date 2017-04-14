inputFiles = dir('log_*.txt');

T = 80;
delta = 80;
%===serial_implementation====
software_energy(1)  = 12.47;
software_exetime(1) = 142.6;

%===openmp_implementation====
software_energy(2)  = 20.764;
software_exetime(2) = 76.1;

%===openmp+neon_implementation====
software_energy(3)  = 20.580;
software_exetime(3) = 73.07;


%==============================================
period_min      = 10;
period_max      = 142*1000; %240000;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;


