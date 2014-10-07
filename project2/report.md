Project 2 - Nonlinear Solvers 
==================================================

Conrad Appel - 10/07/2014 - MATH 3316

In this project, we'll be demonstrating the similarities and differences between two types of linear solvers: Newton's method and Steffensen's method. Then, we'll apply Newton's method to Kepler's equation (used to find a position of an object in an elliptical orbit).

Part 1:
-------

In this first part, I implemented a root-solving method called Newton's method that uses the function, its derivative, and an initial guess to find its roots. The method runs up to a user-specified maximum number of iterations or until the difference between two iterations (`|h|`) is smaller than a user-specified tolerance. The iterations all update using this formula: `x(n+1) = x(n) - f(x(n))/f'(x(n))`. Ideally, at each iteration the current solution will approach the actual root more and more.

`newton.cpp`

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

In order to test the Newton's method function shown above, a driver script was created. In this driver, Newton's method is tested with initial guesses of -1, 2, and 3, and with answer tolerances of 10^-3, 10^-7, and 10^-11, all with a maximum number of 15 iterations. The function used to test it is as follows: `f(x) = .20(x-5)(x+2)(x+3)`, with a subsequent derivative of `f'(x) = .6*x^2 - 3.8`.

`test_newton.cpp`

    /* Conrad Appel
     * MATH3316
     * Oct 7 2014
     */
    
    #include "newton.cpp"
    
    #include <iostream>
    
    using namespace std;
    
    double f(const double, void*);
    double df(const double, void*);
    
    int main() {
        int guesses[3] = { -1, 2, 3 };
        double tols[3] = { 10e-4, 10e-8, 10e-12 };
        int maxit = 15;
    
        for(unsigned int i = 0; i < 3; i++) {
            for(unsigned int j = 0; j < 3; j++) {
                int guess = guesses[i];
                double tol = tols[j];
                double res = newton(f, df, guess, maxit, tol, true, NULL);
            }
        }
        return 0;
    }
    
    double f(const double x, void *data) {
        return .20 * (x - 5) * (x + 2) * (x + 3);
    }
    
    double df(const double x, void *data) {
        // d/dx .2(x^3 - 19x - 30) = .2(3x^2 - 19) = .06x^2 - 3.8
        return .6 * x*x - 3.8;
    }

Results:

    Newton's method, starting at -1, with up to 15 iterations and a tolerance of 0.001
    it0 ; guess -1.75 ; sol'n update 0.75 ; f(x) = 0.421875
    it1 ; guess -1.96497 ; sol'n update 0.214968 ; f(x) = 0.0505087
    it2 ; guess -1.99902 ; sol'n update 0.0340506 ; f(x) = 0.00137486
    it3 ; guess -2 ; sol'n update 0.000980394 ; f(x) = 1.15303e-06
    final: -2
    
    Newton's method, starting at -1, with up to 15 iterations and a tolerance of 1e-07
    it0 ; guess -1.75 ; sol'n update 0.75 ; f(x) = 0.421875
    it1 ; guess -1.96497 ; sol'n update 0.214968 ; f(x) = 0.0505087
    it2 ; guess -1.99902 ; sol'n update 0.0340506 ; f(x) = 0.00137486
    it3 ; guess -2 ; sol'n update 0.000980394 ; f(x) = 1.15303e-06
    it4 ; guess -2 ; sol'n update 8.23591e-07 ; f(x) = 8.13838e-13
    it5 ; guess -2 ; sol'n update 5.81313e-13 ; f(x) = 0
    final: -2
    
    Newton's method, starting at -1, with up to 15 iterations and a tolerance of 1e-11
    it0 ; guess -1.75 ; sol'n update 0.75 ; f(x) = 0.421875
    it1 ; guess -1.96497 ; sol'n update 0.214968 ; f(x) = 0.0505087
    it2 ; guess -1.99902 ; sol'n update 0.0340506 ; f(x) = 0.00137486
    it3 ; guess -2 ; sol'n update 0.000980394 ; f(x) = 1.15303e-06
    it4 ; guess -2 ; sol'n update 8.23591e-07 ; f(x) = 8.13838e-13
    it5 ; guess -2 ; sol'n update 5.81313e-13 ; f(x) = 0
    final: -2

    Newton's method, starting at 2, with up to 15 iterations and a tolerance of 0.001
    it0 ; guess -6.57143 ; sol'n update 8.57143 ; f(x) = 37.7843
    it1 ; guess -4.86252 ; sol'n update 1.70891 ; f(x) = 10.5164
    it2 ; guess -3.85001 ; sol'n update 1.01251 ; f(x) = 2.78338
    it3 ; guess -3.30356 ; sol'n update 0.546452 ; f(x) = 0.657155
    it4 ; guess -3.06443 ; sol'n update 0.239131 ; f(x) = 0.11061
    it5 ; guess -3.00413 ; sol'n update 0.0602968 ; f(x) = 0.00664097
    it6 ; guess -3.00002 ; sol'n update 0.00411235 ; f(x) = 3.04686e-05
    it7 ; guess -3 ; sol'n update 1.90421e-05 ; f(x) = 6.52683e-10
    final: -3

    Newton's method, starting at 2, with up to 15 iterations and a tolerance of 1e-07
    it0 ; guess -6.57143 ; sol'n update 8.57143 ; f(x) = 37.7843
    it1 ; guess -4.86252 ; sol'n update 1.70891 ; f(x) = 10.5164
    it2 ; guess -3.85001 ; sol'n update 1.01251 ; f(x) = 2.78338
    it3 ; guess -3.30356 ; sol'n update 0.546452 ; f(x) = 0.657155
    it4 ; guess -3.06443 ; sol'n update 0.239131 ; f(x) = 0.11061
    it5 ; guess -3.00413 ; sol'n update 0.0602968 ; f(x) = 0.00664097
    it6 ; guess -3.00002 ; sol'n update 0.00411235 ; f(x) = 3.04686e-05
    it7 ; guess -3 ; sol'n update 1.90421e-05 ; f(x) = 6.52683e-10
    it8 ; guess -3 ; sol'n update 4.07927e-10 ; f(x) = 0
    final: -3

    Newton's method, starting at 2, with up to 15 iterations and a tolerance of 1e-11
    it0 ; guess -6.57143 ; sol'n update 8.57143 ; f(x) = 37.7843
    it1 ; guess -4.86252 ; sol'n update 1.70891 ; f(x) = 10.5164
    it2 ; guess -3.85001 ; sol'n update 1.01251 ; f(x) = 2.78338
    it3 ; guess -3.30356 ; sol'n update 0.546452 ; f(x) = 0.657155
    it4 ; guess -3.06443 ; sol'n update 0.239131 ; f(x) = 0.11061
    it5 ; guess -3.00413 ; sol'n update 0.0602968 ; f(x) = 0.00664097
    it6 ; guess -3.00002 ; sol'n update 0.00411235 ; f(x) = 3.04686e-05
    it7 ; guess -3 ; sol'n update 1.90421e-05 ; f(x) = 6.52683e-10
    it8 ; guess -3 ; sol'n update 4.07927e-10 ; f(x) = 0
    it9 ; guess -3 ; sol'n update 0 ; f(x) = 0
    final: -3

    Newton's method, starting at 3, with up to 15 iterations and a tolerance of 0.001
    it0 ; guess 10.5 ; sol'n update 7.5 ; f(x) = 185.625
    it1 ; guess 7.52285 ; sol'n update 2.97715 ; f(x) = 50.5619
    it2 ; guess 5.84618 ; sol'n update 1.67668 ; f(x) = 11.7464
    it3 ; guess 5.14308 ; sol'n update 0.703098 ; f(x) = 1.66451
    it4 ; guess 5.00519 ; sol'n update 0.137896 ; f(x) = 0.0581538
    it5 ; guess 5.00001 ; sol'n update 0.00517791 ; f(x) = 8.04879e-05
    it6 ; guess 5 ; sol'n update 7.18639e-06 ; f(x) = 1.54934e-10
    final: 5
    
    Newton's method, starting at 3, with up to 15 iterations and a tolerance of 1e-07
    it0 ; guess 10.5 ; sol'n update 7.5 ; f(x) = 185.625
    it1 ; guess 7.52285 ; sol'n update 2.97715 ; f(x) = 50.5619
    it2 ; guess 5.84618 ; sol'n update 1.67668 ; f(x) = 11.7464
    it3 ; guess 5.14308 ; sol'n update 0.703098 ; f(x) = 1.66451
    it4 ; guess 5.00519 ; sol'n update 0.137896 ; f(x) = 0.0581538
    it5 ; guess 5.00001 ; sol'n update 0.00517791 ; f(x) = 8.04879e-05
    it6 ; guess 5 ; sol'n update 7.18639e-06 ; f(x) = 1.54934e-10
    it7 ; guess 5 ; sol'n update 1.38334e-11 ; f(x) = 0
    final: 5
    
    Newton's method, starting at 3, with up to 15 iterations and a tolerance of 1e-11
    it0 ; guess 10.5 ; sol'n update 7.5 ; f(x) = 185.625
    it1 ; guess 7.52285 ; sol'n update 2.97715 ; f(x) = 50.5619
    it2 ; guess 5.84618 ; sol'n update 1.67668 ; f(x) = 11.7464
    it3 ; guess 5.14308 ; sol'n update 0.703098 ; f(x) = 1.66451
    it4 ; guess 5.00519 ; sol'n update 0.137896 ; f(x) = 0.0581538
    it5 ; guess 5.00001 ; sol'n update 0.00517791 ; f(x) = 8.04879e-05
    it6 ; guess 5 ; sol'n update 7.18639e-06 ; f(x) = 1.54934e-10
    it7 ; guess 5 ; sol'n update 1.38334e-11 ; f(x) = 0
    it8 ; guess 5 ; sol'n update 0 ; f(x) = 0
    final: 5


For each of the -1 guess cases, the final result approached the -2 root of the function, soon rounding off to -2 after 4 iterations due to roundoff error within the computer, at which point the method stops no matter the tolerance as the difference between iterations is 0. The same happens with a guess of 2, which approaches the -3 root, rounding off after 7 iterations. The same also happens with the 3 guess, which approaches 5 and rounds off after 6 iterations. No matter the guess, all of the trials quickly approached a root and were able to end before reaching the max number of iterations.


Part 2:
-------

In this second part, I implemented another method for finding roots, Steffensen's method, which doesn't require the function's derivative, instead approximating the derivative using the slope between two points separated by a difference using formula `f'(x) = [f(x) - f(x-f(x))]/f(x)`. Other than the method for finding the derivative, Steffensen's method follows most of the same pattern as Newton's.

`steffensen.cpp`

    /* Conrad Appel
     * MATH3316
     * Oct 7 2014
     */
    
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
            double f_of_x = f(res, data);
    
            // find current df value using Steffensen's
            double df_of_x = (f_of_x - f(res - f_of_x, data))/f_of_x;
    
            // x(n+1) = x(n) - f(x(n))/f'(x(n))
            res = res - f_of_x/df_of_x;
    
            // residual after calculating next val
            f_of_x = std::abs(f(res, data));
    
            // |h|
            double sol_update = std::abs(res - prev_res);
    
    
            if(show_iterates)
                std::cout << "it" << i << " ; guess " << res  << " ; sol'n update "  << sol_update << " ; f(x) = " << f_of_x << std::endl;
    
            if(sol_update <= tol)
                break;
        }
    
        std::cout << "final: " << res << std::endl;
    
        return res;
    
    }

The driver file also follows the same pattern as Newton's, even using the same guesses and tolerances. The only differences are that Steffensen's method is allowed a maximum of 20 iterations and we don't need to pass in the derivative function.

`test_steffensen.cpp`

    /* Conrad Appel
     * MATH3316
     * Oct 7 2014
     */
    
    #include "steffensen.cpp"
    
    #include <iostream>
    
    using namespace std;
    
    double f(const double, void*);
    
    int main() {
        int guesses[3] = { -1, 2, 3 };
        double tols[3] = { 10e-4, 10e-8, 10e-12 };
        int maxit = 20;
    
        for(unsigned int i = 0; i < 3; i++) {
            for(unsigned int j = 0; j < 3; j++) {
                int guess = guesses[i];
                double tol = tols[j];
                double res = steffensen(f, guess, maxit, tol, true, NULL);
            }
        }
        return 0;
    }
    
    double f(const double x, void *data) {
        return .20 * (x - 5) * (x + 2) * (x + 3);
    }

Results:

    Steffensen's method, starting at -1, with up to 20 iterations and a tolerance of 0.001
    it0 ; guess -1.68807 ; sol'n update 0.688073 ; f(x) = 0.547385
    it1 ; guess -1.89985 ; sol'n update 0.211776 ; f(x) = 0.152046
    it2 ; guess -1.98418 ; sol'n update 0.0843276 ; f(x) = 0.0224516
    it3 ; guess -1.99951 ; sol'n update 0.0153311 ; f(x) = 0.000688776
    it4 ; guess -2 ; sol'n update 0.000491279 ; f(x) = 6.95489e-07
    final: -2

    Steffensen's method, starting at -1, with up to 20 iterations and a tolerance of 1e-07
    it0 ; guess -1.68807 ; sol'n update 0.688073 ; f(x) = 0.547385
    it1 ; guess -1.89985 ; sol'n update 0.211776 ; f(x) = 0.152046
    it2 ; guess -1.98418 ; sol'n update 0.0843276 ; f(x) = 0.0224516
    it3 ; guess -1.99951 ; sol'n update 0.0153311 ; f(x) = 0.000688776
    it4 ; guess -2 ; sol'n update 0.000491279 ; f(x) = 6.95489e-07
    it5 ; guess -2 ; sol'n update 4.96777e-07 ; f(x) = 7.10632e-13
    it6 ; guess -2 ; sol'n update 5.07594e-13 ; f(x) = 0
    final: -2

    Steffensen's method, starting at -1, with up to 20 iterations and a tolerance of 1e-11
    it0 ; guess -1.68807 ; sol'n update 0.688073 ; f(x) = 0.547385
    it1 ; guess -1.89985 ; sol'n update 0.211776 ; f(x) = 0.152046
    it2 ; guess -1.98418 ; sol'n update 0.0843276 ; f(x) = 0.0224516
    it3 ; guess -1.99951 ; sol'n update 0.0153311 ; f(x) = 0.000688776
    it4 ; guess -2 ; sol'n update 0.000491279 ; f(x) = 6.95489e-07
    it5 ; guess -2 ; sol'n update 4.96777e-07 ; f(x) = 7.10632e-13
    it6 ; guess -2 ; sol'n update 5.07594e-13 ; f(x) = 0
    final: -2

    Steffensen's method, starting at 2, with up to 20 iterations and a tolerance of 0.001
    it0 ; guess 2.28708 ; sol'n update 0.287081 ; f(x) = 12.2983
    it1 ; guess 2.55176 ; sol'n update 0.264682 ; f(x) = 12.3735
    it2 ; guess 2.80087 ; sol'n update 0.249103 ; f(x) = 12.2488
    it3 ; guess 3.03872 ; sol'n update 0.23785 ; f(x) = 11.9353
    it4 ; guess 3.26828 ; sol'n update 0.229563 ; f(x) = 11.4373
    it5 ; guess 3.49167 ; sol'n update 0.223386 ; f(x) = 10.7544
    it6 ; guess 3.71035 ; sol'n update 0.218688 ; f(x) = 9.88346
    it7 ; guess 3.92521 ; sol'n update 0.214861 ; f(x) = 8.82041
    it8 ; guess 4.13634 ; sol'n update 0.211128 ; f(x) = 7.56409
    it9 ; guess 4.34255 ; sol'n update 0.206211 ; f(x) = 6.12352
    it10 ; guess 4.54028 ; sol'n update 0.197729 ; f(x) = 4.53424
    it11 ; guess 4.72142 ; sol'n update 0.181135 ; f(x) = 2.89162
    it12 ; guess 4.87017 ; sol'n update 0.148754 ; f(x) = 1.40394
    it13 ; guess 4.96422 ; sol'n update 0.0940486 ; f(x) = 0.396892
    it14 ; guess 4.99675 ; sol'n update 0.0325328 ; f(x) = 0.0363245
    it15 ; guess 4.99997 ; sol'n update 0.00321749 ; f(x) = 0.000320199
    it16 ; guess 5 ; sol'n update 2.85872e-05 ; f(x) = 2.50095e-08
    final: 5

    Steffensen's method, starting at 2, with up to 20 iterations and a tolerance of 1e-07
    it0 ; guess 2.28708 ; sol'n update 0.287081 ; f(x) = 12.2983
    it1 ; guess 2.55176 ; sol'n update 0.264682 ; f(x) = 12.3735
    it2 ; guess 2.80087 ; sol'n update 0.249103 ; f(x) = 12.2488
    it3 ; guess 3.03872 ; sol'n update 0.23785 ; f(x) = 11.9353
    it4 ; guess 3.26828 ; sol'n update 0.229563 ; f(x) = 11.4373
    it5 ; guess 3.49167 ; sol'n update 0.223386 ; f(x) = 10.7544
    it6 ; guess 3.71035 ; sol'n update 0.218688 ; f(x) = 9.88346
    it7 ; guess 3.92521 ; sol'n update 0.214861 ; f(x) = 8.82041
    it8 ; guess 4.13634 ; sol'n update 0.211128 ; f(x) = 7.56409
    it9 ; guess 4.34255 ; sol'n update 0.206211 ; f(x) = 6.12352
    it10 ; guess 4.54028 ; sol'n update 0.197729 ; f(x) = 4.53424
    it11 ; guess 4.72142 ; sol'n update 0.181135 ; f(x) = 2.89162
    it12 ; guess 4.87017 ; sol'n update 0.148754 ; f(x) = 1.40394
    it13 ; guess 4.96422 ; sol'n update 0.0940486 ; f(x) = 0.396892
    it14 ; guess 4.99675 ; sol'n update 0.0325328 ; f(x) = 0.0363245
    it15 ; guess 4.99997 ; sol'n update 0.00321749 ; f(x) = 0.000320199
    it16 ; guess 5 ; sol'n update 2.85872e-05 ; f(x) = 2.50095e-08
    it17 ; guess 5 ; sol'n update 2.23299e-09 ; f(x) = 0
    final: 5

    Steffensen's method, starting at 2, with up to 20 iterations and a tolerance of 1e-11
    it0 ; guess 2.28708 ; sol'n update 0.287081 ; f(x) = 12.2983
    it1 ; guess 2.55176 ; sol'n update 0.264682 ; f(x) = 12.3735
    it2 ; guess 2.80087 ; sol'n update 0.249103 ; f(x) = 12.2488
    it3 ; guess 3.03872 ; sol'n update 0.23785 ; f(x) = 11.9353
    it4 ; guess 3.26828 ; sol'n update 0.229563 ; f(x) = 11.4373
    it5 ; guess 3.49167 ; sol'n update 0.223386 ; f(x) = 10.7544
    it6 ; guess 3.71035 ; sol'n update 0.218688 ; f(x) = 9.88346
    it7 ; guess 3.92521 ; sol'n update 0.214861 ; f(x) = 8.82041
    it8 ; guess 4.13634 ; sol'n update 0.211128 ; f(x) = 7.56409
    it9 ; guess 4.34255 ; sol'n update 0.206211 ; f(x) = 6.12352
    it10 ; guess 4.54028 ; sol'n update 0.197729 ; f(x) = 4.53424
    it11 ; guess 4.72142 ; sol'n update 0.181135 ; f(x) = 2.89162
    it12 ; guess 4.87017 ; sol'n update 0.148754 ; f(x) = 1.40394
    it13 ; guess 4.96422 ; sol'n update 0.0940486 ; f(x) = 0.396892
    it14 ; guess 4.99675 ; sol'n update 0.0325328 ; f(x) = 0.0363245
    it15 ; guess 4.99997 ; sol'n update 0.00321749 ; f(x) = 0.000320199
    it16 ; guess 5 ; sol'n update 2.85872e-05 ; f(x) = 2.50095e-08
    it17 ; guess 5 ; sol'n update 2.23299e-09 ; f(x) = 0
    it18 ; guess -nan ; sol'n update nan ; f(x) = nan
    it19 ; guess -nan ; sol'n update nan ; f(x) = nan
    final: -nan

    Steffensen's method, starting at 3, with up to 20 iterations and a tolerance of 0.001
    it0 ; guess 3.23077 ; sol'n update 0.230769 ; f(x) = 11.5325
    it1 ; guess 3.45506 ; sol'n update 0.224291 ; f(x) = 10.8803
    it2 ; guess 3.67445 ; sol'n update 0.219388 ; f(x) = 10.0407
    it3 ; guess 3.88991 ; sol'n update 0.215463 ; f(x) = 9.0097
    it4 ; guess 4.10169 ; sol'n update 0.211784 ; f(x) = 7.78514
    it5 ; guess 4.30888 ; sol'n update 0.207187 ; f(x) = 6.37361
    it6 ; guess 4.50842 ; sol'n update 0.199535 ; f(x) = 4.80453
    it7 ; guess 4.69314 ; sol'n update 0.184728 ; f(x) = 3.16008
    it8 ; guess 4.84873 ; sol'n update 0.155585 ; f(x) = 1.62628
    it9 ; guess 4.9532 ; sol'n update 0.104474 ; f(x) = 0.517571
    it10 ; guess 4.99457 ; sol'n update 0.041365 ; f(x) = 0.0607438
    it11 ; guess 4.99992 ; sol'n update 0.00535178 ; f(x) = 0.000892291
    it12 ; guess 5 ; sol'n update 7.96532e-05 ; f(x) = 1.94197e-07
    final: 5

    Steffensen's method, starting at 3, with up to 20 iterations and a tolerance of 1e-07
    it0 ; guess 3.23077 ; sol'n update 0.230769 ; f(x) = 11.5325
    it1 ; guess 3.45506 ; sol'n update 0.224291 ; f(x) = 10.8803
    it2 ; guess 3.67445 ; sol'n update 0.219388 ; f(x) = 10.0407
    it3 ; guess 3.88991 ; sol'n update 0.215463 ; f(x) = 9.0097
    it4 ; guess 4.10169 ; sol'n update 0.211784 ; f(x) = 7.78514
    it5 ; guess 4.30888 ; sol'n update 0.207187 ; f(x) = 6.37361
    it6 ; guess 4.50842 ; sol'n update 0.199535 ; f(x) = 4.80453
    it7 ; guess 4.69314 ; sol'n update 0.184728 ; f(x) = 3.16008
    it8 ; guess 4.84873 ; sol'n update 0.155585 ; f(x) = 1.62628
    it9 ; guess 4.9532 ; sol'n update 0.104474 ; f(x) = 0.517571
    it10 ; guess 4.99457 ; sol'n update 0.041365 ; f(x) = 0.0607438
    it11 ; guess 4.99992 ; sol'n update 0.00535178 ; f(x) = 0.000892291
    it12 ; guess 5 ; sol'n update 7.96532e-05 ; f(x) = 1.94197e-07
    it13 ; guess 5 ; sol'n update 1.7339e-08 ; f(x) = 9.9476e-15
    final: 5

    Steffensen's method, starting at 3, with up to 20 iterations and a tolerance of 1e-11
    it0 ; guess 3.23077 ; sol'n update 0.230769 ; f(x) = 11.5325
    it1 ; guess 3.45506 ; sol'n update 0.224291 ; f(x) = 10.8803
    it2 ; guess 3.67445 ; sol'n update 0.219388 ; f(x) = 10.0407
    it3 ; guess 3.88991 ; sol'n update 0.215463 ; f(x) = 9.0097
    it4 ; guess 4.10169 ; sol'n update 0.211784 ; f(x) = 7.78514
    it5 ; guess 4.30888 ; sol'n update 0.207187 ; f(x) = 6.37361
    it6 ; guess 4.50842 ; sol'n update 0.199535 ; f(x) = 4.80453
    it7 ; guess 4.69314 ; sol'n update 0.184728 ; f(x) = 3.16008
    it8 ; guess 4.84873 ; sol'n update 0.155585 ; f(x) = 1.62628
    it9 ; guess 4.9532 ; sol'n update 0.104474 ; f(x) = 0.517571
    it10 ; guess 4.99457 ; sol'n update 0.041365 ; f(x) = 0.0607438
    it11 ; guess 4.99992 ; sol'n update 0.00535178 ; f(x) = 0.000892291
    it12 ; guess 5 ; sol'n update 7.96532e-05 ; f(x) = 1.94197e-07
    it13 ; guess 5 ; sol'n update 1.7339e-08 ; f(x) = 9.9476e-15
    it14 ; guess 5 ; sol'n update 8.88178e-16 ; f(x) = 0
    final: 5

These trials of Steffensen's method started out similar to Newton's method, with a guess of -1 rounding off to the -2 root after 5 iterations. However, with a guess of 2, the method takes much longer to reach its root of 5, finally getting there after 17 iterations. A potential problem shows up when the tolerance is set too strictly for that same guess: because the guess is inadvertantly rounded off to a whole 5 and f(5) = 0, when the method tries plugging that 0 in for its `f(x)` in the denominator, the following guesses all end up being `nan` because the computer doesn't know how to handle dividing by 0. This issue doesn't show up again during these trials, but it could potentially be fixed by including a condition that checks for `nan` and stops at the previous guess if one is found.


Part 3:
-------

In this third part, we applied Newton's method to Kepler's equation for finding the position of an object in an elliptical orbit, or `ω - εsin(ω) = t`. In our usage, we calculated a constant value of 0.86602540378 for ε using `ε = sqrt(1- b^2/a^2)` with `a` and `b` values of `1.0` and `0.5`. We then use `f(ω) = ω - εsin(ω) - t` and `f'(ω) = 1 - εcos(ω)` to plug into Newton's method, passing in our previous guess as ω (or 0 if none made yet), and the current value of t (from {0, .001, ..., 8.999, 9}) to the function on each iteration of Newton's method.

`kepler.cpp`

    /* Conrad Appel
     * MATH3316
     * Oct 7 2014
     */
    
    #include "mat.h"
    #include "newton.cpp"
    
    #include <cmath>
    
    const double epsilon = 0.86602540378;
    
    // function defs
    double f(double, void*);
    double df(double, void*);
    double r(double);
    
    int main() {
        Mat t = Linspace(0, 9, 9001);
        Mat omega = Mat(9001);
        Mat x = Mat(9001);
        Mat y = Mat(9001);
        for(unsigned int i = 0; i < 9001; i++) {
            double guess;
            if(i == 0) guess = 0.0;
            else guess = omega(i-1);
            omega(i) = newton(f, df, guess, 5, 1/10000, false, &t(i));
            x(i) = r(omega(i))*cos(omega(i));
            y(i) = r(omega(i))*sin(omega(i));
        }
        t.Write("t.txt");
        x.Write("x.txt");
        y.Write("y.txt");
        return 0;
    }
    
    double f(double omega, void* data) {
        double* data_casted = (double*) data;
        return omega - epsilon*sin(omega) - *data_casted;
    }
    
    double df(double omega, void* data) {
        return 1 - epsilon*cos(omega);
    }
    
    double r(double x) {
        return .5/sqrt(pow(.5*cos(x), 2) + sin(x)*sin(x));
    }
    
From the roots we gather from Newton's method, we then calculate the x and y values for the position of the objecct at its current calculated angle ω using `r(ω) = ab/sqrt((b*cos(ω))^2 + (a*sin(ω))^2)` (with `a` and `b` the same as above) to be plugged into `x(t) = r(ω)*cos(ω)` and `y(t) = r(ω)*sin(ω)`, which are both saved into a matrix and output to a file at completion of the program. Then we graph x vs t, y vs t, and x vs y using the following Python script:

    # Conrad Appel
    # MATH3316
    # Oct 7 2014
    
    from pylab import *
    
    x = loadtxt('x.txt')
    y = loadtxt('y.txt')
    t = loadtxt('t.txt')
    
    figure(1)
    plot(t, x)
    xlabel('t')
    ylabel('x(t)')
    title('t vs x(t)')
    savefig('./x_vs_t.png', bbox_inches='tight')
    
    figure(2)
    plot(t, y)
    xlabel('t')
    ylabel('y(t)')
    title('t vs y(t)')
    savefig('./y_vs_t.png', bbox_inches='tight')
    
    figure(3)
    plot(x, y)
    xlabel('x(t)')
    ylabel('y(t)')
    title('x(t) vs y(t)')
    savefig('./y_vs_x.png', bbox_inches='tight')
    
    show()

This first graph shows the x coordinates of the object over a period of time. It is periodic because the `x(t)` function is based on `cos`.

![x(t) vs t](/home/conrad/Development/MATH3316/project2/x_vs_t.png)

This next graph shows the y coordinates of the object over a period of time. It also follows a periodic pattern because `y(t)` is based on the `sin` function.

![y(t) vs t](/home/conrad/Development/MATH3316/project2/y_vs_t.png)

When the x and y coordinates are used to make one graph, they form an elipse because both are periodic, which is what we would expect due to us trying to find the position of an object in an elliptical orbit.

![y(t) vs x(t)](/home/conrad/Development/MATH3316/project2/y_vs_x.png)

In the end, we were successful in plotting the position the position of an object in an elliptical orbit using the tools we built in part 1.
