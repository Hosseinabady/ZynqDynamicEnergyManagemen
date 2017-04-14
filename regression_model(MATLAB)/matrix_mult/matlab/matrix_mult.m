inputFiles = dir('log_*.txt');

%===serial_implementation====
software_energy(1)  = 81.4;
software_exetime(1) = 582.699;

%===openmp_implementation====
software_energy(2)  = 67.23;
software_exetime(2) = 267.92;

%===openmp+neon_implementation====
software_energy(3)  = 50.162;
software_exetime(3) = 251.8;


%==============================================
period_min      = 100;
period_max      = 582*2000;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;



%===============================================
%       data for algorithm 2
%===============================================

period_1 = 1000;
T_1      = period_1;                     %state.period
delta_1  = period_1;                     %state.delta


period_2 = 252;
T_2      = period_2;                     %state.period
delta_2  = period_2;                     %state.delta



state_life_time_1 = 50000;
state_life_time_2 = 2000;