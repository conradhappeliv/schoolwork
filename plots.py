import numpy as np
import matplotlib.pyplot as plot


def plot_time(plot, msg):
    plot.set_xlabel("Time")
    plot.set_ylabel("Amplitude")
    plot.plot(msg.t, msg.msg)


def plot_freq(plot, msg):
    plot.set_xlabel("Freq (Hz)")
    plot.set_ylabel("|Y(freq)|")
    length = len(msg.msg)
    spacing = 1./msg.fs
    x = np.linspace(0, 1./(2*spacing), length/2)
    y = np.fft.fft(msg.msg)
    plot.plot(x[1:], 2.0/length * np.abs(y[0:length/2])[1:])


def plot_both(msg, title="", filename=""):
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
    if filename: plot.savefig(filename)


def plot_before_after(before, after):
    plots, axes = plot.subplots(2, 2)

    plot_time(axes[0][0], before)
    plot_freq(axes[0][1], before)

    plot_time(axes[1][0], after)
    plot_freq(axes[1][1], after)

def plot_before_after_amqam(before1, before2, after1, after2, filename=''):
    plots, axes = plot.subplots(4, 2)

    plot_time(axes[0][0], before1)
    plot_freq(axes[0][1], before1)

    plot_time(axes[1][0], before2)
    plot_freq(axes[1][1], before2)

    plot_time(axes[2][0], after1)
    plot_freq(axes[2][1], after1)

    plot_time(axes[3][0], after2)
    plot_freq(axes[3][1], after2)

    if filename: plots.savefig(filename)

def show():
    plot.show()
