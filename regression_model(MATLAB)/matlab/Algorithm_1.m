
alpha_1 = PL_power_model.Coefficients.Estimate(1);
alpha_2 = PL_power_model.Coefficients.Estimate(2);

theta = time_model.Coefficients.Estimate(2);
gamma_1 = dvfs_energy_model.Coefficients.Estimate(2);
gamma_2 = dvfs_energy_model.Coefficients.Estimate(1);

alpha_4 = MEM_power_model.Coefficients.Estimate(1);
beta_1 = freq_voltage_model.Coefficients.Estimate(2);
beta_2 = freq_voltage_model.Coefficients.Estimate(1);


PFPGA_idle_sleep= 0.029294074;
 
alpha_3 = PFPGA_idle_sleep;
theta_3 = theta*PFPGA_idle_sleep;
fFPGA_max = f_min(1);
fFPGA_min = f_min(end);


t_soft = software_exetime;
e_soft = software_energy;



Emin=100000;
t=0;
impl = -1;
for i=1:3
	if (t_soft(i) < delta && e_soft(i) < Emin )
        Emin = e_soft(i);
        t = t_soft(i);
        impl = i;
    end
end

%==========================================================================
%           Energy Model 1
%==========================================================================
Emin_first_e_model = Emin;
impl_first_e_model = impl;
t_first_e_model    = t;

f=theta/delta;
if ( f < fFPGA_max )
    if (f > fFPGA_min)
        Vfpga = beta_1*f + beta_2;
        Efpga_first_e_model = theta*alpha_1*Vfpga*Vfpga +theta*alpha_2*Vfpga/f + theta*alpha_4 + alpha_3*T-theta_3/f;
        if (Efpga_first_e_model < Emin_first_e_model) 
            Emin_first_e_model = Efpga_first_e_model;
            t_first_e_model = delta;
            impl_first_e_model = 0;
        end
    else
        Vfpga = beta_1*fFPGA_min + beta_2;
        Efpga_first_e_model = theta*alpha_1*Vfpga*Vfpga +theta*alpha_2*Vfpga/fFPGA_min + theta*alpha_4 + alpha_3*T-theta_3/fFPGA_min;
        if (Efpga_first_e_model < Emin_first_e_model) 
            Emin_first_e_model = Efpga_first_e_model;
            t_first_e_model = delta;
            f = fFPGA_min;
            impl_first_e_model = 0;
        end
    end
end
    
impl_first_e_model;
Emin_first_e_model;
%Vfpga_first_model = Vfpga;

%==========================================================================
%           Energy Model 2
%==========================================================================



Emin_second_e_model = Emin;
impl_second_e_model = impl;
t_first_e_model    = t;

f=theta/delta;
if ( f < fFPGA_max )
    if (f > fFPGA_min)
        Vfpga = beta_1*f + beta_2;
        Efpga_second_e_model = gamma_1*Vfpga + gamma_2 + alpha_3*T-theta_3/f;
        if (Efpga_second_e_model < Emin_second_e_model) 
            Emin_second_e_model = Efpga_second_e_model;
            t_second_e_model = delta;
            impl_second_e_model = 0;
        end
    else
        Vfpga = beta_1*fFPGA_min + beta_2;
        Efpga_second_e_model = gamma_1*Vfpga + gamma_2 + alpha_3*T-theta_3/fFPGA_min;
        if (Efpga_second_e_model < Emin_second_e_model) 
            Emin_second_e_model = Efpga_second_e_model;
            t_second_e_model = delta;
            f = fFPGA_min;
            impl_second_e_model = 0;
        end
    end
end
    
impl_second_e_model;
Emin_second_e_model;

%==========================================================================
%           Real Measurement
%==========================================================================

impl_empirical = impl;
Emin_empirical = Emin;
for idx = 1:numel(target_period)
    if (target_period(idx) == T)
        if ( target_energy(idx) < Emin_empirical)
            Emin_empirical = target_energy(idx);
            impl_empirical = 0;
            break;
        end
    end
end

impl_empirical;
Emin_empirical;

First_model_error = 100*abs(Emin_empirical-Emin_first_e_model)/Emin_empirical;
Second_model_error = 100*abs(Emin_empirical-Emin_second_e_model)/Emin_empirical;
