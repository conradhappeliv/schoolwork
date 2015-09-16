function [ mixed ] = Mixer(message, t)
    mixed = message .* cos(2*pi*3000*t);
end
