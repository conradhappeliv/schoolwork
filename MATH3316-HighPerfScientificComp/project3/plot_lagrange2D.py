#!/usr/bin/env python
#
# Lagrange2D testing script
#
# Daniel R. Reynolds
# SMU Mathematics
# Math 3316
# 5 October 2014

from pylab import *

# Load all data output by test_lagrange2D.cpp routine:

a = loadtxt('a.txt')
b = loadtxt('b.txt')
f = loadtxt('ftrue.txt')
p6 = loadtxt('p6.txt')
p15 = loadtxt('p15.txt')

# Plot $f(x,y)$ first

from mpl_toolkits.mplot3d.axes3d import Axes3D
fig = figure()
ax = fig.add_subplot(111, projection='3d')
X, Y = meshgrid(b, a)
surf = ax.plot_surface(X, Y, f, rstride=1, cstride=1,linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$f(x,y)$')
savefig('lagrange2d_f.png')

# Now plot both $p_6(x,y)$ and $p_{15}(x,y)$

fig = figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, p6, rstride=1, cstride=1,linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$p_6(x,y)$')
savefig('lagrange2d_p6.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, p15, rstride=1, cstride=1,linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$p_{15}(x,y)$')
savefig('lagrange2d_p15.png')

# Now plot the error in p6

e6 = abs(f-p6)
fig = figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, e6, rstride=1, cstride=1,linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$|f(x,y) - p_6(x,y)|$')
savefig('lagrange2d_e6.png')

e15 = abs(f-p15)
fig = figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, e15, rstride=1, cstride=1,linewidth=0, cmap=cm.jet)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$|f(x,y) - p_{15}(x,y)|$')
savefig('lagrange2d_e15.png')

# Now check the max error for each, and compare against a known tolerance for
# these functions over these intervals with this many nodes 

e6norm = sqrt(sum(sum(e6**2))/size(e6))
e15norm = sqrt(sum(sum(e15**2))/size(e15))
if (e6norm > 0.013):
    print 'p6 faulure!   ||e6|| = ', e6norm, ' is above tolerance of 0.013'
else:
    print 'p6 success!   ||e6|| = ', e6norm, ' is below tolerance of 0.013'
if (e15norm > 4.e-8):
    print 'p15 failure!  ||e15|| = ', e15norm, ' is above tolerance of 4e-8'
else:
    print 'p15 success!  ||e15|| = ', e15norm, ' is below tolerance of 4e-8'

