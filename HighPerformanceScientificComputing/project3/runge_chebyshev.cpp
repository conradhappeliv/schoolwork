// Conrad Appel
// MATH 3316
// Nov 4 2014

#include <iostream>
#include <cmath>

#include "mat.h"
#include "lagrange2D.cpp"

// two-dimensional Runge function
double f(int x, int y) {
    return 1.0/(1 + std::pow(x, 2) + std::pow(y, 2));
}

// this method uses Chebyshev nodes in order to remedy the issues
// associated with equispaced interpolation points
// x(i) = L*cos(pi*(2i + 1)/(2m+2))
double chebNode(double n, double i, double m) {
    return n*std::cos((2*i + 1) * PI / (2*m + 2));
}

// used to reuse code for 8 and 16 nodes
void computeWithNodes(unsigned int n, unsigned int m, std::string filename) {
    Mat x(m+1);
    Mat y(n+1);
    for(unsigned int i = 0; i < x.Size(); i++) {
        // calculate all of the Chebyshev nodes
        x(i) = chebNode(6, i, m);
        y(i) = chebNode(6, i, m);
    }

    // evaluate f(x, y) at all the nodes
    Mat f_eval(m+1, n+1);
    for(unsigned int i = 0; i < x.Size(); i++) {
        for(unsigned int j = 0; j < y.Size(); j++) {
            f_eval(i, j) = f(x(i), y(j));
        }
    }

    Mat avals = Linspace(-6, 6, 101);
    Mat bvals = Linspace(-6, 6, 201);

    Mat p(101, 201);
    for(unsigned int i = 0; i < avals.Size(); i++) {
        for(unsigned int j = 0; j < bvals.Size(); j++) {
            // evaluate the 2D Lagrange polynomial at all points in avals and bvals
            p(i, j) = lagrange2D(x, y, f_eval, avals(i), bvals(j));
        }
    }

    avals.Write("./avals.txt");
    bvals.Write("./bvals.txt");
    p.Write(filename.c_str());
}

int main() {
    computeWithNodes(8, 8, "./p8_cheb.txt");
    computeWithNodes(16, 16, "./p16_cheb.txt");

    return 0;
}
