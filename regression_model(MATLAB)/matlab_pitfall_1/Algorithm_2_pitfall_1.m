

period_1 = t_mp;
T_1      = period_1;                     %state.period
delta_1  = period_1;                     %state.delta

period_2 = t_ep*4;
T_2      = period_2;                     %state.period
delta_2  = period_2;                     %state.delta


number_of_frame = 100;


total_energy_algorithm2 = 0;
current_platform = 0;                    %0=FPGA

number_of_iteration_algorithm2=400;
current_energy = 0;

for i = 1: 1000 
    p=randperm(100);
    random_index(i) = p(1);
end


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
    
    %new_platform = impl_second_e_model;
    %new_energy   = Emin_second_e_model;
    
    new_platform = impl_first_e_model;
    new_energy = Emin_first_e_model;
    
    if (new_platform ~= 0 && current_platform == 0) 
        total_energy_algorithm2 = total_energy_algorithm2 + current_energy; % maximum overhead t1-->t2
        energy_overhead = energy_overhead + current_energy;
    end
 
    if (new_platform == 0 && current_platform ~= 0) 
        total_energy_algorithm2 = total_energy_algorithm2 + 9.4;
        total_energy_algorithm2 = total_energy_algorithm2 + current_energy*ceil(48/delta);
        energy_overhead = energy_overhead + current_energy*ceil(48/delta);
    end
        
    current_platform = new_platform;
    current_energy  = new_energy;
    total_energy_algorithm2 = total_energy_algorithm2  + current_energy*number_of_frame;%state_life_time/T;

    for jj = 1:5
        array_period(k+jj, 1) = period;
        array_delat(k+jj, 1) = delta;
        array_energy_overhead(k+jj, 1) = energy_overhead;
        array_total_energy_algorithm2(k+jj, 1) = total_energy_algorithm2;
        array_platform(k+jj, 1)= new_platform;
        if (new_platform == 0)
            array_PL_voltage(k+jj, 1) = Vfpga_first_model;
        else
            array_PL_voltage(k+jj, 1) = 0;
        end
    end
    
    k=k+jj;
end


total_energy_algorithm2;
%energy_overhead
total_ideal_energy_algorithm2 = 0;

%ideal case
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
    
    current_platform = new_platform;
    current_energy  = new_energy;
    
    total_ideal_energy_algorithm2 = total_ideal_energy_algorithm2  + current_energy*number_of_frame;%state_life_time/T;
end

total_ideal_energy_algorithm2;


%only software
total_only_software_energy_algorithm2=0;
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
    
   % Algorithm_1
    
   new_energy = Inf;
   new_software_exetime=Inf;
   for j = 1:3
     if software_exetime(j) < delta
         if software_energy(j) < new_energy
             new_energy = software_energy(j);
             new_software_exetime = software_exetime(j);
         end
     end
   end
   
   current_energy  = new_energy;
    
   total_only_software_energy_algorithm2 = total_only_software_energy_algorithm2  + current_energy*number_of_frame;%state_life_time/T;
end

total_only_software_energy_algorithm2;





%only hardware
total_only_hardware_energy_algorithm2=0;
for i = 1: 2: number_of_iteration_algorithm2
    
    if random_index(i) >0 && random_index(i) <= probability
       period = period_1;
       T = T_1;
       delta = delta_1;
    end
    if random_index(i) > probability && random_index(i) <= 100
       period = period_2;
       T = T_2;
       delta = delta_2;
    end
    
 %   state_life_time = state_life_time_1;
    
    new_energy = Inf;
    for idx = 1:numel(target_period)
        if (target_period(idx) == T)
            new_energy =  target_energy(idx);
            break;
        end
    end
       
        

    current_energy  = new_energy;
    
    total_only_hardware_energy_algorithm2 = total_only_hardware_energy_algorithm2  + current_energy*number_of_frame;%state_life_time/T;
end

total_only_hardware_energy_algorithm2;


probability
Algorithm_2_efficiency = 100*(total_only_hardware_energy_algorithm2-total_energy_algorithm2)/total_only_hardware_energy_algorithm2
