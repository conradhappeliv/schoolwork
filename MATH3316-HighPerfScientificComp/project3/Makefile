# Conrad Appel
# MATH 3316
# Nov 4 2014

all: test_newton compare test_lagrange2d runge_regular runge_chebyshev

test_newton:
	g++ -std=c++11 test_newton.cpp mat.cpp -o test_newton.o

compare:
	g++ -std=c++11 compare.cpp mat.cpp -o compare.o

test_lagrange2d:
	g++ -std=c++11 test_lagrange2D.cpp lagrange2D.cpp mat.cpp -o lagrange2D.o

runge_regular:
	g++ -std=c++11 runge_regular.cpp mat.cpp -o runge_regular.o

runge_chebyshev:
	g++ -std=c++11 runge_chebyshev.cpp mat.cpp -o runge_chebyshev.o

clean:
	rm -f *.o *.txt *.png
