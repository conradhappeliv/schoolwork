# Conrad Appel
# MATH 3316
# 2 Dec 2014

from pylab import *

x = loadtxt('./x.txt')
t = loadtxt('./t.txt')
c900 = loadtxt('./c900.txt')
c900_1 = loadtxt('./c900_1hour.txt')
c900_6 = loadtxt('./c900_6hour.txt')
c900_12 = loadtxt('./c900_12hour.txt')
c900_24 = loadtxt('./c900_24hour.txt')
c900_48 = loadtxt('./c900_48hour.txt')
c1100 = loadtxt('./c1100.txt')
c1100_1 = loadtxt('./c1100_1hour.txt')
c1100_6 = loadtxt('./c1100_6hour.txt')
c1100_12 = loadtxt('./c1100_12hour.txt')
c1100_24 = loadtxt('./c1100_24hour.txt')
c1100_48 = loadtxt('./c1100_48hour.txt')

figure(1)
imshow(c900, extent=[0, 48, 4, 0], aspect='auto')
ylabel('x (mm)')
xlabel('t (hours)')
title('Carbon Concentration at (t, x) with T = 900 K')
colorbar(orientation='horizontal')
savefig('c900.png')

figure(2)
imshow(c1100, extent=[0, 48, 4, 0], aspect='auto')
ylabel('x (mm)')
xlabel('t (hours)')
title('Carbon Concentration at (t, x) with T = 1100 K')
colorbar(orientation='horizontal')
savefig('c1100.png')

figure(3)
plot(x, c900_1, label='1 hour')
plot(x, c900_6, label='6 hours')
plot(x, c900_12, label='12 hours')
plot(x, c900_24, label='24 hours')
plot(x, c900_48, label='48 hours')
xlabel('x (m)')
ylabel('C(x)')
title('Carbon Concentrations; T = 900K; Varying t')
legend(loc='upper right')
savefig('c900_fixedt.png')

figure(4)
plot(x, c1100_1, label='1 hour')
plot(x, c1100_6, label='6 hours')
plot(x, c1100_12, label='12 hours')
plot(x, c1100_24, label='24 hours')
plot(x, c1100_48, label='48 hours')
xlabel('x (m)')
ylabel('C(x)')
title('Carbon Concentrations; T = 1100K; Varying t')
legend(loc='upper right')
savefig('c1100_fixedt.png')

show()