import message
import mixer
import channel
import receiver
from plots import plot_both

for msg in [message.sin, message.square, message.triangle, message.pulse_train, message.PR_pulse_train, message.voice]:
    message_name = str(msg).split()[1]
    original_message = msg()
    original_message.write(filename='audio/'+message_name+'_orig.wav')
    plot_both(original_message, filename='plots/'+message_name+'_orig.png')
    m = mixer.modulate(original_message)
    m.write(filename='audio/'+message_name+'_mod1.wav')
    plot_both(m, filename='plots/'+message_name+'_mod1.png')
    m = mixer.modulate(original_message)
    m.write(filename='audio/'+message_name+'_mod2.wav')
    plot_both(m, filename='plots/'+message_name+'_mod2.png')
    m = receiver.lpf(m)
    m.write(filename='audio/'+message_name+'_lpf.wav')
    plot_both(m, filename='plots/'+message_name+'_lpf.png')