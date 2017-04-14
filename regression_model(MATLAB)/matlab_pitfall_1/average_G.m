Data=xlsread('profiling_data_X_G_U.csv');


U = Data(:,1);
G = Data(:,3);
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
G_average=[0  0 0 0];

while (i<n+1)
	
    if (G(i)==1)
        G_average(1) = G_average(1) + energy(i);
    end
    
	if (G(i)==4)
        G_average(2) = G_average(2) + energy(i);
    end
    
	if (G(i)==8)
        G_average(3) = G_average(3) + energy(i);
    end
    
   	if (G(i)==10)
        G_average(4) = G_average(4) + energy(i);
    end
    
	i=i+1;
end

G_average = G_average./(i/4)


