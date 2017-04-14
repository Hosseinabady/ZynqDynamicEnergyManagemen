

for idx = 1:numel(v_min)
    v = v_min(idx);
    f = f_min(idx);
    
    for index_data = 1:numel(Data(:,1))
        if (Data(index_data, 3) == v && Data(index_data, 2) == f) 
            dvfs_eng(idx,1) = total_energy(index_data);
            dvfs_exetime(idx,1) = Data(index_data, 4);
        end
    end
end

dvfs_energy_voltage_e = [ 
                      0    0; %
                      1    0  %
       ];

dvfs_energy_model = fitlm(v_min, dvfs_eng, dvfs_energy_voltage_e, 'RobustOpts', 'on' );
dvfs_energy_model
dvfs_energy_model.Rsquared
dvfs_energy_model_estimate = feval(dvfs_energy_model, v_min);

dvfs_efficiency_factor = 100*(dvfs_eng(1,1)-dvfs_eng(idx,1))/dvfs_eng(1,1);
delat_e_per_delta_v = dvfs_energy_model.Coefficients.Estimate(2);