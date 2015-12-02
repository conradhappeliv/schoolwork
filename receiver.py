from message import Message
from mixer import carrier_freq
from scipy import signal
import numpy as np


# Returns both signals that were modulated orthogonally in a single carrier signal
def demuxAMQAM(m):
    m1 = Message(m.fs, m.t, 2 * m.msg * np.sin(2*np.pi*carrier_freq*m.t))
    m2 = Message(m.fs, m.t, 2 * m.msg * np.cos(2*np.pi*carrier_freq*m.t))
    return m1, m2


# Amplifies the signal by a scale of 10^6
def unattenuate(m):
    m.msg = np.multiply(m.msg, 10**6)
    return m


# Applies a low-pass filter to the signal to filter out high frequencies
def lpf(m):
    cutoff = 9000
    norm_pass = cutoff/(m.fs/2)
    (N, Wn) = signal.buttord(wp=norm_pass, ws=1.5*norm_pass, gpass=2, gstop=50, analog=0)
    (b, a) = signal.butter(N, Wn, btype='lowpass', analog=0, output='ba')
    m.msg = signal.lfilter(b, a, m.msg)
    return m

