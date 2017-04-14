
theta = time_model.Coefficients.Estimate(2);
fFPGA_max = f_min(1);
fFPGA_min = f_min(end);

beta_1 = freq_voltage_model.Coefficients.Estimate(2);
beta_2 = freq_voltage_model.Coefficients.Estimate(1);

alpha_1 = PL_power_model.Coefficients.Estimate(1);
alpha_2 = PL_power_model.Coefficients.Estimate(2);

alpha_4 = MEM_power_model.Coefficients.Estimate(1);
gamma_1 = dvfs_energy_model.Coefficients.Estimate(2);
gamma_2 = dvfs_energy_model.Coefficients.Estimate(1);

PFPGA_idle_sleep= 0.029294074;
 
alpha_3 = PFPGA_idle_sleep;
theta_3 = theta*PFPGA_idle_sleep;

idx=1;
for period=period_min:period_step:period_max
    
    task_deadline =period - other_tasks_exe_time;
    T = period;
    f_task = theta/task_deadline;
    
    if ( f_task < fFPGA_max )
        if (f_task > fFPGA_min)
            Vfpga = beta_1*f_task + beta_2;
            fpga_memory_active(idx, 1) = gamma_1*Vfpga + gamma_2;
            fpga_idle(idx, 1) = alpha_3*T-theta_3/f_task;
            Efpga_second_e_model(idx, 1) = fpga_memory_active(idx, 1) + fpga_idle(idx, 1);
            target_period_second_model(idx, 1) = T;
            target_energy_second_model(idx, 1) = Efpga_second_e_model(idx, 1);
            idx=idx+1;
        else
            Vfpga = beta_1*fFPGA_min + beta_2;
            fpga_memory_active(idx, 1) = gamma_1*Vfpga + gamma_2;
            fpga_idle(idx, 1) = alpha_3*T-theta_3/fFPGA_min;
            Efpga_second_e_model(idx, 1) = fpga_memory_active(idx, 1) + fpga_idle(idx, 1);
            target_period_second_model(idx, 1) = T;
            target_energy_second_model(idx, 1) = Efpga_second_e_model(idx, 1);
            idx=idx+1;
        end
    end
end