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
semilogy(data['n'], data['r'], color='b', label='n vs r')
semilogy(data['n'], data['R'], color='r', linestyle='--', label='n vs R')
legend(loc='upper center')
title('n vs r & n vs R')
xlabel('n')
ylabel('r')
savefig('../errsemilogy.png', bbox_inches='tight')

figure(2)
loglog(data['h'], data['r'], color='b', label='h vs r')
loglog(data['h'], data['R'], color='r', linestyle='--', label='h vs R')
legend(loc='upper center')
title('h vs. r & h vs. R')
xlabel('h')
ylabel('r')
savefig('../errloglog.png', bbox_inches='tight')

show()