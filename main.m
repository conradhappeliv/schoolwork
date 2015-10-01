[x, t, Fs] = Message();

% PLOT "BEFORE"
figure(1);
plot(t, x);
figure(2);
PlotFreq(Fs, x);

x = Mixer(x, t);
x = Channel(x);
x = Receiver(x, t);

% PLOT "AFTER"
figure(3);
plot(t, x);
figure(4);
PlotFreq(Fs, x);
