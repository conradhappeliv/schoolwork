import message
import mixer
import channel
import receiver
from plots import plot_before_after, plot_before_after_amqam, show

# message
orig1 = message.sin(10)
orig2 = message.square(10)
m1 = message.sin(10)
m2 = message.square(10)
#plot_both(m, "Before")
#show()

# mixer
m = mixer.AMQAM(m1, m2)

# channel
#m = channel.attenuation(m)
#m = channel.fading(m)
#m = channel.gauss_noise(m)

# receiver
m1, m2 = receiver.demuxAMQAM(m)
#m = receiver.unattenuate(m)
m1 = receiver.lpf(m1)
m2 = receiver.lpf(m2)
#plot_both(m, "After")
plot_before_after_amqam(orig1, orig2, m1, m2)
show()
m.write()
