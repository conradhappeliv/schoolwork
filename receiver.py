from scipy import signal
import numpy as np


def unattenuate(m):
    m.msg = np.multiply(m.msg, 10**6)
    return m


def lpf(m):
    filt = signal.firwin(numtaps=10, cutoff=2000, nyq=100000)
    m.msg = signal.lfilter(filt, 1.0, m.msg)
    return m

