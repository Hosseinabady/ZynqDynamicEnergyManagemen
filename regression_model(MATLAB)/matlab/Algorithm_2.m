p_= 1;
q_=1;
n_=100;
m_=20;


total_energy_algorithm2 = 0;
current_platform = 0;                    %0=FPGA

number_of_iteration_algorithm2=400;
current_energy = 0;

%fileID = fopen('random_number_1000.txt','w');
%for i = 1: 1000 
%    p=randperm(100);
%    random_index(i) = p(1);
%    fprintf(fileID,'%d \n', p);
%end
%fclose(fileID);

fileID = fopen('random_number_1000.txt','r');
random_index = fscanf(fileID,'%f');
fclose(fileID);


%Algorithm 2 with timeout  = 0
energy_overhead = 0;
random_index(1) = 1;
k = 1;
number_of_period_in_current_state = 0;
total_energy_algorithm2 = 0;
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
    number_of_frame = (q_-m_)/(p_-n_)*random_index(i+200) +(q_-p_*(q_-m_)/(p_-n_));
    %state_life_time = state_life_time_1;
    
    Algorithm_1
    
    new_platform = impl_second_e_model;
    new_energy   = Emin_second_e_model;
    
    %new_platform = impl_first_e_model;
    %new_energy = Emin_first_e_model;
    
    if (new_platform ~= 0 && current_platform == 0) 
        total_energy_algorithm2 = total_energy_algorithm2 + current_energy; % maximum overhead t1-->t2
        energy_overhead = energy_overhead + current_energy;
        
    end
 
    if (new_platform == 0 && current_platform ~= 0) 

        total_energy_algorithm2 = total_energy_algorithm2 + 9.4; %reconf energy
        total_energy_algorithm2 = total_energy_algorithm2 + current_energy*ceil(48/delta); %reconf delay
        energy_overhead = energy_overhead + current_energy*ceil(48/delta);
        number_of_period_in_current_state = 0;
    end
        
    current_platform = new_platform;
    current_energy  = new_energy;
    total_energy_algorithm2 = total_energy_algorithm2  + current_energy*number_of_frame;%state_life_time/T;

end


total_energy_algorithm2;
%energy_overhead


%Algorithm 2 with timeout > 0
energy_overhead = 0;
random_index(1) = 1;
k = 1;
number_of_period_in_current_state = 0;
total_energy_algorithm2_with_timeout = 0;
time_out_in_sw = 0;
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
    number_of_frame = (q_-m_)/(p_-n_)*random_index(i+200) +(q_-p_*(q_-m_)/(p_-n_));
    %state_life_time = state_life_time_1;
    
    Algorithm_1
    
    new_platform = impl_second_e_model;
    new_energy   = Emin_second_e_model;
    
    %new_platform = impl_first_e_model;
    %new_energy = Emin_first_e_model;
    
    if (new_platform ~= 0 && current_platform == 0) 
        if (delta > 400)
            threshold = 1;
        else
            threshold = 1+400/delta;
        end
        if (number_of_frame > delta)
            total_energy_algorithm2_with_timeout = total_energy_algorithm2_with_timeout + 9.4; %reconf energy
            time_out_in_sw=0;
        else 
            total_energy_algorithm2_with_timeout = total_energy_algorithm2_with_timeout + 0.029*10; %reconf energy
        end
        time_out_in_sw=time_out_in_sw+delta;
        total_energy_algorithm2_with_timeout = total_energy_algorithm2_with_timeout + current_energy; % maximum overhead t1-->t2
        energy_overhead = energy_overhead + current_energy;
        
    end
 
    if (current_platform ~= 0) 
        time_out_in_sw=time_out_in_sw+1;
    end
    if (new_platform == 0 && current_platform ~= 0) 
        total_energy_algorithm2_with_timeout = total_energy_algorithm2_with_timeout + current_energy*ceil(48/delta); %reconf delay
        energy_overhead = energy_overhead + current_energy*ceil(48/delta);
        number_of_period_in_current_state = 0;
    end
        
    current_platform = new_platform;
    current_energy  = new_energy;
    total_energy_algorithm2_with_timeout = total_energy_algorithm2_with_timeout  + current_energy*number_of_frame;%state_life_time/T;

end


total_energy_algorithm2_with_timeout;
%energy_overhead








total_threshold_policy_energy_algorithm2 = 0;

%Algorithm 2-- with threshold
energy_overhead = 0;
random_index(1) = 1;
k = 1;
delay_TB=0;
number_of_period_in_current_state = 0;
active_time = 0;
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
    
    
    %new_platform = impl_first_e_model;
    %new_energy = Emin_first_e_model;
    
    if (impl_second_e_model ~= 0 && current_platform == 0) 
        new_platform = impl_second_e_model;
        new_energy   = Emin_second_e_model;
%        total_threshold_policy_energy_algorithm2 = total_threshold_policy_energy_algorithm2 + current_energy; % maximum overhead t1-->t2
        energy_overhead = energy_overhead + current_energy;
        delay_TB=1;
    end
 
    if (current_platform == 0) 
        active_time=active_time+1;
    end
    
    if (impl_second_e_model == 0 && current_platform ~= 0) 
        if  (active_time < 1+400/delta)
            new_platform = impl_second_e_model;
            new_energy   = Emin_second_e_model;
        
%        if  (delay_TB > 4)
            total_threshold_policy_energy_algorithm2 = total_threshold_policy_energy_algorithm2 + 9.4; %reconf energy
            total_threshold_policy_energy_algorithm2 = total_threshold_policy_energy_algorithm2 + current_energy*ceil(48/delta); %reconf delay
%        end
            energy_overhead = energy_overhead + current_energy*ceil(48/delta);
            number_of_period_in_current_state = 0;
            delay_TB=1;
            active_time=0;
            delay_TB = delay_TB + 1;
        end
    end
      
    
    current_platform = new_platform;
    current_energy  = new_energy;
    total_threshold_policy_energy_algorithm2 = total_threshold_policy_energy_algorithm2  + current_energy*number_of_frame;%state_life_time/T;

end

total_threshold_policy_energy_algorithm2;

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

    number_of_frame = (q_-m_)/(p_-n_)*random_index(i+200) +(q_-p_*(q_-m_)/(p_-n_));
       Algorithm_1
       new_energy   = Efpga_second_e_model;

 %   state_life_time = state_life_time_1;
    
%    new_energy = Inf;
%    for idx = 1:numel(target_period)
%        if (abs(target_period(idx) - T)<1)
%            new_energy =  target_energy(idx);
%            break;
%        end
%    end
       
        

    current_energy  = new_energy;
    
    total_only_hardware_energy_algorithm2 = total_only_hardware_energy_algorithm2  + current_energy*number_of_frame;%state_life_time/T;
end

total_only_hardware_energy_algorithm2;


probability
Algorithm_2_efficiency = 100*(total_only_hardware_energy_algorithm2-total_energy_algorithm2)/total_only_hardware_energy_algorithm2
Algorithm_2_efficiency_with_threshold_policy = 100*(total_only_hardware_energy_algorithm2-total_energy_algorithm2_with_timeout)/total_only_hardware_energy_algorithm2



%Algorithm_2_efficiency_with_ideal = 100*(total_ideal_energy_algorithm2-total_energy_algorithm2)/total_ideal_energy_algorithm2
%Algorithm_2_efficiency_with_threshold_policy_with_ideal = 100*(total_ideal_energy_algorithm2-total_threshold_policy_energy_algorithm2)/total_ideal_energy_algorithm2
