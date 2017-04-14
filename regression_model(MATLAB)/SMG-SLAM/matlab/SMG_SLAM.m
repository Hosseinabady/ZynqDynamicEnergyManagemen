

inputFileName   = 'log_power_monitor_overhead_Thu_Mar__9_22_51_48_2017_Hardware_X_new_07.txt';
outputFile   = 'profiling_data_X_G_U.csv'; 
outputFileID = fopen(outputFile,'w'); 

inputFileID  = fopen(inputFileName,'r'); 

fprintf(outputFileID, 'vccint_voltage_average, vccint_current_average , vccint_power_average , vccpint_voltage_average , vccpint_current_average , vccpint_power_average , vccaux_voltage_average , vccaux_current_average , vccaux_power_average , vccpaux_voltage_average , vccpaux_current_average , vccpaux_power_average , vcc1v5_voltage_average , vcc1v5_current_average , vcc1v5_power_average  ');
fprintf(outputFileID, '\n');

while ~feof(inputFileID)
    tline = fgetl(inputFileID);
    if (strfind(tline, 'vccint_voltage_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end

	if (strfind(tline, 'vccint_current_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end

 	if (strfind(tline, 'vccint_power_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end 
    
	if (strfind(tline, 'vccpint_voltage_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end
    
  	if (strfind(tline, 'vccpint_current_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end
    
	if (strfind(tline, 'vccpint_power_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end  
    
 
    
	if (strfind(tline, 'vccaux_voltage_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end    
    
	if (strfind(tline, 'vccaux_current_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end     
    
 	if (strfind(tline, 'vccaux_power_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end   
    

    
 	if (strfind(tline, 'vccpaux_voltage_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end      
    
  	if (strfind(tline, 'vccpaux_current_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end    
    
       
 	if (strfind(tline, 'vccpaux_power_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end  
    

    if (strfind(tline, 'vcc1v5_voltage_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end  

    if (strfind(tline, 'vcc1v5_current_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, ', ');
    end  
        
    
    
	if (strfind(tline, 'vcc1v5_power_average')) 
        [token_1, remain] = strtok(tline, ' = ');
        [token_2, remain] = strtok(remain);
        [token_3, remain] = strtok(remain);
        [token_4, remain] = strtok(remain);
        fprintf(outputFileID, token_3);
        fprintf(outputFileID, '\n');
    end
    
    
end
fclose(outputFileID);
    
    

fclose(inputFileID);
    
    
   