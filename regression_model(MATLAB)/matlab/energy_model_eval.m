
%measurement & original model
for idx = 1:numel(v_min)
    v = v_min(idx);
    f = f_min(idx);
    
    for index_data = 1:numel(Data(:,1))
        if (Data(index_data, 3) == v && Data(index_data, 2) == f) 
            dvfs_eng_measurement(idx,1) = total_energy(index_data);
            dvfs_exetime_measurement(idx,1) = Data(index_data, 4);
            
            dvfs_eng_original_model(idx,1) = total_energy_estimate(index_data);
            dvfs_exetime_original_model(idx,1) = estimated_time(index_data);
        end
    end
end


%linear model
dvfs_energy_linear_model = feval(dvfs_energy_model, v_min);


original_model_goodness=goodnessOfFit(dvfs_eng_original_model, dvfs_eng_measurement, 'NMSE')
linear_model_goodness=goodnessOfFit(dvfs_energy_linear_model, dvfs_eng_measurement, 'NMSE')