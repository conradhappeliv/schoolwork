#include <cmath>

#include "mat.h"

// seems to only converge at h^4
double simpsons_rule(double (*f)(const double), const double x0, double h) {
    h /= 2;
    double x1 = x0 + h;
    double x2 = x1 + h;
    return 1.0/3.0 * h * (f(x0) + 4*f(x1) + f(x2));
}

double booles_rule(double (*f)(const double), const double x0, double h) {
    h /= 4;
    double x1, x2, x3, x4;
    x1 = x0 + h;
    x2 = x1 + h;
    x3 = x2 + h;
    x4 = x3 + h;
    return 2.0/45.0 * h * (7*f(x0) + 32*f(x1) + 12*f(x2) + 32*f(x3) + 7*f(x4));
}

double six_point_rule(double (*f)(const double), const double x0, double h) {
    h /= 5;
    double x1, x2, x3, x4, x5;
    x1 = x0 + h;
    x2 = x1 + h;
    x3 = x2 + h;
    x4 = x3 + h;
    x5 = x4 + h;
    return 5.0/288 * h * (19*f(x0) + 75*f(x1) + 50*f(x2) + 50*f(x3) + 75*f(x4) + 19*f(x5));
}

double newton4(double (*f)(const double), const double left, double h) {
    double midpoint = left + h/2;
    double x0, x1, x2, x3;
    x0 = midpoint - .5*h * std::sqrt(1.0/7*(3 - 4 * std::sqrt(.3)));
    x1 = midpoint - .5*h * std::sqrt(1.0/7*(3 + 4 * std::sqrt(.3)));
    x2 = midpoint + .5*h * std::sqrt(1.0/7*(3 - 4 * std::sqrt(.3)));
    x3 = midpoint + .5*h * std::sqrt(1.0/7*(3 + 4 * std::sqrt(.3)));

    return (  (.5 + 1.0/12*std::sqrt(10.0/3))*f(x0)
            + (.5 - 1.0/12*std::sqrt(10.0/3))*f(x1)
            + (.5 + 1.0/12*std::sqrt(10.0/3))*f(x2)
            + (.5 - 1.0/12*std::sqrt(10.0/3))*f(x3));
}

double composite_int(double (*f)(const double), const double a, const double b, const int n) {
    const double h = (b - a) / n;
    double sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += newton4(f, a + i*h, h);
    }
    return sum*h*.5;
}
