import numpy as np
import scipy.signal as signal

carrier_freq = 10000


# Modulates a message signal by a carrier sin wave
def modulate(m):
    m.msg *= np.sin(2*np.pi*carrier_freq*m.t)
    return m


# Given two message signals, combines them into a single carrier signal by modulating each by orthogonal carrier signals
def AMQAM(m1, m2):
    m1.msg = np.multiply(m1.msg, 1./np.abs(m1.msg).max())
    m2.msg = np.multiply(m2.msg, 1./np.abs(m2.msg).max())
    # Make the lengths equal
    if len(m1.msg) != len(m2.msg) or m1.fs != m2.fs:
        if m1.fs != m2.fs:
            if m1.fs > m2.fs:
                total_samps = len(m2.msg)/m2.fs*m1.fs
                m2.msg, m2.t = signal.resample(m2.msg, total_samps, m2.t)
                m2.orig_len = len(m2.t)
                m2.fs = m1.fs
            else:
                total_samps = len(m1.msg)/m1.fs*m2.fs
                m1.msg, m1.t = signal.resample(m1.msg, total_samps, m1.t)
                m2.orig_len = len(m2.t)
                m1.fs = m2.fs

        if len(m1.msg) != len(m2.msg):
            new_len = max(len(m1.msg), len(m2.msg))
            shape = np.zeros(new_len).shape
            if len(m1.msg) > len(m2.msg):
                oldmsg = m2.msg
                m2.msg = np.zeros(shape[0])
                m2.msg[:len(oldmsg)] += oldmsg
                m2.t = m1.t
            else:
                oldmsg = m1.msg
                m1.msg = np.zeros(shape[0])
                m1.msg[:len(oldmsg)] += oldmsg
                m1.t = m2.t

    m1 = modulate(m1)
    # Modulate the second signal and add it to the resulting signal
    m1.msg += m2.msg*np.cos(2*np.pi*carrier_freq*m2.t)
    m1.orig_len2 = m2.orig_len
    return m1
