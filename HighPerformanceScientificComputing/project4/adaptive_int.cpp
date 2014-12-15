// Conrad Appel
// MATH 3316
// 2 Dec 2014

#include <cmath>

#include "composite_int.cpp"

// Approximates integral of f from [a, b], with a desired relative and absolute tolerance of rtol & atol
// stores result in R and final number of intervals in n, with total calculated intervals in nTot
int adaptive_int(double (*f)(const double), const double a, const double b, const double rtol, const double atol, double& R, int& n, int& nTot) {
    int k = 5; // initial value of k
    n = 15; // initial value of n
    double cur, next;
    next = composite_int(f, a, b, n);
    do {
        if(n >= 10000000) return 1; // convergence isn't happening fast enough or at all
        nTot += 2*n + k; // accounts for both calculation of cur and next in this iteration
        cur = next;
        n = n + k; // increment n
        next = composite_int(f, a, b, n);
        k = n; // increase n by a proportion of itself
    } while(std::abs(next-cur) >= (rtol*std::abs(next) + atol)); // compares error between iterations to desired accuracy
    R = next;
    return 0;
}
