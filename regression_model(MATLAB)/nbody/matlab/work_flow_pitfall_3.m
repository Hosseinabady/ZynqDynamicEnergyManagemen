clear;
rmpath ('../../matlab');
rmpath ('../../matlab_pitfall_1');
rmpath ('../../matlab_pitfall_2');
addpath ('../../matlab_pitfall_3');

nbody_pitfall_3
models;
voltage_frequency;
dvfs_efficiency;
frame_energy;
evaluation_factors;
energy_model_eval;


t_mp = 24;
t_ep = 3133;
%period_1 = t_mp;
period_1 = max(2*t_mp, t_ep/2);
T_1      = period_1;                     %state.period
delta_1  = period_1;                     %state.delta

%period_2 = t_ep*4;
period_2 = 2*t_ep;
T_2      = period_2;                     %state.period
delta_2  = period_2;                     %state.delta


number_of_frame = 100;



%probability = 10;
%Algorithm_2
%probability = 20;
%Algorithm_2
probability = 50;
Algorithm_2
%probability = 70;
%Algorithm_2
%probability = 90;
%Algorithm_2