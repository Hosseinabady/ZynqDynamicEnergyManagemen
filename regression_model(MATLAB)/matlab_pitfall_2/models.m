


transform_data;

Data=xlsread('profiling_data_X_G_U.csv');

exe_time_limit = 158100000;

model_time;
model_pl;
model_ps;
model_mem;
total_energy=exe_time.*(PL_power+PS_power+MEM_power);
total_energy_estimate=estimated_time.*(PL_power_model_estimate+PS_power_model_estimate+MEM_power_model_estimate);
