#!/usr/bin/env python

# Conrad Appel
# MATH3316
# Nov 4 2014

from pylab import *
from mpl_toolkits.mplot3d import Axes3D

f = loadtxt('./runge.txt')
p8_reg = loadtxt('./p8_reg.txt')
p16_reg = loadtxt('./p16_reg.txt')
p8_cheb = loadtxt('./p8_cheb.txt')
p16_cheb = loadtxt('./p16_cheb.txt')

err_p8_reg = ndarray(shape=(101, 201))
err_p16_reg = ndarray(shape=(101, 201))
err_p8_cheb = ndarray(shape=(101, 201))
err_p16_cheb = ndarray(shape=(101, 201))

# error calculations
for i in range(101):
    for j in range(201):
        err_p8_reg[i, j] = abs(f[i, j] - p8_reg[i, j])
        err_p16_reg[i, j] = abs(f[i, j] - p16_reg[i, j])
        err_p8_cheb[i, j] = abs(f[i, j] - p8_cheb[i, j])
        err_p16_cheb[i, j] = abs(f[i, j] - p16_cheb[i, j])

avals = loadtxt('./avals.txt')
bvals = loadtxt('./bvals.txt')

X, Y = meshgrid(bvals, avals)

fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, f)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$f(x,y)$')
savefig('runge2d_f.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, p8_reg)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$p8reg(x,y)$')
savefig('runge_p8_reg.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, p16_reg)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$p16reg(x,y)$')
savefig('runge_p16_reg.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, p8_cheb)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$p8cheb(x,y)$')
savefig('runge_p8_cheb.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, p16_cheb)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$p16cheb(x,y)$')
savefig('runge_p16_cheb.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, err_p8_reg)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$err(p8reg(x,y))$')
savefig('runge_p8_reg_err.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, err_p16_reg)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$err(p16reg(x,y))$')
savefig('runge_p16_reg_err.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, err_p8_cheb)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$err(p8cheb(x,y))$')
savefig('runge_p8_cheb_err.png')

fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, err_p16_cheb)
ax.set_xlabel('x')
ax.set_ylabel('y')
title('$err(p16cheb(x,y))$')
savefig('runge_p16_cheb_err.png')

show()
