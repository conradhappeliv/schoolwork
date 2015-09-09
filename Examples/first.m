Fs = 150;
t = 0:1/Fs:1;
f = 5;
x = sin(2*pi*f*t);
X = fftshift(fft(x));

X_mag = abs(X);

df = -Fs/2:1:Fs/2;

figure(1);
plot(t,x);
title('Sine Wave Signal');
xlabel('Time (s)');
ylabel('Amplitude');
figure(2);
plot(df,X_mag);
title('Spectrum of a Sine Wave');
xlabel('Frequency (Hz) ');
ylabel('Amplitude');


