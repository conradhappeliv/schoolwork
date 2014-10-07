/* Conrad Appel
 * MATH3316
 * Oct 7 2014
 */

#include "mat.h"
#include "newton.cpp"

#include <cmath>

const double epsilon = 0.86602540378;

// function defs
double f(double, void*);
double df(double, void*);
double r(double);

int main() {
    Mat t = Linspace(0, 9, 9001);
    Mat omega = Mat(9001);
    Mat x = Mat(9001);
    Mat y = Mat(9001);
    for(unsigned int i = 0; i < 9001; i++) {
        double guess;
        if(i == 0) guess = 0.0;
        else guess = omega(i-1);
        omega(i) = newton(f, df, guess, 5, 1/10000, false, &t(i));
        x(i) = r(omega(i))*cos(omega(i));
        y(i) = r(omega(i))*sin(omega(i));
    }
    t.Write("t.txt");
    x.Write("x.txt");
    y.Write("y.txt");
    return 0;
}

double f(double omega, void* data) {
    double* data_casted = (double*) data;
    return omega - epsilon*sin(omega) - *data_casted;
}

double df(double omega, void* data) {
    return 1 - epsilon*cos(omega);
}

double r(double x) {
    return .5/sqrt(pow(.5*cos(x), 2) + sin(x)*sin(x));
}
