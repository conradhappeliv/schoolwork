from pylab import *

def sine():
    sample_freq = 8000
    sin_frequency = 40
    t = arange(0., 1., 1./sample_freq)
    msg = sin(2*pi*sin_frequency*t)
    msg = Message(sample_freq, t, msg)
    return msg

def square():
    pass

def pulse_train():
    pass

def voice():
    pass

class Message():
    def __init__(self, sample_frequency, t, msg):
        self.fs = sample_frequency
        self.t = t
        self.msg = msg