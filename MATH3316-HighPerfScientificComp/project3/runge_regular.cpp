// Conrad Appel
// MATH 3316
// Nov 4 2014

#include <iostream>
#include <cmath>

#include "mat.h"
#include "lagrange2D.cpp"

// two-dimensional Runge function
double f(double x, double y) {
    return 1.0/(1.0 + x*x + y*y);
}

// used to reuse code for 8 and 16 nodes
void computeWithNodes(unsigned int n, unsigned int m, std::string filename) {
    Mat x = Linspace(-6, 6, m+1);
    Mat y = Linspace(-6, 6, n+1);

    Mat f_eval(m+1, n+1);
    for(unsigned int i = 0; i < m; i++) {
        for(unsigned int j = 0; j < n; j++) {
            // evaluate f(x, y) at all the nodes
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
    computeWithNodes(8, 8, "./p8_reg.txt");
    computeWithNodes(16, 16, "./p16_reg.txt");

    Mat avals = Linspace(-6, 6, 101);
    Mat bvals = Linspace(-6, 6, 201);

    Mat runge(101, 201);
    for(unsigned int i = 0; i < avals.Size(); i++) {
        for(unsigned int j = 0; j < bvals.Size(); j++) {
            // get all of the actual f values for comparison to our interpolated points
            runge(i, j) = f(avals(i), bvals(j));
        }
    }

    runge.Write("./runge.txt");
    return 0;
}
