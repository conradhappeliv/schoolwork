#include <iostream>
#include <cmath>

#include "mat.h"
#include "adaptive_int.cpp"

// integrand
const double c = .5;
const double d = 25;
double f(const double x) {
    return (std::exp(c*x) + std::sin(d*x));
}

int main() {
    // limits of integration
    const double a = -1;
    const double b = 7;

    // actual integral value
    double trueVal = 1.0 / c * (std::exp(c*b) - std::exp(c*a)) - 1.0 / d * (std::cos(d*b) - std::cos(d*a));
    printf("True integral value = %22.16e\n\n", trueVal);

    double rtols[] = { 1e-2, 1e-4, 1e-6, 1e-8, 1e-10, 1e-12 };
    double atols[] = { 1e-5, 1e-7, 1e-9, 1e-11, 1e-13, 1e-15 };
    //adaptive_int(f, a, b, rtol, atol, R, n, nTot);

    std::cout << "    rtol     atol      n    nTot        R         |I(f)-R(f)|  rtol|I(f)|+atol" << std::endl;
    for(unsigned int i = 0; i < 6; i++) { // for each pair of tols
        double R;
        int n, nTot = 0;
        int res = adaptive_int(f, a, b, rtols[i], atols[i], R, n, nTot);
        double err = std::abs(trueVal - R);
        double errBound = rtols[i] * std::abs(trueVal) + atols[i];
        printf("  %2.1e | %2.1e | %3u | %5u | %12.6e |  %7.1e  |   %7.1e\n", rtols[i], atols[i], n, nTot, R, err, errBound);
    }
    std::cout << std::endl;
}
