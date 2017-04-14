%==========================================================================
%  Write the model in a xml file
%==========================================================================

outputFile   = 'models.xml';
outputFileID = fopen(outputFile,'w');

fprintf(outputFileID, '<?xml version="1.0"?>\n');
fprintf(outputFileID, '<models>\n');
%--------exe time model--------------------------
fprintf(outputFileID, '\t<exe_time>\n');

fprintf(outputFileID, '\t\t<a0>\n');
fprintf(outputFileID, '\t\t\t%f\n', time_model.Coefficients.Estimate(1));
fprintf(outputFileID, '\t\t</a0>\n');

fprintf(outputFileID, '\t\t<a1>\n');
fprintf(outputFileID, '\t\t\t%f\n', time_model.Coefficients.Estimate(2));
fprintf(outputFileID, '\t\t</a1>\n');

fprintf(outputFileID, '\t\t<a2>\n');
fprintf(outputFileID, '\t\t\t%f\n', time_model.Coefficients.Estimate(3));
fprintf(outputFileID, '\t\t</a2>\n');

fprintf(outputFileID, '\t</exe_time>\n');

%--------PL power model--------------------------
fprintf(outputFileID, '\t<pl_power>\n');

fprintf(outputFileID, '\t\t<a0>\n');
fprintf(outputFileID, '\t\t\t%f\n', PL_power_model.Coefficients.Estimate(1));
fprintf(outputFileID, '\t\t</a0>\n');

fprintf(outputFileID, '\t\t<a1>\n');
fprintf(outputFileID, '\t\t\t%f\n', PL_power_model.Coefficients.Estimate(2));
fprintf(outputFileID, '\t\t</a1>\n');

fprintf(outputFileID, '\t\t<a2>\n');
fprintf(outputFileID, '\t\t\t%f\n', PL_power_model.Coefficients.Estimate(3));
fprintf(outputFileID, '\t\t</a2>\n');

fprintf(outputFileID, '\t</pl_power>\n');
%--------PS power model--------------------------
fprintf(outputFileID, '\t<ps_power type = %d >\n', ps_power_type);

fprintf(outputFileID, '\t\t<a0>\n');
fprintf(outputFileID, '\t\t\t%f\n', PS_power_model.Coefficients.Estimate(1));
fprintf(outputFileID, '\t\t</a0>\n');

fprintf(outputFileID, '\t\t<a1>\n');
fprintf(outputFileID, '\t\t\t%f\n', PS_power_model.Coefficients.Estimate(2));
fprintf(outputFileID, '\t\t</a1>\n');

fprintf(outputFileID, '\t</ps_power>\n');

%--------MEM power model--------------------------
fprintf(outputFileID, '\t<mem_power type = %d >\n', mem_power_type);

fprintf(outputFileID, '\t\t<a0>\n');
fprintf(outputFileID, '\t\t\t%f\n', MEM_power_model.Coefficients.Estimate(1));
fprintf(outputFileID, '\t\t</a0>\n');

fprintf(outputFileID, '\t\t<a1>\n');
fprintf(outputFileID, '\t\t\t%f\n', MEM_power_model.Coefficients.Estimate(2));
fprintf(outputFileID, '\t\t</a1>\n');

fprintf(outputFileID, '\t</mem_power>\n');

fprintf(outputFileID, '</models>\n');