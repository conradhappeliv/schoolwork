#include "mat.h"

#include <iostream>
#include <cmath>

double steffensen(double (*f)(const double, void *data), double x, int maxit, double tol, bool show_iterates, void *data) {

    if(show_iterates)
        std::cout << std::endl << "Steffensen's method, starting at " << x << ", with up to " << maxit << " iterations and a tolerance of " << tol << std::endl;

    double prev_res = x;
    double res = x;
    for(unsigned int i = 0; i < maxit; i++) {
        prev_res = res;

        double f_of_x = f(res, NULL);
        double df_of_x = (f_of_x - f(x - f_of_x, NULL)) / f_of_x;

        // x(n+1) = x(n) - f(x(n))/f'(x(n))
        res = res - f_of_x/df_of_x;

        double sol_update = std::abs(res - prev_res);

        if(show_iterates)
            std::cout << "it" << i+1 << " ; guess " << res  << " ; sol'n update "  << sol_update << " ; f(x) = " << f_of_x << std::endl;

        if(sol_update <= tol)
            break;
    }

    std::cout << "final: " << res << std::endl;

    return res;

}
