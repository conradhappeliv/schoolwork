// Conrad Appel
// MATH 3316
// Nov 4 2014

#include "mat.h"
#include "lagrange.cpp"

// evaluates the Lagrange interpolated polynomial at specified 2D point (x, y)
double lagrange2D(Mat& x, Mat& y, Mat& f, double a, double b) {
    double sum = 0;
    // implements equation (2) from the project description
    for(int i = 0; i < x.Size(); i++) {
        for(int j = 0; j < y.Size(); j++) {
            sum += f(i, j) * lagrange_basis(x, i, a) * lagrange_basis(y, j, b);
        }
    }
    return sum;
}
