%=============t_mp========================
t_mp = target_period(1);

%=============t_sp========================

if (software_exetime(1) < software_exetime(2)) 
    if (software_exetime(1) < software_exetime(3)) 
        fastest_software_index = 1;
    else
        if (software_exetime(2) < software_exe_timeexeyime(3)) 
            fastest_software_index = 2;
        else
            fastest_software_index = 3;
        end
    end
else
    if (software_exetime(2) < software_exetime(3)) 
        fastest_software_index = 2;
    else
        fastest_software_index = 3;
    end
end



for idx = 1:numel(target_exe_time)
    target_deadline = target_period(idx)- other_tasks_exe_time;
    if (target_deadline > software_exetime(fastest_software_index))
        t_sp_index = idx;
        break;
    end
end

t_sp = target_period(idx);


%=============t_ep========================
break_outer_loop = 0;
for idx = 1:numel(target_exe_time)
    target_deadline = target_period(idx)- other_tasks_exe_time;
    
    for i=1:3
        if (software_exetime(i) < target_deadline )
            if (software_energy(i) < target_energy(idx) )
                t_sp_index = idx;
                break_outer_loop = 1;
                break;
            end
        end
    end
    if (break_outer_loop == 1)
        break;
    end
end

t_ep = target_period(idx);

%============= pe & ee ========================
pe=(t_sp-t_mp)/t_sp;
ee=(t_ep-t_mp)/t_ep;
