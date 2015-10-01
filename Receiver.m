function [extracted] = Receiver(message, t)
    %anti-attenuation
    message = message*10^6;
    
    extracted = message .* cos(2*pi*3000*t);
    df = designfilt('lowpassfir','PassbandFrequency',1500,...
                'StopbandFrequency',1900,'PassbandRipple',1,...
                'StopbandAttenuation',95,'SampleRate',8000);
    extracted = filter(df, extracted);
end
