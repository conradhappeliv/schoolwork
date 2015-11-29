from message import Message
from mixer import carrier_freq
from scipy import signal
import numpy as np


def demuxAMQAM(m):
    m1 = Message(m.fs, m.t, 2 * m.msg * np.sin(2*np.pi*carrier_freq*m.t))
    m2 = Message(m.fs, m.t, 2 * m.msg * np.cos(2*np.pi*carrier_freq*m.t))
    return m1, m2


def unattenuate(m):
    m.msg = np.multiply(m.msg, 10**6)
    return m


def lpf(m):
    filt = signal.firwin(numtaps=100, cutoff=4000, nyq=100000)
    m.msg = signal.lfilter(filt, 1.0, m.msg)
    return m

