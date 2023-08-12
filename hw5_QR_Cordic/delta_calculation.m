%================================================================
%  Delta
%================================================================
function [constraint_met,delta_] = delta_calculation(M, M_fix,delta)
    % Checking if meets the criteria delta
    m_dif = (M-M_fix).^2;
    M = M.^2;
    delta_ = sqrt(sum(m_dif(:))) / sqrt(sum(M(:)));

    if delta_ > delta
          constraint_met = 0;
    else
       constraint_met = 1;
    end
end
