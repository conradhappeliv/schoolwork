import numpy as np
import matplotlib.pyplot as plot


def plot_time(msg):
    plot.plot(msg.t, msg.msg)
    plot.show()


def plot_freq(msg):
    length = len(msg.msg)
    spacing = 1./msg.fs
    x = np.linspace(0, 1./(2*spacing), length/2)
    y = np.fft.fft(msg.msg)
    plot.plot(x[1:], 2.0/length * np.abs(y[0:length/2])[1:])
    plot.show()


def plot_both(msg, title=""):
    plots, axes = plot.subplots(2, 1)
    if title: plot.title(title)

    axes[0].plot(msg.t, msg.msg)
    axes[0].set_xlabel("Time")
    axes[0].set_ylabel("Amplitude")

    length = len(msg.msg)
    spacing = 1./msg.fs
    x = np.linspace(0, 1./(2*spacing), length/2)
    y = np.fft.fft(msg.msg)
    axes[1].plot(x[1:], 2.0/length * np.abs(y[0:length/2])[1:])
    axes[1].set_xlabel("Freq (Hz)")
    axes[1].set_ylabel("|Y(freq)|")

def show():
    plot.show()