// Conrad Appel
// MATH 3316
// 2 Dec 2014

#include "adaptive_int.cpp"
#include "mat.h"

#include <cmath>

const double C0 = .0025;
const double Cs = .012;

double erf(const double y, const double rtol, const double atol) {
    double R;
    int n;
    int nTot;
    /*R = composite_int([](const double z){
        return std::exp(-(z*z));
    }, 0, y, 500);*/
    adaptive_int([](const double z){
        return std::exp(-(z*z));
    }, 0, y, rtol, atol, R, n, nTot);
    R *= 2.0/std::sqrt(PI);
    return R;
}

double D(const double T) {
    return 6.2e-7*std::exp(-8e4/(8.31*T));
}

double carbon(double x, double t, const double T, const double rtol, const double atol) {
    if(t <= 0) return C0;
    return Cs - (Cs-C0)*erf((x/std::sqrt(4*t*D(T))), rtol, atol);
}

