#include <iostream>
#include <cmath>

#include "mat.h"
#include "composite_int.cpp"

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

    // test composite numerical integration function
    int n[] = {6, 12, 24, 48, 96, 192, 384, 768, 1536, 3072};
    int ntests = 10;
    Mat errs(ntests);
    Mat hvals(ntests);
    Mat approxs(ntests);
    // calculate approxs, errs, convergence rates
    for(unsigned int i = 0; i < ntests; i++) {
        approxs(i) = composite_int(f, a, b, n[i]);
        errs(i) = std::abs((trueVal - approxs(i)) / trueVal);
        hvals(i) = (b - a) / n[i];
    }

    // output results
    std::cout << "Composite Numerical Integration Approximation:" << std::endl;
    for(unsigned int i = 0; i < ntests; i++) {
        printf("   %6i", n[i]);
        if(i == 0)
            printf("  %22.16e  %7.1e     ----\n", approxs(i), errs(i));
        else
            printf("  %22.16e  %7.1e   %f\n", approxs(i), errs(i), (std::log(errs(i-1)) - std::log(errs(i)))/(std::log(hvals(i-1)) - std::log(hvals(i))));
    }

    return 0;
}
