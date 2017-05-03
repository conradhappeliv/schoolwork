// Conrad Appel
// MATH 3316
// 2 Dec 2014
//
// Adapted from project 2 to better suit this application

#include "mat.h"

#include <iostream>
#include <cmath>

double steffensen(double (*f)(const double), double x, int maxit, double tol) {
    double prev_res = x;
    double res = x;
    for(unsigned int i = 0; i < maxit; i++) {
        prev_res = res;
        double f_of_x = f(res);

        // find current df value using Steffensen's
        double df_of_x = (f_of_x - f(res - f_of_x))/f_of_x;

        if(df_of_x == 0) break; // can't divide by 0

        // x(n+1) = x(n) - f(x(n))/f'(x(n))
        res = res - f_of_x/df_of_x;

        // residual after calculating next val
        f_of_x = std::abs(f(res));

        // |h|
        double sol_update = std::abs(res - prev_res);
        if(sol_update <= tol)
            break;
    }
    return res;
}
