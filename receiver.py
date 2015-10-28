from scipy import signal

def unattenuate(m):
    return m

def lpf(m):
    filt = signal.firwin(numtaps=10, cutoff=800, nyq=80000)
    m.msg = signal.lfilter(filt, 1.0, m.msg)
    return m

