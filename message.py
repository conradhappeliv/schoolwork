import pylab as pl
import numpy as np
import scipy.io.wavfile as wav
import random


# Sinusoidal message wave
def sin(sin_frequency=440):
    sample_freq = 44100
    end = 6./sin_frequency
    t = pl.arange(0., end, 1./sample_freq)
    msg = pl.sin(2*pl.pi*sin_frequency*t)
    msg = Message(sample_freq, t, msg)
    return msg


# Square message wave
def square(square_frequency=440):
    sample_freq = 44100
    end = 6./square_frequency
    t = pl.arange(0., end, 1./sample_freq)
    msg = pl.sign(pl.sin(2*pl.pi*square_frequency*t))  # sign rounds to -1 or 1
    msg = Message(sample_freq, t, msg)
    return msg


# Triangular message wave
def triangle(triangle_frequency=440):
    sample_freq = 44100
    end = 6./triangle_frequency
    t = pl.arange(0., end, 1./sample_freq)
    msg = np.zeros(len(t))

    # triangle generation
    direction = 1
    for x in range(len(t)):
        if x == 0:
            msg[x] = 0
        else:
            msg[x] = msg[x-1] + end * direction
        if msg[x] >= 1 or msg[x] <= -1:
            direction *= -1

    msg = Message(sample_freq, t, msg)
    return msg


# Pulse-train message wave
def pulse_train(pulse_freq=250):
    duty_cycle = 1./6  # Amount of time spent "on" - expects a number less than 1
    sample_freq = 44100
    end = 6./pulse_freq - 1/pulse_freq
    t = pl.arange(0., end, 1./sample_freq)
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


# Generates a pseudo-random stream of ones and zeros (kind of mimics white noise)
def PR_pulse_train():
    sample_freq = 44100
    t = pl.arange(0., .01, 1./sample_freq)
    msg = np.zeros(len(t))

    # generation
    for x in range(len(t)):
        msg[x] = round(random.random())

    msg = Message(sample_freq, t, msg)
    return msg


# Loads an audio signal from a file into a message
def voice(filename="name.wav"):
    rate, data = wav.read(filename)
    try: data = data[:, 0]
    except: pass
    msg = Message(rate, np.arange(0., len(data)/rate, 1/rate), data)
    return msg


class Message():
    def __init__(self, sample_frequency, t, msg):
        self.fs = sample_frequency
        self.t = t
        self.msg = msg

    def write(self, filename='audio.wav'):
        wav.write(filename, self.fs, self.msg)