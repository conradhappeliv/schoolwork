function [ m, t, Fs ] = Message()
    [m, Fs] = audioread('name.m4a');
    m = m(:,1)';
    t = (0:length(m)-1)/Fs;

    % SIN
    %Fs = 8000;
    %t = 0:1/Fs:1;
    %m = sin(2*pi*40*t);
    
    % SQUARE
    %Fs = 8000;
    %t = 0:1/Fs:1;
    %m = square(t*40);
    
    % PULSE TRAIN
    % D = % delay
    % W = % pulse width
    % m = pulstran(t,d,'rectpuls', W);
    

end
