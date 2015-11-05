import numpy as np
import random


def gauss_noise(m, SNR=10):
    for i in range(len(m.msg)):
        max_amp = 1./SNR*m.msg[i]
        noise = random.uniform(0, max_amp) - max_amp/2
        m.msg[i] += noise
    return m


def attenuation(m):
    m.msg = np.multiply(m.msg, 10**-6)
    return m


def fading(m):
    str1 = random.uniform(.5, 1.)
    str2 = random.uniform(0., 1.-str1)
    str3 = 1. - str1 - str2
    delay2 = random.randint(1, m.fs)
    delay3 = random.randint(1, m.fs)
    for i in range(len(m.msg)):
        m.msg[i] = m.msg[i] * str1
        if i-delay2 > 0:
            m.msg[i] += m.msg[i-delay2]*str2
        if i-delay3 > 0:
            m.msg[i] += m.msg[i-delay3]*str3
    return m