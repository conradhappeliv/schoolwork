all : test_newton compare test_lagrange2d

test_newton:
	g++ -std=c++11 test_newton.cpp mat.cpp -o test_newton.o

compare:
	g++ -std=c++11 compare.cpp mat.cpp -o compare.o

test_lagrange2d:
	g++ -std=c++11 test_lagrange2D.cpp lagrange2D.cpp mat.cpp -o lagrange2D.o

clean:
	rm -f *.o *.txt *.png
