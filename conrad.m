SampleFreq = 8000;
t = 0:1/SampleFreq:1;

% MESSAGE
x = sin(2*pi*40*t);
%x = sin(2*pi*40*t) .* sin(2*pi*80*t) .* sin(2*pi*440*t) .* sin(2*pi*880*t) .* sin(2*pi*4000*t);
%x = square(t*40);
%x = sin(40*t) .* cos(60*t);

% PLOT "BEFORE"
figure(1);
plot(t, x);
figure(2);
PlotFreq(SampleFreq, x);

% MIXER
x = x .* cos(2*pi*3000*t);

% CHANNEL
for i=1:size(x),
   x(i) = x(i) +(-1 + (1+1)*rand(1));
end

% RECEIVER
windowSize = round(SampleFreq/150);
x = x ./ cos(2*pi*3000*t);
x = filter((1/windowSize)*ones(1,windowSize), 1, x);

% PLOT "AFTER"
figure(3);
plot(t, x);
figure(4);
PlotFreq(SampleFreq, x);
