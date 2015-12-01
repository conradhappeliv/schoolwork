import numpy as np
import matplotlib.pyplot as plot
from scipy import signal


def main():
    # play with these values
    filt = signal.firwin(numtaps=10000, cutoff=4000, nyq=44100)

    w, h = signal.freqz(filt)
    plot.figure()
    plot.title("Digital Filter Frequency Response")
    plot.plot(w/np.pi*44100, 20 * np.log10(abs(h)))
    plot.show()


if __name__ == "__main__":
    main()