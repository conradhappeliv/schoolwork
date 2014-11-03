#include <iostream>
#include <cmath>

#include "mat.h"
#include "lagrange2D.cpp"

double f(int x, int y) {
    return 1.0/(1 + std::pow(x, 2) + std::pow(y, 2));
}

void computeWithNodes(unsigned int n, unsigned int m, std::string filename) {
    Mat x = Linspace(-6, 6, m+1);
    Mat y = Linspace(-6, 6, n+1);

    Mat f_eval(m+1, n+1);
    for(unsigned int i = 0; i < m; i++) {
        for(unsigned int j = 0; j < n; j++) {
            f_eval(i, j) = f(i, j);
        }
    }

    Mat avals = Linspace(-6, 6, 101);
    Mat bvals = Linspace(-6, 6, 201);

    Mat p(101, 201);
    for(unsigned int i = 0; i < avals.Size(); i++) {
        for(unsigned int j = 0; j < bvals.Size(); j++) {
            p(i, j) = lagrange2D(x, y, f_eval, i, j);
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
            runge(i, j) = f(avals(i), bvals(j));
        }
    }

    runge.Write("./runge.txt");

    return 0;
}
