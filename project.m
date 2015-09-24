%SampleFreq = 8000;
%t = 0:1/SampleFreq:1;

x = Message();


figure(1);
plot(t, x);
figure(2);
PlotFreq(SampleFreq, x);

x = Mixer(x, t);


x = Channel(x);

figure(3);
PlotFreq(SampleFreq, x);

x = Receiver(x, t);


figure(4);
plot(t, x);
figure(5);
PlotFreq(SampleFreq, x);









