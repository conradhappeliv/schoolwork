#include <cmath>

#include "mat.h"

double newton4(double (*f)(const double), const double left, double h) {
    double midpoint = left + h/2; // of current subinterval
    double x0, x1, x2, x3;
    // calculate position of nodes
    x0 = midpoint - .5*h * std::sqrt(1.0/7*(3 - 4 * std::sqrt(.3)));
    x1 = midpoint - .5*h * std::sqrt(1.0/7*(3 + 4 * std::sqrt(.3)));
    x2 = midpoint + .5*h * std::sqrt(1.0/7*(3 - 4 * std::sqrt(.3)));
    x3 = midpoint + .5*h * std::sqrt(1.0/7*(3 + 4 * std::sqrt(.3)));

    // nodes * respective weights
    return (  (.5 + 1.0/12*std::sqrt(10.0/3))*f(x0)
            + (.5 - 1.0/12*std::sqrt(10.0/3))*f(x1)
            + (.5 + 1.0/12*std::sqrt(10.0/3))*f(x2)
            + (.5 - 1.0/12*std::sqrt(10.0/3))*f(x3))*h*.5;
}

// integrates f from [a, b] with n subintervals
double composite_int(double (*f)(const double), const double a, const double b, const int n) {
    const double h = (b - a) / n; // length of subinterval
    double sum = 0; // sum of all subintervals
    for(unsigned int i = 0; i < n; i++) {
        sum += newton4(f, a + i*h, h);
    }
    return sum;
}
