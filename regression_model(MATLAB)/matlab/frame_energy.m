
PFPGA_idle_sleep= 0.029294074;

index=1;
for period=period_min:period_step:period_max
    
    task_deadline =period - other_tasks_exe_time;

    for i = 1:numel(dvfs_exetime(:,1))
        if (task_deadline < dvfs_exetime(i,1)) 
            break
        end
    end
    
    i = i - 1;
    if (i > 0)
        target_exe_time(index, 1) = dvfs_exetime(i,1);
        target_period(index, 1) = period;
        target_energy(index, 1) = dvfs_eng(i,1); %without idle time
        target_energy(index, 1) = target_energy(index, 1) + (target_period(index, 1)-target_exe_time(index, 1))*PFPGA_idle_sleep; %with idle time
        index=index+1;
    end

    
 
end


