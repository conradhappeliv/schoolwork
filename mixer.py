import numpy as np

carrier_freq = 10000

def modulate(m):
    m.msg *= np.sin(2*np.pi*carrier_freq*m.t)
    return m

