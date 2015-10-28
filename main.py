import message
import mixer
import channel
import receiver
from plots import plot_time, plot_freq, plot_both, show


# message
m = message.voice()
plot_both(m, "Before")
show()

# mixer
m = mixer.modulate(m)

# channel
m = channel.attenuation(m)

# receiver
m = mixer.modulate(m)
m = receiver.unattenuate(m)
m = receiver.lpf(m)
plot_both(m, "After")
show()
m.write()