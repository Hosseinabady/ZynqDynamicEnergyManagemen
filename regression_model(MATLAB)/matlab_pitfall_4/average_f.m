Data=xlsread('profiling_data_X_G_U.csv');


U = Data(:,1);
F_factor = Data(:,5);
%exe_time = Data(:,7);
exe_time = estimated_time;
PL_power =(Data(:,8));
PS_power =((Data(:,9)-353.3));
MEM_power =((Data(:,12)-622.44));

%total_power = PL_power + PS_power + MEM_power;
total_power = total_power_model_estimate;
energy = total_power.*exe_time;



[n m]=size(exe_time);
i=1;
g_index = 1;
F_factor_average = [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
while (i<n+1)

    
    f_factor_index = (F_factor(i)-10)/5+1;
    F_factor_average(f_factor_index) = F_factor_average(f_factor_index) + energy(i);
    
	i=i+1;
end

F_factor_average = F_factor_average./(i/18)
