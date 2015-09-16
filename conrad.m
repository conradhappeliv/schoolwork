SampleFreq = 8000;
t = 0:1/SampleFreq:1;

x = Message(t);

% PLOT "BEFORE"
figure(1);
plot(t, x);
figure(2);
PlotFreq(SampleFreq, x);

x = Mixer(x, t);
x = Channel(x);
x = Receiver(x, t);

% PLOT "AFTER"
figure(3);
plot(t, x);
figure(4);
PlotFreq(SampleFreq, x);
