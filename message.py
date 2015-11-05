import pylab as pl
import numpy as np
import scipy.io.wavfile as wav
import random


def sin():
    sin_frequency = 400
    sample_freq = 8000
    t = pl.arange(0., 1., 1./sample_freq)
    msg = pl.sin(2*pl.pi*sin_frequency*t)
    msg = Message(sample_freq, t, msg)
    return msg


def square():
    square_frequency = 40
    sample_freq = 8000
    t = pl.arange(0., 1., 1./sample_freq)
    msg = pl.sign(pl.sin(2*pl.pi*square_frequency*t))  # sign rounds to -1 or 1
    msg = Message(sample_freq, t, msg)
    return msg


def triangle():
    triangle_frequency = 250
    sample_freq = 8000
    t = pl.arange(0., 1., 1./sample_freq)
    msg = np.zeros(len(t))

    # triangle generation
    direction = 1
    for x in range(len(t)):
        if x == 0:
            msg[x] = 0
        else:
            msg[x] = msg[x-1] + 1/triangle_frequency * direction
        if msg[x] >= 1 or msg[x] <= -1:
            direction *= -1

    msg = Message(sample_freq, t, msg)
    return msg


def pulse_train():
    duty_cycle = 1./6  # expects a number less than 1
    pulse_freq = 250
    sample_freq = 8000
    t = pl.arange(0., 1., 1./sample_freq)
    msg = np.zeros(len(t))

    # generation
    for x in range(len(t)):
        new_x = x % pulse_freq
        if new_x < duty_cycle*pulse_freq:
            msg[x] = 1
        else:
            msg[x] = 0

    msg = Message(sample_freq, t, msg)
    return msg


def PR_pulse_train():
    sample_freq = 300
    t = pl.arange(0., 1., 1./sample_freq)
    msg = np.zeros(len(t))

    # generation
    for x in range(len(t)):
        msg[x] = round(random.random())

    msg = Message(sample_freq, t, msg)
    return msg


def voice():
    rate, data = wav.read('name.wav')
    data = data[:, 0]
    msg = Message(rate, np.arange(0., len(data)/rate, 1/rate), data)
    return msg


class Message():
    def __init__(self, sample_frequency, t, msg):
        self.fs = sample_frequency
        self.t = t
        self.msg = msg

    def write(self, filename='audio.wav'):
        wav.write(filename, self.fs, self.msg)