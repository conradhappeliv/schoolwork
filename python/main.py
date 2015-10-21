import message
import mixer
import channel
import receiver
from plots import plot_time, plot_freq, plot_both, show


# message
m = message.sine()
plot_both(m, "Before")

# mixer
m = mixer.mix(m)

# channel
m = channel.attenuation(m)

# receiver
m = receiver.unattenuate(m)
m = receiver.lpf(m)
plot_both(m, "After")
show()