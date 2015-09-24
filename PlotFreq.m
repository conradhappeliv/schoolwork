function [] = PlotFreq( sample_freq, x )
    FreqX = fftshift(fft(x));
    FreqX = abs(FreqX);
    df = -sample_freq/2:1:sample_freq/2;
    plot(df, FreqX);
end
