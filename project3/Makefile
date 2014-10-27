all : test_newton compare

test_newton:
	g++ -std=c++11 test_newton.cpp mat.cpp -o test_newton.o

compare:
	g++ -std=c++11 compare.cpp mat.cpp -o compare.o

clean:
	rm -f *.o
