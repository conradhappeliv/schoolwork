/* Conrad Appel
 * MATH3316
 * Oct 7 2014
 */

#include "newton.cpp"

#include <iostream>

using namespace std;

double f(const double, void*);
double df(const double, void*);

int main() {
    int guesses[3] = { -1, 2, 3 };
    double tols[3] = { 10e-4, 10e-8, 10e-12 };
    int maxit = 15;

    for(unsigned int i = 0; i < 3; i++) {
        for(unsigned int j = 0; j < 3; j++) {
            int guess = guesses[i];
            double tol = tols[j];
            double res = newton(f, df, guess, maxit, tol, true, NULL);
        }
    }
    return 0;
}

double f(const double x, void *data) {
    return .20 * (x - 5) * (x + 2) * (x + 3);
}

double df(const double x, void *data) {
    // d/dx .2(x^3 - 19x - 30) = .2(3x^2 - 19) = .06x^2 - 3.8
    return .6 * x*x - 3.8;
}
