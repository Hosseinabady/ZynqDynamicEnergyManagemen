
%================================================================================
%      Voltage Frequenct MODEL
%================================================================================

voltage   =(Data(:,3));
frequency =(Data(:,2));


[ m, dummy] = size(voltage);


frequencies = [200	166.666667	142.857143	125	111.111111	100, 90.909091, 83.333333, 76.923077	71.428571	66.666667	62.5	58.823529	55.555556	52.631579	50	47.619048	45.454545	43.478261	41.666667	40	38.461538	37.037037	35.714286	34.482759	33.333333	32.258065	31.25	30.30303	29.411765	28.571429	27.777778	27.027027	26.315789	25.641026	25	24.390244	23.809524	23.255814	22.727273	22.222222	21.73913	21.276596	20.833333	20.408163];
[dummy, no_frequencies] = size(frequencies);

k = 1;
v_tmp = 2;
for f = 1:no_frequencies
    for i = 1 : m
        if (frequency(i, 1) ==  frequencies(f))
            %f_min(k, 1) = frequencies(f);
            %v_min(k, 1) = 1;
            f_tmp = frequencies(f);
     
            for i = 1 : m
                if (frequency(i, 1) ==  f_tmp)
                    if (v_tmp > voltage(i, 1)) 
                         v_tmp = voltage(i, 1);
                    end
                end
            end
            if (k > 2)
                if (v_tmp <  v_min(k-1, 1))
                    v_min(k, 1) = v_tmp;
                    f_min(k, 1) = frequencies(f);
                    k=k+1;
                end
            else
                v_min(k, 1) = v_tmp;
                f_min(k, 1) = frequencies(f);
                k=k+1;
            end
            break;
        end
    end
end



 %                    f  
freq_voltage_e = [ 
                     0    0; %
                     1    0  %
                  ];

freq_voltage_model = fitlm(f_min, v_min, freq_voltage_e, 'RobustOpts', 'on' );
freq_voltage_model
freq_voltage_model.Rsquared
freq_voltage_model_estimate = feval(freq_voltage_model, f_min);