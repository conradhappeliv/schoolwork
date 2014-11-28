#include <cmath>

#include "composite_int.cpp"

int adaptive_int(double (*f)(const double), const double a, const double b, const double rtol, const double atol, double& R, int& n, int& nTot) {
    int k = 5;
    n = 1;
    double cur, next;
    next = composite_int(f, a, b, n);
    do {
        if(n >= 1000000) return 1;
        nTot += 2*n + k;
        cur = next;
        n = n + k;
        next = composite_int(f, a, b, n);
        k = n/3;
    } while(std::abs(next-cur) >= (rtol*std::abs(next) + atol));
    R = next;
    return 0;
}
