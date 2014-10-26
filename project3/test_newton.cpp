#include <cmath>
#include <iostream>

#include "newton_interp.cpp"
#include "mat.h"

double f(const double x) {
    return exp(-x*x);
}

void testWithNNodes(int n) {
    n -= 1;
    Mat x = Linspace(-2.0, 2.0, n+1);
    Mat y(n+1);
    for(int i = 0; i < n+1; i++) {
        y(i) = f(x(i));
    }
    double dx = 4.0/n;
    Mat z = Linspace(-2.0+dx/2.0, 2.0-dx/2.0, n);

    Mat p(n);
    for(int i = 0; i < n; i++) {
        Mat c(n+1);
        newton_coeffs(x, y, c);
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
    testWithNNodes(6);
    testWithNNodes(12);
    return 0;
}
