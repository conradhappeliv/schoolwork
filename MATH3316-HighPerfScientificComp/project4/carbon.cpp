// Conrad Appel
// MATH 3316
// 2 Dec 2014

#include "adaptive_int.cpp"
#include "mat.h"

#include <cmath>

// initial values for alloy
const double C0 = .0025;
const double Cs = .012;

double erf(const double y, const double rtol, const double atol) {
    double R;
    int n, nTot; // unused but necessary

    // integral of e^(-z^2) from 0 to y
    adaptive_int([](const double z){ // lambda function representing e^(-z^2)
        return std::exp(-(z*z));
    }, 0, y, rtol, atol, R, n, nTot);
    R *= 2.0/std::sqrt(PI); // integral*2sqrt(pi)
    return R;
}

// temp-dependent diffusion coefficient for steel
double D(const double T) {
    return 6.2e-7*std::exp(-8e4/(8.31*T));
}

// x = depth, t = time, T = temp, rtol/atol = relative/absolute tolerance for integration
double carbon(double x, double t, const double T, const double rtol, const double atol) {
    if(t <= 0) return C0; // can't do negative sqrt & if t = 0, no diffusion has occured
    return Cs - (Cs-C0)*erf((x/std::sqrt(4*t*D(T))), rtol, atol);
}

