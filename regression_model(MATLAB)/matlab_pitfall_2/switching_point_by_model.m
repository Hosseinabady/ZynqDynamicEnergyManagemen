%==========================================================================
%             Practical -- real measurement
%==========================================================================
impl_index = -1;
for T=period_min:period_step:period_max

    delta = T;
    Algorithm_1;
    impl_sp = impl_empirical;
    if (impl_sp > 0 &&  impl_sp < 4)
        break;
    end
end

sp_practical = T;

for idx = 1:numel(target_period) 
    if (target_period(idx) == sp_practical)
        sp_practical_energy = target_energy(idx);
        break;
    end
end
sp_practical
sp_practical_energy

%==========================================================================
%             first model
%==========================================================================

impl_index = -1;
for T=period_min:period_step:period_max

    delta = T;
    Algorithm_1;
    impl_sp = impl_first_e_model;

    if (impl_sp > 0 &&  impl_sp < 4)
        break;
    end
end
sp_first_model = T;

for idx = 1:numel(target_period) 
    if (target_period(idx) == sp_first_model)
        sp_first_model_energy = target_energy(idx);
        break;
    end
end
sp_first_model
sp_first_model_energy



%==========================================================================
%             second model
%==========================================================================


impl_index = -1;
for T=period_min:period_step:period_max

    delta = T;
    Algorithm_1;
    impl_sp = impl_second_e_model;
    if (impl_sp > 0 &&  impl_sp < 4)
        break;
    end
end
sp_second_model = T;
for idx = 1:numel(target_period) 
    if (target_period(idx) == sp_second_model)
        sp_second_model_energy = target_energy(idx);
        break;
    end
end
sp_second_model
sp_second_model_energy

