# Conrad Appel
# MATH 3316
# 2 Dec 2014

all: test_int test_adapt carbon application

test_int:
	g++ -std=c++11 test_int.cpp mat.cpp -o test_int.out

test_adapt:
	g++ -std=c++11 test_adapt.cpp mat.cpp -o test_adapt.out

carbon:
	g++ -std=c++11 test_carbon.cpp mat.cpp -o carbon.out

application:
	g++ -std=c++11 application.cpp mat.cpp -o application.out

clean:
	rm -f *.out *.txt *.png
