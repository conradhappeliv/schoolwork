function [] = PlotFreq( sample_freq, x )
    FreqX = fftshift(fft(x));
    FreqX = abs(FreqX);
    if(length(x) > sample_freq)
        endofsamp = 1;
        while(endofsamp < length(x)-1)
            beginofsamp = endofsamp;
            endofsamp = endofsamp + min(length(x)-endofsamp, sample_freq)-1;
            fragment = FreqX(beginofsamp:endofsamp);
            df = -length(fragment)/2:1:length(fragment)/2;
            df = df(1:length(df)-1);
            figure();
            plot(df, fragment);
            title(strcat(num2str(beginofsamp),' to  ',num2str(endofsamp)));
        end
    else
        df = -sample_freq/2:1:sample_freq/2;
        plot(df, FreqX);
    end
end
