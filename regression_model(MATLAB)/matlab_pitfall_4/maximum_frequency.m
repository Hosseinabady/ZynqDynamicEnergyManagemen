inputFiles = dir('max_freq_*.txt');


outputFile   = 'maximum_frequency.txt'; 
outputFileID = fopen(outputFile,'w'); 
fprintf(outputFileID, 'CpuUtil , SDEPCX , SDEPCG , VCCINT ,frqFct ,frqMhz ,exe time ,intPower ,pintPower ,auxPower ,pauxPower ,1v5Power');
fprintf(outputFileID, '\n');

for file_index=1:numel(inputFiles)
    %inputFileName = inputFiles{file_index};
    %inputFileName = stripped(inputFileName);

    inputFileName = inputFiles(file_index).name;
    inputFileID  = fopen(inputFileName,'r'); 
    data_valid = 0;

    while ~feof(inputFileID)
        
        tline = fgetl(inputFileID);
        read_all_data_for_one_frequency = 0;
        
        
        
        if (strfind(tline, 'VCCINT voltage')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);
            [token_4, remain] = strtok(remain);
            VCCINT_voltage = token_4; 
        end

        if (strfind(tline, 'CPUutil')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);

            CPUUTIL = token_3; 
        end

        if (strfind(tline, 'SDEPCX')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);

            SDEPCX = token_3; 
        end

        if (strfind(tline, 'SDEPCG')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);

            SDEPCG = token_3; 
        end

        if (strfind(tline, 'frequency factor')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);
            [token_4, remain] = strtok(remain);

            PL_frequency_factor = token_4; 
        end

        if (strfind(tline, 'vccint_voltage_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCINT_VOLTAGE_AVERAGE = token_3; 
        end

        if (strfind(tline, 'vccint_current_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCINT_CURRENT_AVERAGE = token_3; 
        end

        if (strfind(tline, 'vccint_power_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCINT_POWER_AVERAGE = token_3; 
        end

        if (strfind(tline, 'vccpint_voltage_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCPINT_VOLTAGE_AVERAGE = token_3; 
        end

        if (strfind(tline, 'vccpint_current_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCPINT_CURRENT_AVERAGE = token_3; 
        end

        if (strfind(tline, 'vccpint_power_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCPINT_POWER_AVERAGE = token_3; 
        end

        if (strfind(tline, 'vccaux_voltage_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCAUX_VOLTAGE_AVERAGE = token_3; 
        end    

        if (strfind(tline, 'vccaux_current_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCAUX_CURRENT_AVERAGE = token_3; 
        end 

        if (strfind(tline, 'vccaux_power_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCAUX_POWER_AVERAGE = token_3; 
        end  

        if (strfind(tline, 'vccpaux_voltage_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCPAUX_VOLTAGE_AVERAGE = token_3; 
        end     

        if (strfind(tline, 'vccpaux_current_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCPAUX_CURRENT_AVERAGE = token_3; 
        end  

        if (strfind(tline, 'vccpaux_power_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCCPAUX_POWER_AVERAGE = token_3; 
        end

        if (strfind(tline, 'vcc1v5_voltage_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCC1V5_VOLTAGE_AVERAGE = token_3; 
        end

        if (strfind(tline, 'vcc1v5_current_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCC1V5_CURRENT_AVERAGE = token_3; 
        end    

        if (strfind(tline, 'vcc1v5_power_average')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);


            VCC1V5_POWER_AVERAGE = token_3; 
        end    

        if (strfind(tline, 'hardware execution time')) 
            [token_1, remain] = strtok(tline, ' = ');
            [token_2, remain] = strtok(remain);
            [token_3, remain] = strtok(remain);
            [token_4, remain] = strtok(remain);

            EXE_TIME = token_4; 
            read_all_data_for_one_frequency = 1;
        end    

        if (strfind(tline, 'Validation PASSED!')) 
            data_valid = 1;
        end
        if (read_all_data_for_one_frequency == 1) && (data_valid == 1)
            fprintf(outputFileID, CPUUTIL); 
            fprintf(outputFileID, ', '); 

            fprintf(outputFileID, SDEPCX); 
            fprintf(outputFileID, ', ');

            fprintf(outputFileID, SDEPCG); 
            fprintf(outputFileID, ', ');

            fprintf(outputFileID, VCCINT_voltage); 
            fprintf(outputFileID, ', ');

            fprintf(outputFileID, PL_frequency_factor); 
            fprintf(outputFileID, ', ');

            fprintf(outputFileID, '%f', 1000/str2double(PL_frequency_factor)); 
            fprintf(outputFileID, ', ');

            fprintf(outputFileID, EXE_TIME); 
            fprintf(outputFileID, ', ');

            fprintf(outputFileID, VCCINT_POWER_AVERAGE); 
            fprintf(outputFileID, ', ');

            fprintf(outputFileID, VCCPINT_POWER_AVERAGE); 
            fprintf(outputFileID, ', ');        

            fprintf(outputFileID, VCCAUX_POWER_AVERAGE); 
            fprintf(outputFileID, ', ');        


            fprintf(outputFileID, VCCPAUX_POWER_AVERAGE); 
            fprintf(outputFileID, ', ');        

            fprintf(outputFileID, VCC1V5_POWER_AVERAGE); 
            fprintf(outputFileID, ', ');                

            fprintf(outputFileID, '\n');
            data_valid = 0;
        end

    end
    fclose(inputFileID);
end
fclose(outputFileID);
    
    

    
    
    
   