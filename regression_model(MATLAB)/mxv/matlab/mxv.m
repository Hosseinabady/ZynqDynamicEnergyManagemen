inputFiles = dir('log_*.txt');

%===serial_implementation====
software_energy(1)  = 8.21;
software_exetime(1) = 53.3;

%===openmp_implementation====
software_energy(2)  = 11.03;
software_exetime(2) = 37.3;

%===openmp+neon_implementation====
software_energy(3)  = 10.63;
software_exetime(3) = 24.5;


%==============================================
period_min      = 10;
period_max      = 53*2400;
period_step     = 1;
other_tasks_exe_time     = 0;
f_min_available = 20.5;



%===============================================
%       data for algorithm 2
%===============================================

period_1 = 100;
T_1      = period_1;                     %state.period
delta_1  = period_1;                     %state.delta


period_2 = 25;
T_2      = period_2;                     %state.period
delta_2  = period_2;                     %state.delta



state_life_time_1 = 50000;
state_life_time_2 = 2000;