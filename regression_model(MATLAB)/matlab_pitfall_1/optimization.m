

u = 80;
exe_time_max = 500;

Data=xlsread('profiling_data_X_G_U.csv');



U = Data(:,1);
X = Data(:, 2);
G = Data(:, 3);
V = Data(:, 4);
f_fact= Data(:, 5);


estimated_energy = total_power_model_estimate.*estimated_time;
object_function = estimated_energy.*estimated_time.*estimated_time;
[object_function_estimated, index] = max(object_function);

[n m]=size(exe_time);
i=1;
while (i<n+1)

    %if (estimated_time(i) < exe_time_max)
        if (U(i) == u) 
            if (( V(i) == 1) &&  (f_fact(i) == 10))
                    object_function = estimated_energy(i).*estimated_time(i).*estimated_time(i);
                    %object_function = estimated_energy(i);
                if (object_function < object_function_estimated)  
                    object_function_estimated = object_function;
                    index = i;
                end
                if((X(i) == 1) && (G(i) == 6) )
                    energy_1_6 = estimated_energy(i)
                end
           end
        %end
    end
	i=i+1;
end
object_function_estimated
U_opt_group = Data(index, 1)
X_opt_group = Data(index, 2)
G_opt_group = Data(index, 3)
V_opt_group = Data(index, 4)
f_fact_opt_group = Data(index, 5)
