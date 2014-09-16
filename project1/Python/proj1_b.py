# Conrad Appel
# MATH 3316
# 9/16/14

import numpy
from pylab import *

data = {}
for name in ['n', 'h', 'r', 'R']:
    file_name = '../'+name+'.txt'
    data[name] = numpy.loadtxt(file_name)

figure(1)
semilogy(data['n'], data['r'], color='b')
semilogy(data['n'], data['R'], color='r', linestyle='--')
title('n vs r & n vs R')
xlabel('n')
ylabel('r')

figure(2)
loglog(data['h'], data['r'], color='b')
loglog(data['h'], data['R'], color='r', linestyle='--')
title('h vs. r & h vs. R')
xlabel('h')
ylabel('r')

show()