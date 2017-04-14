Data=xlsread('profiling_data_X_G_U.csv');


U = Data(:,1);
V = Data(:,4);
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
V_average = [ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
while (i<n+1)
	if (G(i)==1)
        G_average(1) = G_average(1) + energy(i);
    end
    
	v_index = V(i)*100-85+1;
    V_average(v_index) = V_average(v_index) + energy(i);
    
	i=i+1;
end

V_average = V_average./(i/16)
