/* Conrad Appel
 * MATH3316
 * Oct 7 2014
 */

#include "mat.h"

#include <iostream>
#include <cmath>

double newton(double (*f)(const double, void *data), double (*df)(const double, void *data), double x, int maxit, double tol, bool show_iterates, void *data) {

    if(show_iterates)
        std::cout << std::endl << "Newton's method, starting at " << x << ", with up to " << maxit << " iterations and a tolerance of " << tol << std::endl;

    double prev_res = x;
    double res = x;
    for(unsigned int i = 0; i < maxit; i++) {
        prev_res = res;
        double f_of_x = f(res, data);

        // x(n+1) = x(n) -  f(x(n))/f'(x(n))
        res = res - f_of_x/df(res, data);

        // residual after calculating next val
        f_of_x = std::abs(f(res, data));

        // |h|
        double sol_update = std::abs(res - prev_res);

        if(show_iterates)
            std::cout << "it" << i << " ; guess " << res  << " ; sol'n update "  << sol_update << " ; f(x) = " << f_of_x << std::endl;

        if(sol_update <= tol)
            break;
    }
    if(show_iterates)
        std::cout << "final: " << res << std::endl;

    return res;

}
