#include <iostream>
#include <cmath>

#include "mat.h"
#include "adaptive_int.cpp"

//integrand
const double c = .5;
const double d = 25;
double f(const double x) {
    return (std::exp(c*x) + std::sin(d*x));
}

int main() {
    //limits of integration
    const double a = -1;
    const double b = 7;

    // actual integral value
    double trueVal = 1.0 / c * (std::exp(c*b) - std::exp(c*a)) - 1.0 / d * (std::cos(d*b) - std::cos(d*a));
    printf("True integral value = %22.16e\n\n", trueVal);


}
