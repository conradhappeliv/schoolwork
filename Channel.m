function [ muddled ] = Channel( message )
    muddled = message;
    
    % Attenuation
    muddled = muddled*10^-6;
end
