clear;
addpath('../../matlab');
bs
models;
voltage_frequency;
dvfs_efficiency;
frame_energy;
evaluation_factors;
energy_model_eval;

t_mp = 65;
t_ep = 15000;
%period_1 = t_mp;
period_1 = max(2*t_mp, t_ep/2);
T_1      = period_1;                     %state.period
delta_1  = period_1;                     %state.delta

%period_2 = t_ep*4;
period_2 = 2*t_ep;
T_2      = period_2;                     %state.period
delta_2  = period_2;                     %state.delta


number_of_frame = 100;



hw_sw_file_name = 'hw_sw_pitfall_1.txt';
calculate_energy