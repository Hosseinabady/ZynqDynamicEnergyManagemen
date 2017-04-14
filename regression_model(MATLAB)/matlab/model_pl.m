
%================================================================================
%      PL Power MODEL
%================================================================================

PL_power =(Data(:,5));




data_power(:,1) = Data(:,2);     %f
data_power(:,2) = Data(:,3);     %V

%            f   V
PL_e = [ 
             1  2  0; %
             0  1  0  %
       ];

PL_power_model = fitlm(data_power, PL_power, PL_e, 'RobustOpts', 'on' );
PL_power_model
PL_power_model.Rsquared
PL_power_model_estimate = feval(PL_power_model, data_power(:,1), data_power(:,2));