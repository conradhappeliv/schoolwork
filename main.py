import message
import mixer
import channel
import receiver
from plots import plot_before_after, show

# message
orig = message.sin()
m = message.sin()
#plot_both(m, "Before")
#show()

# mixer
m = mixer.modulate(m)

# channel
#m = channel.attenuation(m)
#m = channel.fading(m)
#m = channel.gauss_noise(m)

# receiver
m = mixer.modulate(m)
#m = receiver.unattenuate(m)
m = receiver.lpf(m)
#plot_both(m, "After")
plot_before_after(orig, m)
show()
m.write()
