

%================================================================================
%      PS Power MODEL 
%================================================================================



PS_power =((Data(:,6)-0.307544446-0.0013423));


%========================================
%      PS Power MODEL Case 1
%========================================
data_power(:,1) = Data(:,2);     %f

%           f  
T_ps_p = [% 0   0; %
            1   0; %
        ];

PS_power_model = fitlm(data_power, PS_power, T_ps_p, 'RobustOpts', 'on' );
PS_power_model
PS_power_model.Rsquared
PS_power_model_estimate = feval(PS_power_model, data_power(:,1));

