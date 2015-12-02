import numpy as np
import matplotlib.pyplot as plot
from scipy import signal


def main():
    # play with these values
    cutoff = 9000
    norm_pass = cutoff/(44100/2)
    (N, Wn) = signal.buttord(wp=norm_pass, ws=1.5*norm_pass, gpass=2, gstop=50, analog=0)
    (b, a) = signal.butter(N, Wn, btype='lowpass', analog=0, output='ba')
    print("b="+str(b)+", a="+str(a))


    w, h = signal.freqz(b, a)
    plot.figure()
    plot.title("Digital Filter Frequency Response")
    plot.plot(w/np.pi*44100, 20 * np.log10(abs(h)))
    plot.show()


if __name__ == "__main__":
    main()