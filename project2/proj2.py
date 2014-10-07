# Conrad Appel
# MATH3316
# Oct 7 2014

from pylab import *

x = loadtxt('x.txt')
y = loadtxt('y.txt')
t = loadtxt('t.txt')

figure(1)
plot(t, x)
xlabel('t')
ylabel('x(t)')
title('x(t) vs t')
savefig('./x_vs_t.png', bbox_inches='tight')

figure(2)
plot(t, y)
xlabel('t')
ylabel('y(t)')
title('y(t) vs t')
savefig('./y_vs_t.png', bbox_inches='tight')

figure(3)
plot(x, y)
xlabel('x(t)')
ylabel('y(t)')
title('y(t) vs x(t)')
savefig('./y_vs_x.png', bbox_inches='tight')

show()