%Spet 1 : Prepare data 
% 1-1 Import data 
Data=xlsread('profiling_data_X_G_U.csv');

exe_time_limit = 158100000;
%================================================================================
%      Perfromance MODEL
%================================================================================
% 1-2 Prepare data 
Data_time=Data;
[n m]=size(Data_time(:,7));
i=1;
while (i<n+1)
	deleted_line=0; 

	if (Data_time(i,7) > exe_time_limit)
        Data_time(i,:)=[];
    end
	
	i=i-deleted_line+1;
	[n m]=size(Data_time(:,7));
end
Data_time(:,12)=[];
Data_time(:,11)=[];
Data_time(:,10)=[];
Data_time(:,9)=[];
Data_time(:,8)=[];
Data_time(:,5)=[];
Data_time(:,4)=[];

exe_time = Data_time(:,5);
Data_time(:,1)=Data_time(:,1)/100; %cpu utilization
Data_time(:,1)=1./Data_time(:,1);  %1/cpuU
Data_time(:,2)=1./Data_time(:,2);  %1/X
Data_time(:,3)=1./Data_time(:,3);  %1/G
Data_time(:,4)=1./Data_time(:,4);  %1/f


%Spet 2 : Create fited model
% 2-1 :Terms Matrix
%       1/u  1/x  1/g  1/f    
T_t = [  1    0    0    0   0; %1/u  
         1    1    0    1   0; %1/uxf
         1    1    1    1   0  %1/xgf
       ];
  
   
% 2--2 : fit linear model
time_model = fitlm(Data_time, exe_time, T_t, 'RobustOpts', 'on');

estimated_time   = feval(time_model, Data_time(:,1), Data_time(:,2), Data_time(:,3), Data_time(:,4));

time_model
time_model.Rsquared

%================================================================================
%      PL Power MODEL
%================================================================================
Data_power=Data;
Total_power=Data_power(:,8)+(Data_power(:,9)-353.3)+(Data_power(:,12)-622.44);

[n m]=size(Data_power(:,7));
i=1;
while (i<n+1)
	deleted_line=0; 

	if (Data_power(i,7) > exe_time_limit)
        Data_power(i,:)=[];
    end
	
	i=i-deleted_line+1;
	[n m]=size(Data_power(:,7));
end



PL_power =(Data_power(:,8));

Data_power(:,12)=[];
Data_power(:,11)=[];
Data_power(:,10)=[];
Data_power(:,9)=[];
Data_power(:,8)=[];
Data_power(:,7)=[];

Data_power(:,5)=[];



Data_power(:,1) = (Data_power(:,1)/100); %U: cpu utilization
Data_power(:,2) = Data_power(:,2);     %X
Data_power(:,3) = Data_power(:,3);     %G
Data_power(:,4) = Data_power(:,4);     %V
Data_power(:,5) = Data_power(:,5);     %f


%        U   X  G  V   f  
T_e = [  0   0  0  1   0   0; %
         0   1  0  2   1   0; %
         0   1  1  2   1   0  %
       ];

PL_power_model = fitlm(Data_power, PL_power, T_e, 'RobustOpts', 'on' );
PL_power_model
PL_power_model.Rsquared
PL_power_model_estimate = feval(PL_power_model, Data_power(:,2), Data_power(:,3), Data_power(:,4), Data_power(:,5));
%================================================================================
%      PS Power MODEL
%================================================================================
Data_power=Data;
[n m]=size(Data_power(:,7));
i=1;
while (i<n+1)
	deleted_line=0; 

	if (Data_power(i,7) > exe_time_limit)
        Data_power(i,:)=[];
    end
	
	i=i-deleted_line+1;
	[n m]=size(Data_power(:,7));
end

PS_power =((Data_power(:,9)-353.3));

Data_power(:,12)=[];
Data_power(:,11)=[];
Data_power(:,10)=[];
Data_power(:,9)=[];
Data_power(:,8)=[];
Data_power(:,7)=[];

Data_power(:,5)=[];



Data_power(:,1) = 1./(Data_power(:,1)/100); %1/U: cpu utilization
Data_power(:,2) = 1./Data_power(:,2);     %1/X
Data_power(:,3) = 1./Data_power(:,3);     %1/G
Data_power(:,4) = 1./Data_power(:,4);     %1/V
Data_power(:,5) = 1./Data_power(:,5);     %1/f

PS_power_rev=1./PS_power;
%           1/U   1/X   1/G   1/V   1/f  
T_ps_p = [  1      0     0     0     0   0; %
%            0      0     0     0     1   0; %
%            0      0     1     0     0   0; %
%            0      1     0     0     0   0; %
            0      1     1     0     1   0; %
         ];

PS_power_model = fitlm(Data_power, PS_power_rev, T_ps_p, 'RobustOpts', 'on' );
PS_power_model
PS_power_model.Rsquared
PS_power_model_estimate_rev = feval(PS_power_model, Data_power(:,1), Data_power(:,2), Data_power(:,3), Data_power(:,5));
PS_power_model_estimate = 1./PS_power_model_estimate_rev;

%================================================================================
%      MEM Power MODEL
%================================================================================
Data_power=Data;
[n m]=size(Data_power(:,7));
i=1;
while (i<n+1)
	deleted_line=0; 

	if (Data_power(i,7) > exe_time_limit)
        Data_power(i,:)=[];
    end
	
	i=i-deleted_line+1;
	[n m]=size(Data_power(:,7));
end

MEM_power =((Data_power(:,12)-622.44));

Data_power(:,12)=[];
Data_power(:,11)=[];
Data_power(:,10)=[];
Data_power(:,9)=[];
Data_power(:,8)=[];
Data_power(:,7)=[];

Data_power(:,5)=[];



Data_power(:,1) = 1./(Data_power(:,1)/100); %1/U: cpu utilization
Data_power(:,2) = Data_power(:,2);     %X
Data_power(:,3) = Data_power(:,3);     %G
Data_power(:,4) = Data_power(:,4);     %V
Data_power(:,5) = Data_power(:,5);     %f




%          1/U   X  G  V   f  
T_mem_p = [ 1    0  0  0   0   0; %
            0    1  0  0   1   0; %
         ];

MEM_power_model = fitlm(Data_power, MEM_power, T_mem_p, 'RobustOpts', 'on' );
MEM_power_model
MEM_power_model.Rsquared
MEM_power_model_estimate = feval(MEM_power_model, Data_power(:,1), Data_power(:,2), Data_power(:,5));

total_power_model_estimate = PL_power_model_estimate + PS_power_model_estimate + MEM_power_model_estimate;
