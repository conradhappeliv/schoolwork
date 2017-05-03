// Conrad Appel
// MATH 3316
// Nov 4 2014

#include <cmath>
#include <iostream>

#include "newton_interp.cpp"
#include "mat.h"

// f(x) = e^(-x^2)
double f(const double x) {
    return exp(-x*x);
}

// used to reuse code for 8 and 16 nodes
void testWithNNodes(int n, double range) {
    n -= 1;
    Mat x = Linspace(-2.0, 2.0, n+1);
    Mat y(n+1);
    for(int i = 0; i < n+1; i++) {
        y(i) = f(x(i));
    }
    double dx = 4.0/n;
    Mat z = Linspace(-range+dx/2.0, range-dx/2.0, n); // evaluation points

    Mat p(n); // results of interpolation
    Mat c(n+1); // coefficients
    newton_coeffs(x, y, c); // only need to calculate the coefficients once
    for(int i = 0; i < n; i++) {
        // calculate Newton interpolant at each evaluation point
        p(i) = newton_eval(x, c, z(i));
    }

    std::cout << "interpolant/error w/ " << n+1 << " nodes: " << std::endl;
    std::cout << "    z        f(z)               p(z)              error" << std::endl;
    for(int i = 0; i < n; i++) {
        printf("   %6.3f   %16.13f   %16.13f   %g\n", z(i), f(z(i)), p(i), std::abs(f(z(i)) - p(i)));
    }

    std::cout << std::endl << std::endl;
}

int main()
{
    testWithNNodes(6, 2.0);
    testWithNNodes(12, 1.0);
    return 0;
}
