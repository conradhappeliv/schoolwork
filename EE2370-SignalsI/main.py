import message
import mixer
import channel
import receiver
from plots import plot_before_after, plot_before_after_amqam, show

# message
orig1 = message.sin()
orig2 = message.square()
m1 = message.sin()
m2 = message.square()

# mixer
m = mixer.AMQAM(m1, m2)

# channel
m = channel.attenuation(m)
m = channel.fading(m)
m = channel.gauss_noise(m)

# receiver
m = receiver.unattenuate(m)
m1, m2 = receiver.demuxAMQAM(m)
m1 = receiver.lpf(m1)
m2 = receiver.lpf(m2)

plot_before_after_amqam(orig1, orig2, m1, m2)
show()
