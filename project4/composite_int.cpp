// Conrad Appel
// MATH 3316
// 2 Dec 2014

#include <cmath>

#include "mat.h"

// all of these calculations moved outside functions for efficiency
const double node1 = std::sqrt(1.0/7*(3 - 4 * std::sqrt(.3))) * .5;
const double node2 = std::sqrt(1.0/7*(3 + 4 * std::sqrt(.3))) * .5;
const double weight1 = .5 + 1.0/12*std::sqrt(10.0/3);
const double weight2 = .5 - 1.0/12*std::sqrt(10.0/3);

double newton4(double (*f)(const double), const double left, double h) {
    double midpoint = left + h/2; // of current subinterval
    double x0, x1, x2, x3;
    // calculate position of nodes
    x0 = midpoint - h * node1;
    x1 = midpoint - h * node2;
    x2 = midpoint + h * node1;
    x3 = midpoint + h * node2;

    // nodes * respective weights
    return weight1*f(x0)
          +weight2*f(x1)
          +weight1*f(x2)
          +weight2*f(x3);
}

// integrates f from [a, b] with n subintervals
double composite_int(double (*f)(const double), const double a, const double b, const int n) {
    const double h = (b - a) / n; // length of subinterval
    double sum = 0; // sum of all subintervals
    for(unsigned int i = 0; i < n; i++) {
        sum += newton4(f, a + i*h, h);
    }
    return sum*h*.5;
}
