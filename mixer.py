import numpy as np

carrier_freq = 10000


# Modulates a message signal by a carrier sin wave
def modulate(m):
    m.msg *= np.sin(2*np.pi*carrier_freq*m.t)
    return m


# Given two message signals, combines them into a single carrier signal by modulating each by orthogonal carrier signals
def AMQAM(m1, m2):
    try:
        m1 = modulate(m1)

        # Make the lengths equal
        if len(m1.msg) != len(m2.msg):
            new_len = max(len(m1.msg), len(m2.msg))
            m1.t = m1.t if len(m1.t) > len(m2.t) else m2.t
            try:
                shape = np.zeros(new_len).shape
                m1.msg.resize(shape)
                m1.t.resize(shape)
                m2.msg.resize(shape)
                m2.t.resize(shape)
            except:
                print("COULD NOT RESIZE")

        # Modulate the second signal and add it to the resulting signal
        m1.msg += m2.msg*np.cos(2*np.pi*carrier_freq*m2.t)
    except:
        print("AMQAM broke")
    return m1
