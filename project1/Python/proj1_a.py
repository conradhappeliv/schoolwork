# Conrad Appel
# MATH3316, Fall 2014
# Due Sep. 16, 2014

import numpy
from pylab import *

data = {}
for name in ['err5', 'err9', 'err13', 'f', 'p5', 'p9', 'p13', 'z']:
    file_name = '../'+name+'.txt'
    data[name] = numpy.loadtxt(file_name)
x = data['z']

figure(1)
plot(x, data['p5'], label='p5')
plot(x, data['p9'], label='p9')
plot(x, data['p13'], label='p13')
plot(x, data['f'], label='sin(x)')
legend(loc='upper left')
ylabel('sin(x)')
xlabel('x')
title('sin(x) approximated with Taylor polynomials')

figure(2)
semilogy(x, data['err5'], label='err(p5)')
semilogy(x, data['err9'], label='err(p9)')
semilogy(x, data['err13'], label='err(p13)')
legend(loc='upper center')
ylabel('err(x)')
xlabel('x')
title('Errors in Taylor polynomial approximations of sin(x)')

show()

