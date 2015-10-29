import numpy as np
import random


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