// Conrad Appel
// MATH 3316
// Nov 4 2014

#include "mat.h"
#include "lagrange.cpp"

double lagrange2D(Mat& x, Mat& y, Mat& f, double a, double b) {
    double sum = 0;
    for(int i = 0; i < x.Cols(); i++) {
        for(int j = 0; j < y.Cols(); j++) {
            sum += f(i, j) * lagrange_basis(x, i, a) * lagrange_basis(y, j, b);
        }
    }
    return sum;
}
