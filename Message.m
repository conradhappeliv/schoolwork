function [ message ] = Message(t)
    message = sin(2*pi*40*t);
    %x = sin(2*pi*40*t) .* sin(2*pi*80*t) .* sin(2*pi*440*t) .* sin(2*pi*880*t) .* sin(2*pi*4000*t);
    %x = square(t*40);
    %x = sin(40*t) .* cos(60*t);
end
