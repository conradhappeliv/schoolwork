%%% scaling of signals

function siggraphscaled
clear all
clf
% plot actual signal above i.e. y(t)
t=-3:0.002:5
y=exp(-abs(t)/4).*(ustep(t)-ustep(t-4))
plot(t,y)
title('Original signal y(t)')

% plot time shifted signal i.e. y(t+2)
t1=t+2
y=exp(-abs(t1)/4).*(ustep(t1)-ustep(t1-4))
plot(t,y)
title('time delayed signal (y(t+2))')


% plot time scaled signal i.e. y(2t)

t1=2*t
y=exp(-abs(t1)/4).*(ustep(t1)-ustep(t1-4))
plot(t,y)
title('time delayed signal (y(2))')


% plot time scaled and shifted signal i.e. y(2-2t)


t1=2-2*t
y=exp(-abs(t1)/4).*(ustep(t1)-ustep(t1-4))
plot(t,y)
title('time delayed signal (y(2))')


%%% unit step function, 
% y=ustep(t) = 1 ; t>=0 
% y=ustep(t) = 0 ; t<0 
% t can be matrix or scalar


function y=ustep(t)
y=(t>=0) % (t>=0) returns 1 (true) if t>=0, elase returns a 0 (false)



%%%%%%% Can plot the unit step function as follows:
% t= -5:0.1:5     % generates numbers from -5 to 5 in increments of 0.1
% y=ustep(t)
% plot(t,y)