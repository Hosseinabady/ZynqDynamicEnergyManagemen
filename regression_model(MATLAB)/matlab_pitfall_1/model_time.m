%================================================================================
%      Perfromance MODEL
%================================================================================
% 1-2 Prepare data 


exe_time = Data(:,4);


data_time(:,1)= 1./Data(:,2);  %1/f



%         1/f    
T_t = [    0   0; %1/u  
           1   0; %1/u  
       ];
  
   
% 2--2 : fit linear model
time_model = fitlm(data_time, exe_time, T_t, 'RobustOpts', 'on');
estimated_time   = feval(time_model, data_time(:,1));

time_model
time_model.Rsquared
