function [extracted] = Receiver(message, t)
    %windowSize = round(SampleFreq/150);
    windowSize = 150;
    extracted = message ./ cos(2*pi*3000*t);
    %extracted = filter((1/windowSize)*ones(1,windowSize), 1, extracted);
end
