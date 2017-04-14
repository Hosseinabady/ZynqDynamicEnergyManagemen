

%================================================================================
%      PS Power MODEL 
%================================================================================
Data=xlsread('profiling_data_X_G_U.csv');

Data_power=Data;

MEM_power =((Data_power(:,12)-622.44));

Data_power(:,12)=[];
Data_power(:,11)=[];
Data_power(:,10)=[];
Data_power(:,9)=[];
Data_power(:,8)=[];
Data_power(:,7)=[];

Data_power(:,5)=[];

%========================================
%      PS Power MODEL Case 2
%========================================
%Case 1 a+b.(fGX)/U
Data_power_Case_2(:,1) = 1./(Data_power(:,1)/100);    %U: cpu utilization
Data_power_Case_2(:,2) =    Data_power(:,2);        %X
Data_power_Case_2(:,3) =    Data_power(:,3);        %G
Data_power_Case_2(:,4) =    Data_power(:,5);        %f

%                 1/U     X     G     f  
T_ps_p_Case_2 = [   0      0     0     0   0; % a
                    1      1     1     1   0; % 
                    0      1     1     1   0
                ];

MEM_power_model_Case_2 = fitlm(Data_power_Case_2, MEM_power, T_ps_p_Case_2, 'RobustOpts', 'on' );
%MEM_power_model_estimate_Case_2 = feval(MEM_power_model_Case_2, Data_power_Case_2(:,1), Data_power_Case_2(:,2), Data_power_Case_2(:,3), Data_power_Case_2(:,4));
MEM_power_model_Case_2