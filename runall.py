import message
import mixer
import channel
import receiver
from plots import plot_both, plot_before_after_amqam

types = [message.voice, message.sin, message.square, message.triangle, message.pulse_train, message.PR_pulse_train]

for msg in types:
    message_name = str(msg).split()[1]
    original_message = msg()
    original_message_aud = msg(length=2)
    original_message_aud.write(filename='audio/'+message_name+'_orig.wav')
    plot_both(original_message, filename='plots/'+message_name+'_orig.png')
    m = mixer.modulate(original_message)
    m_aud = mixer.modulate(original_message_aud)
    m_aud.write(filename='audio/'+message_name+'_mod1.wav')
    plot_both(m, filename='plots/'+message_name+'_mod1.png')
    m = mixer.modulate(m)
    m_aud = mixer.modulate(m_aud)
    m_aud.write(filename='audio/'+message_name+'_mod2.wav')
    plot_both(m, filename='plots/'+message_name+'_mod2.png')
    m = receiver.lpf(m)
    m_aud = receiver.lpf(m_aud)
    m_aud.write(filename='audio/'+message_name+'_lpf.wav')
    plot_both(m, filename='plots/'+message_name+'_lpf.png')
    for fn in [channel.attenuation, channel.fading, channel.gauss_noise]:
        function_name = str(fn).split()[1]
        original_message = msg()
        original_message_aud = msg(length=2)
        m = fn(original_message)
        m_aud = fn(original_message_aud)
        m_aud.write(filename='audio/'+message_name+'_'+function_name+'.wav')
        plot_both(m, filename='plots/'+message_name+'_'+function_name+'.png')

#am-qam
for ind1 in range(len(types)):
    msg1 = types[ind1]
    name1 = str(msg1).split()[1]
    orig1 = msg1()
    orig1.write(filename='audio/qam/'+name1+'_orig.wav')
    plot_both(orig1, filename='plots/qam/'+name1+'_orig.png')
    for msg2 in types[ind1:]:
        name2 = str(msg2).split()[1]
        orig2 = msg2()
        m = mixer.AMQAM(msg1(), msg2())
        m1, m2 = receiver.demuxAMQAM(m)
        m1 = receiver.lpf(m1)
        m2 = receiver.lpf(m2)
        m1.write(filename='audio/qam/'+name1+'_'+name2+'_msg1.wav')
        m2.write(filename='audio/qam/'+name1+'_'+name2+'_msg2.wav')
        plot_before_after_amqam(orig1, orig2, m1, m2, filename='plots/qam/'+name1+'_'+name2+'.png')