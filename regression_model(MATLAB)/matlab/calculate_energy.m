    total_energy = 0;
    
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

    
    




    number_of_frame = 100;

    
    
    fileID = fopen(hw_sw_file_name,'r');
    A = fscanf(fileID,'%d %f %f %f %f\n', [5, Inf]);
    [m,n] = size(A);
    for k=1:n
        impl  = A(1, k);
        Vfpga = A(2, k);
        f     = A(3, k);
        T     = A(4, k);
        delta = A(5, k);
        if impl == 0 
            %current_energy = theta*alpha_1*Vfpga*Vfpga +theta*alpha_2*Vfpga/f + theta*alpha_4 + alpha_3*T-theta_3/f;
            current_energy = gamma_1*Vfpga + gamma_2 + alpha_3*T-theta_3/f;
            if (k > 1)
                if (A(1, k-1) ~=0 )  
                    total_energy = total_energy + 9.4;
                    total_energy = total_energy + current_energy*ceil(48/delta);
                end
            end
        end
       
        if impl == 1
            current_energy = software_energy(1);
            if (k > 1)
                if (A(1, k-1) == 0 ) 
                   total_energy = total_energy + current_energy; 
                end
            end
        end
    
        if impl == 2 
            current_energy = software_energy(2);
            if (k > 1)
                if (A(1, k-1) == 0 ) 
                   total_energy = total_energy + current_energy; 
                end
            end
        end

        if impl == 3 
            current_energy = software_energy(3);
            if (k > 1)
                if (A(1, k-1) == 0 ) 
                   total_energy = total_energy + current_energy; 
                end
            end
        end
    
        total_energy = total_energy + current_energy*number_of_frame;
    end
    total_energy
    fclose(fileID);


