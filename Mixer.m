function [ mixed ] = Mixer(message, t)
    mixed = message .* cos(2*pi*3000*t);
    
    %not out of phase
    %m(t)*cos(wt)*cos(wt) = .5*m(t) + .5*m(t)*cos(2wt)
    
    % out of phase
    % m(t)*cos(wt)*cos(wt + delta)
    % = .5*m(t)*cos(2wt+delta) + .5*cos(delta)*m(t)
end
