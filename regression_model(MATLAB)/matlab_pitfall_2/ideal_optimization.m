u = 80;
exe_time_max = 800;

Data=xlsread('profiling_data_X_G_U.csv');


U = Data(:,1);
X = Data(:, 2);
G = Data(:, 3);
V = Data(:, 4);
f_fact= Data(:, 5);

exe_time = Data(:,7);
PL_power =(Data(:,8));
PS_power =((Data(:,9)-353.3));
MEM_power =((Data(:,12)-622.44));

total_power = PL_power + PS_power + MEM_power;

energy = total_power.*exe_time;

%[object_function, index] = max(energy.*exe_time.*exe_time);
[object_function, index] = max(energy);




[n m]=size(exe_time);
i=1;
while (i<n+1)
	
	if (exe_time(i) < exe_time_max)
        if (U(i) == u) 
            if (( V(i) == 1) &&  (f_fact(i) == 10))
                if (energy(i) < object_function)  
                    %object_function = energy(i).*exe_time(i).*exe_time(i);
                    object_function = energy(i);
                    index = i;
                end
           end
        end
    end
	i=i+1;
end

U_gold_group = Data(index, 1)
X_gold_group = Data(index, 2)
G_gold_group = Data(index, 3)
V_gold_group = Data(index, 4)
f_fact_gold_group = Data(index, 5)





[n m]=size(exe_time);
i=1;
while (i<n+1)
	
	if (exe_time(i) < exe_time_max)
        if (U(i) == u) 
             if (energy(i) < object_function)  
                  object_function = energy(i).*exe_time(i).*exe_time(i);
                  %object_function = energy(i);
                  index = i;
             end
        end
    end
	i=i+1;
end

U_gold = Data(index, 1)
X_gold = Data(index, 2)
G_gold = Data(index, 3)
V_gold = Data(index, 4)
f_fact_gold = Data(index, 5)
