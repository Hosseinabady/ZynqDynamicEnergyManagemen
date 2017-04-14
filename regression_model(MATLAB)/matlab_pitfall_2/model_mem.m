

%================================================================================
%      PS Power MODEL 
%================================================================================


[m,n] = size(Data(:,9));
MEM_power = zeros(m, 1);

MEM_power_rev =MEM_power;

data_power(:,1) = Data(:,2);     %f

%            f  
T_ps_p = [ %   0   0;
              1   0
         ];


MEM_power_model = fitlm(data_power, MEM_power, T_ps_p, 'RobustOpts', 'on' );
MEM_power_model
MEM_power_model.Rsquared
MEM_power_model_estimate = feval(MEM_power_model, data_power(:,1));