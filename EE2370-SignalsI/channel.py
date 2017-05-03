import numpy as np
import random


# Adds a varying level of noise to a signal according to the SNR (signal-to-noise ratio, in DBs) parameter
def gauss_noise(m, SNR=10):
    for i in range(len(m.msg)):
        max_amp = 1./SNR*m.msg[i]  # the maximum amount of noise*2 for the current amplitude level
        noise = random.uniform(0, max_amp) - max_amp/2  # random positive or negative noise
        m.msg[i] += noise
    return m


# Mimics the heavy decrease in signal strength
# This would be caused by a large distance between sender and receiver or other channel issues
def attenuation(m):
    m.msg = np.multiply(m.msg, 10**-6)
    return m


# Mimics an "echo" caused by signals bouncing off of obstacles
def fading(m):
    str1 = random.uniform(.5, 1.)  # strength of original signal
    str2 = random.uniform(0., 1.-str1)  # strength for first echo
    str3 = 1. - str1 - str2  # strength of second echo (original signal + echo1 + echo2 must equal 1)
    delay2 = random.randint(1, m.fs)  # delay of first echo
    delay3 = random.randint(1, m.fs)  # delay of second echo
    for i in range(len(m.msg)):
        m.msg[i] = m.msg[i] * str1
        if i-delay2 > 0:
            m.msg[i] += m.msg[i-delay2]*str2
        if i-delay3 > 0:
            m.msg[i] += m.msg[i-delay3]*str3
    return m