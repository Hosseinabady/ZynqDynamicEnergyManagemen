


%period_1 = t_mp;
period_1 = max(2*t_mp, t_ep/2);
T_1      = period_1;                     %state.period
delta_1  = period_1;                     %state.delta

%period_2 = t_ep*4;
period_2 = 2*t_ep;
T_2      = period_2;                     %state.period
delta_2  = period_2;                     %state.delta



number_of_frame = 100;


total_energy_algorithm2 = 0;
current_platform = 0;                    %0=FPGA

number_of_iteration_algorithm2=400;
current_energy = 0;

fileID = fopen('random_number_1000.txt','r');
random_index = fscanf(fileID,'%f');
fclose(fileID);

fileID = fopen('hw_sw_pitfall_1.txt','w');
%Algorithm 2
energy_overhead = 0;
random_index(1) = 1;
k = 1;
for i = 1: 2: number_of_iteration_algorithm2 
    
    if random_index(i) >0 && random_index(i) <= probability
       period = period_1;
       T = T_1;
       delta = delta_1;
    end
    if random_index(i) >probability && random_index(i) <= 100
       period = period_2;
       T = T_2;
       delta = delta_2;
    end
    
    %state_life_time = state_life_time_1;
    
    Algorithm_1
    
    new_platform = impl_second_e_model;
    new_energy   = Emin_second_e_model;
    
    %new_platform = impl_first_e_model;
    %new_energy = Emin_first_e_model;
    if (new_platform == 0)
        fprintf(fileID,'%d %f %f %f %f\n',new_platform, Vfpga_first_model, freq_first_model, T, delta);
    else
        fprintf(fileID,'%d %f %f %f %f\n',new_platform, 0, 0, T, delta);
    end
        
    
end

fclose(fileID);

