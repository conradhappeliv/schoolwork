Project 4 - Numerical Integration
=================================

Conrad Appel - 12/02/2014 - MATH 3316

In this project, I will design a function used to approximate an integral over a given interval with a certain number of subintervals. Then, in an effort to reduce wasted computational effort, I will create another method that only calls the first method up until a certain number of intervals, determined by the accuracy gain between two subsequent calculations. Then, using this more efficient implementation, I will attempt to model concentrations of carbon relative to iron in an alloy during the process of carburizing. Finally, using this model, I should be able solve a given problem of finding a time needed to reach a certain concentration with certain given variables.

*Program outputs, code, and plots are all organized in the appendices at the end of the document.*

Part 1: High-order Numerical Integration
----------------------------------------

Code for this part:
* ./composite_int.cpp
* ./test_int.cpp

In this first section, I need to inplement an algorithm for approximating an integral with a convergence rate of at least h^7. I then wrote a test used to affirm that said implementation actually reaches that rate of convergence.

After testing out a few different methods of composite numerical integration, I settled on the four-node Newton method explained in the textbook, which allowed me to achieve the required rate of convergence while still maintaining the smallest necessary amount of computational effort. I was also able to use much smaller values of n than the given Gauss method because this method of numerical integration is able to converge much quicker than the methods with less nodes.

Part 2: Adaptive Numerical Integration
---------------------------------------

Code for this part:
* ./adaptive_int.cpp
* ./test_adapt.cpp

In the second part of the project, I utilized the `composite_int` function created in part one in a way to reach a certain level of accuracy without using unnecessary computational power. To achieve this goal, this `adaptive_int` function would call `composite_int()` with increasing numbers of `n`, stopping when the increase in accuracy is less than a combination of given relative and absolute tolerances. In doing so, we save ourselves from under-guessing or over-guessing the "correct" value of `n`. 

However, there are potential problems with using this method over the simple `composite_int` method. First, finding the ideal value of `n` requires calling `composite_int` a number of times until the desired accuracy is found. Along the way, the total number of intervals the `composite_int` function needs to calculate on could greatly surpass the final value of n used. Another issue arises if the `composite_int` method used within has trouble converging quickly enough or at all. For these cases, I added a line of code that would end the function at a certain number of n, in an attempt to stop the loop from running infinitely or for an unreasonable amount of time. Even with this workaround, it could take a relatively large amount of time and effort to reach the set limit, and the effort would probably be wasted in the end.

An implementation problem I ran into was deciding a value `k` to increase `n` by during each iteration. If `k` was a small constant value, it would most likely take far too long to reach the ideal `n`, whereas if k were a large constant, it would be very easy to overshoot the value of `n` and need to do unnecessary work. Since there is no one "magic" `k` value, I decided to use a `k` value proportional to the current `n` value. I chose this method because at a small `n`, it would increase on the next iteration by a small `k`, and at a larger `n` value, it would increase by a proportionally larger `k`. This method would resolve the issue of having a large `k` cause earth-shatteringly large effects on a small `n` or an increase of a small `k` on a large `n` having next to no effect. This method of choosing a `k` additionally better represents the `adaptive` attribute of this method of integration.

*Side note: The value of k could probably be better chosen by comparing the error in the current iteration to the desired error and setting the `k/n` according to the comparison. I did not get a chance to experiment with this.*

When running the `adaptive_int` method using the `test_adapt.cpp` driver (figure A:./test_adapt.out), I was able to demonstrate both the benefits and shortcomings of using this method. Like I expected, the method was indeed able to achieve an accuracy calculated with given relative and absolute tolerances, and was able to do so with only a small overhead from finding the ideal `n`. At its worst in these trials, the method needed only 1415 additional calculated `n`s to reach the desired accuracy with `n = 250`. While experimenting with fixed proportions of `k/n`, I noticed that a smaller proportion was better for more tolerant accuracies and for finding the value of n that causes the error to match the desired accuracy most closely. A 1:1 proportion seemed to work most efficiently (required the least `nTot`) while still closely matching the desired accuracy in general. However, no matter how efficient the method is, it always requires extra work. It does save work in the long run because we have no better way of determining the ideal value of `n`.

Part 3: Application
-------------------

Code for this part:
* ./carbon.cpp
* ./test_carbon.cpp
* ./carbon.py

In this section, I needed to apply the integration methods to a real problem. The problem given is to create a model of the the concentration of carbon in an alloy during the process of carburization, where I need to approximate an integral in the error function (*erf*) with the `adaptive_int` method. This model is implemented in the `./carbon.cpp` file. The only implementation issue I ran into was when the `t` parameter was less than or equal to zero. In that case, I returned the initial concentration of carbon, `C0`.

I also created a test driver, `./test_carbon.cpp`, which demonstrates the usage of the model with a variety of different parameters (depth, time, and temperature). The first of these is an array of depths linearly spaced from 0-4 mm and times linearly spaced from 0-48 hours, with a fixed temperature of 900 K. The second is the same test, with a temperature of 1100 K. The third test holds the time still at 1, 6, 12, 24, and 48 hours with a temperature of 900 K and with x from 0-4 mm. The fourth is the same as the third, but with a temperature of 1100 K. All tests output their results to files, which are loaded in the Python script `./carbon.py` and then graphed. The first two are graphed as contour plots, and the third and fourth are graphed as overlayed lines (one for each time). All four graphs are displayed and explained in Appendix C.

Part 4: Problem
---------------

Code for this part:
* ./application.cpp
* ./steffensen.cpp (adapted from project 2)

In this final section of the project, I used the carburization model from the previous section to find the time at which an alloy reaches a certain carbon concentration with other parameters fixed. Because the second MATH 3316 project required us to implement root-finding solvers, it would be easy for me to repurpose said solvers to solve this problem for me.

Out of the Newton and Steffensen root-finders, I chose to use Steffensen's method because Newton's method requires a given derivative, and the carburization model seems very difficult to find the derivative. To make a valid root-solvable problem, I had to rearrange the problem as such (called `solve_me()` in `./application.cpp`):

    carbon(.002 m, t, 1000 K) = .5%
    f(t) = carbon(.002, t, 1000) - .005
    solve f(t) = 0

I needed to decide on an initial guess for the Steffensen solver to start at. Looking at the contour graphs for T = 900 K and 1100 K where x = 2 mm, it seems like a concentration of .5% occurs at about t = 20 hours and 0 hours, respectively. Because the problem's temperature of 1000 K falls between the temperatures of the two aforementioned models, I figured taking the average of the two eyeballed values of t would lead to a good guess. Therefore, I used t = 10 hours or 36000 seconds as the initial guess in the Steffensen solver.

When solved using the Steffensen function, a result of 39079.0575545 seconds is found for the value of `t` (accurate to the microsecond). When plugged back into the model to check, it does indeed produce a resulting concentration of .5%, as I expected.


Appendix A: Code Output
-----------------------

`./test_int.out`

    True integral value = 6.5033551341673331e+01
    
    Composite Numerical Integration Approximation:
            6  6.4871424830042372e+01  2.5e-03     ----
           12  6.4958352643429464e+01  1.2e-03   1.108340
           24  6.5034198198284486e+01  9.9e-06   6.861118
           36  6.5033499697655969e+01  7.9e-07   6.234199
           48  6.5033549618853030e+01  2.6e-08   11.820033
           60  6.5033551131199360e+01  3.2e-09   9.421540
           72  6.5033551299509654e+01  6.5e-10   8.818501
           84  6.5033551330378131e+01  1.7e-10   8.544765
           96  6.5033551337990318e+01  5.7e-11   8.392383
          108  6.5033551340287318e+01  2.1e-11   8.297458



`./test_adapt.out`

    True integral value = 6.5033551341673331e+01
    
        rtol     atol      n    nTot        R         |I(f)-R(f)|  rtol|I(f)|+atol
      1.0e-02 | 1.0e-05 |  20 |    35 | 6.503599e+01 |  2.4e-03  |   6.5e-01
      1.0e-04 | 1.0e-07 |  40 |    95 | 6.503354e+01 |  1.2e-05  |   6.5e-03
      1.0e-06 | 1.0e-09 |  80 |   215 | 6.503355e+01 |  1.7e-08  |   6.5e-05
      1.0e-08 | 1.0e-11 | 160 |   455 | 6.503355e+01 |  5.6e-11  |   6.5e-07
      1.0e-10 | 1.0e-13 | 320 |   935 | 6.503355e+01 |  2.0e-13  |   6.5e-09
      1.0e-12 | 1.0e-15 | 320 |   935 | 6.503355e+01 |  2.0e-13  |   6.5e-11
    



`./carbon.out`

    no output


`./application.out`

    Result: 
    	39079.0574377 seconds
    	10 hours, 51 minutes, 19.0574377 seconds
    	carbon(0.002 m, 39079.057 s, 1000.000 K) = 0.005



Appendix B: Code
----------------

`./Makefile`

    # Conrad Appel
    # MATH 3316
    # 2 Dec 2014
    
    all: test_int test_adapt carbon application
    
    test_int:
    	g++ -std=c++11 test_int.cpp mat.cpp -o test_int.out
    
    test_adapt:
    	g++ -std=c++11 test_adapt.cpp mat.cpp -o test_adapt.out
    
    carbon:
    	g++ -std=c++11 test_carbon.cpp mat.cpp -o carbon.out
    
    application:
    	g++ -std=c++11 application.cpp mat.cpp -o application.out
    
    clean:
    	rm -f *.out *.txt *.png



`./adaptive_int.cpp`

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



`./application.cpp`

    // Conrad Appel
    // MATH 3316
    // 2 Dec 2014
    
    #include "carbon.cpp"
    #include "mat.h"
    #include "steffensen.cpp"
    
    #include <iomanip> // setprecision, fixed
    
    // problem constants
    const double rtoler = 1e-14;
    const double atoler = 1e-15;
    const double depth = .002; // m
    const double temperature = 1e3; // Kelvin
    
    // t is the answer when this function
    // is 0 (root-finding problem).
    // basically a reconfiguration of C(x, t, T) = .5%
    double solve_me(const double t) {
        return carbon(depth, t, temperature, rtoler, atoler)-.005;
    }
    
    int main() {
        // use root-finder to solve for the correct value of t
        double time = steffensen(solve_me, 36000, 10000, 1e-6);
    
        // calculate different units for output
        int hours = time/3600;
        int minutes = (time - hours*3600)/60;
        double seconds = time - hours*3600 - minutes*60;
    
        // output
        std::cout << "Result: " << std::endl;
            std::cout << '\t' << std::setprecision(7) << std::fixed << time << " seconds" << std::endl;
            std::cout << '\t' << hours << " hours, " << minutes << " minutes, " << std::setprecision(7) << std::fixed << seconds << " seconds" << std::endl;
            std::cout << '\t' << std::setprecision(3) << "carbon(" << depth << " m, " << time <<" s, " << temperature << " K) = " << carbon(depth, time, temperature, rtoler, atoler) << std::endl;
    }



`./carbon.cpp`

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
    



`./carbon.py`

    # Conrad Appel
    # MATH 3316
    # 2 Dec 2014
    
    from pylab import *
    
    x = loadtxt('./x.txt')
    t = loadtxt('./t.txt')
    c900 = loadtxt('./c900.txt')
    c900_1 = loadtxt('./c900_1hour.txt')
    c900_6 = loadtxt('./c900_6hour.txt')
    c900_12 = loadtxt('./c900_12hour.txt')
    c900_24 = loadtxt('./c900_24hour.txt')
    c900_48 = loadtxt('./c900_48hour.txt')
    c1100 = loadtxt('./c1100.txt')
    c1100_1 = loadtxt('./c1100_1hour.txt')
    c1100_6 = loadtxt('./c1100_6hour.txt')
    c1100_12 = loadtxt('./c1100_12hour.txt')
    c1100_24 = loadtxt('./c1100_24hour.txt')
    c1100_48 = loadtxt('./c1100_48hour.txt')
    
    figure(1)
    imshow(c900, extent=[0, 4, 0, 48], aspect='auto')
    xlabel('x (mm)')
    ylabel('t (hours)')
    title('Carbon Concentration at (x, t) with T = 900 K')
    colorbar(orientation='horizontal')
    savefig('c900.png')
    
    figure(2)
    imshow(c1100, extent=[0, 4, 0, 48], aspect='auto')
    xlabel('x (mm)')
    ylabel('t (hours)')
    title('Carbon Concentration at (x, t) with T = 1100 K')
    colorbar(orientation='horizontal')
    savefig('c1100.png')
    
    figure(3)
    plot(x, c900_1, label='1 hour')
    plot(x, c900_6, label='6 hours')
    plot(x, c900_12, label='12 hours')
    plot(x, c900_24, label='24 hours')
    plot(x, c900_48, label='48 hours')
    xlabel('x (m)')
    ylabel('C(x)')
    title('Carbon Concentrations; T = 900K; Varying t')
    legend(loc='upper right')
    savefig('c900_fixedt.png')
    
    figure(4)
    plot(x, c1100_1, label='1 hour')
    plot(x, c1100_6, label='6 hours')
    plot(x, c1100_12, label='12 hours')
    plot(x, c1100_24, label='24 hours')
    plot(x, c1100_48, label='48 hours')
    xlabel('x (m)')
    ylabel('C(x)')
    title('Carbon Concentrations; T = 1100K; Varying t')
    legend(loc='upper right')
    savefig('c1100_fixedt.png')
    
    show()


`./composite_int.cpp`

    // Conrad Appel
    // MATH 3316
    // 2 Dec 2014
    
    #include <cmath>
    
    #include "mat.h"
    
    // all of these calculations moved outside functions for efficiency
    const double node1 = std::sqrt(1.0/7*(3 - 4 * std::sqrt(.3))) * .5;
    const double node2 = std::sqrt(1.0/7*(3 + 4 * std::sqrt(.3))) * .5;
    const double weight1 = .5 + 1.0/12*std::sqrt(10.0/3);
    const double weight2 = .5 - 1.0/12*std::sqrt(10.0/3);
    
    double newton4(double (*f)(const double), const double left, double h) {
        double midpoint = left + h/2; // of current subinterval
        double x0, x1, x2, x3;
        // calculate position of nodes
        x0 = midpoint - h * node1;
        x1 = midpoint - h * node2;
        x2 = midpoint + h * node1;
        x3 = midpoint + h * node2;
    
        // nodes * respective weights
        return weight1*f(x0)
              +weight2*f(x1)
              +weight1*f(x2)
              +weight2*f(x3);
    }
    
    // integrates f from [a, b] with n subintervals
    double composite_int(double (*f)(const double), const double a, const double b, const int n) {
        const double h = (b - a) / n; // length of subinterval
        double sum = 0; // sum of all subintervals
        for(unsigned int i = 0; i < n; i++) {
            sum += newton4(f, a + i*h, h);
        }
        return sum*h*.5;
    }



`./steffensen.cpp`

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



`./test_adapt.cpp`

    // Conrad Appel
    // MATH 3316
    // 2 Dec 2014
    
    #include <iostream>
    #include <cmath>
    
    #include "mat.h"
    #include "adaptive_int.cpp"
    
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
    
        // test values
        double rtols[] = { 1e-2, 1e-4, 1e-6, 1e-8, 1e-10, 1e-12 };
        double atols[] = { 1e-5, 1e-7, 1e-9, 1e-11, 1e-13, 1e-15 };
    
        std::cout << "    rtol     atol      n    nTot        R         |I(f)-R(f)|  rtol|I(f)|+atol" << std::endl;
        for(unsigned int i = 0; i < 6; i++) { // for each pair of tols
            double R;
            int n, nTot = 0;
            adaptive_int(f, a, b, rtols[i], atols[i], R, n, nTot);
            double err = std::abs(trueVal - R);
            double errBound = rtols[i] * std::abs(trueVal) + atols[i];
            printf("  %2.1e | %2.1e | %3u | %5u | %12.6e |  %7.1e  |   %7.1e\n", rtols[i], atols[i], n, nTot, R, err, errBound);
        }
        std::cout << std::endl;
    }



`./test_carbon.cpp`

    // Conrad Appel
    // MATH 3316
    // 2 Dec 2014
    
    #include "carbon.cpp"
    
    // given
    const double rtoler = 1e-12;
    const double atoler = 1e-14;
    
    int main() {
        Mat x = Linspace(0, .004, 300); // m
        Mat t = Linspace(0, 172800, 500); // seconds
        Mat c900 = Mat(300, 500); // test one
        Mat c1100 = Mat(300, 500); // test two
        Mat c900_1 = Mat(300); // start of test three
        Mat c900_6 = Mat(300);
        Mat c900_12 = Mat(300);
        Mat c900_24 = Mat(300);
        Mat c900_48 = Mat(300);
        Mat c1100_1 = Mat(300); // start of test four
        Mat c1100_6 = Mat(300);
        Mat c1100_12 = Mat(300);
        Mat c1100_24 = Mat(300);
        Mat c1100_48 = Mat(300);
    
        // c900
        for(unsigned int i = 0; i < 300; i++)
            for(unsigned int j = 0; j < 500; j++)
                c900(i, j) = carbon(x(i), t(j), 900, rtoler, atoler);
        // c1100
        for(unsigned int i = 0; i < 300; i++)
            for(unsigned int j = 0; j < 500; j++)
                c1100(i, j) = carbon(x(i), t(j), 1100, rtoler, atoler);
        // c900_1hour
        for(unsigned int i = 0; i < 300; i++)
            c900_1(i) = carbon(x(i), 3600, 900, rtoler, atoler);
        // c900_6hour
        for(unsigned int i = 0; i < 300; i++)
            c900_6(i) = carbon(x(i), 21600, 900, rtoler, atoler);
        // c900_12hour
        for(unsigned int i = 0; i < 300; i++)
            c900_12(i) = carbon(x(i), 43200, 900, rtoler, atoler);
        // c900_24hour
        for(unsigned int i = 0; i < 300; i++)
            c900_24(i) = carbon(x(i), 86400, 900, rtoler, atoler);
        // c900_48hour
        for(unsigned int i = 0; i < 300; i++)
            c900_48(i) = carbon(x(i), 172800, 900, rtoler, atoler);
        // c1100_1hour
        for(unsigned int i = 0; i < 300; i++)
            c1100_1(i) = carbon(x(i), 3600, 1100, rtoler, atoler);
        // c1100_6hour
        for(unsigned int i = 0; i < 300; i++)
            c1100_6(i) = carbon(x(i), 21600, 1100, rtoler, atoler);
        // c1100_12hour
        for(unsigned int i = 0; i < 300; i++)
            c1100_12(i) = carbon(x(i), 43200, 1100, rtoler, atoler);
        // c1100_24hour
        for(unsigned int i = 0; i < 300; i++)
            c1100_24(i) = carbon(x(i), 86400, 1100, rtoler, atoler);
        // c1100_48hour
        for(unsigned int i = 0; i < 300; i++)
            c1100_48(i) = carbon(x(i), 172800, 1100, rtoler, atoler);
    
        // write to files
        x.Write("./x.txt");
        t.Write("./t.txt");
        c900.Write("./c900.txt");
        c1100.Write("./c1100.txt");
        c900_1.Write("./c900_1hour.txt");
        c900_6.Write("./c900_6hour.txt");
        c900_12.Write("./c900_12hour.txt");
        c900_24.Write("./c900_24hour.txt");
        c900_48.Write("./c900_48hour.txt");
        c1100_1.Write("./c1100_1hour.txt");
        c1100_6.Write("./c1100_6hour.txt");
        c1100_12.Write("./c1100_12hour.txt");
        c1100_24.Write("./c1100_24hour.txt");
        c1100_48.Write("./c1100_48hour.txt");
    }



`./test_int.cpp`

    // Conrad Appel
    // MATH 3316
    // 2 Dec 2014
    
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
        int n[] = {6, 12, 24, 36, 48, 60, 72, 84, 96, 108};
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



Appendix C: Plots
-----------------

![](/home/conrad/Development/MATH3316/project4/c900.png)
Figure 1: Contour plot showing the carbon concentration in an alloy over time or at different depths with a fixed temperature of 900 K.

Note that on the surface of the steal, the carbon concentration approaches that of the gas almost instantly whereas it takes longer for the carbon to percolate the greater depths of the steel.

![](/home/conrad/Development/MATH3316/project4/c1100.png)
Figure 2: Contour plot showing the carbon concentration in an alloy over time or at different depths with a fixed temperature of 1100 K.

Comparing figure 1 and figure 2, it seems that with a greater temperature, the carbon diffuses down deeper into the steel much more quickly. This is due to the temperature-dependent diffusion coefficient for steel becoming larger as T becomes larger.

![](/home/conrad/Development/MATH3316/project4/c900_fixedt.png)
Figure 3: Carbon concentrations with varying depths, fixed times along individual lines, and a fixed temperature of 900 K.

Looking at this graph, it's obvious that carbon concentrations in the steel are always closer to that of the gas the more time has passed (visually, the lines with greater times are always above those with less time).

![](/home/conrad/Development/MATH3316/project4/c1100_fixedt.png)
Figure 4: Carbon concentrations with varying depths, fixed times along individual lines, and a fixed temperature of 1100 K.

Once again comparing this and the previous graph, the trials with greater temperatures more quickly approaches the gas's concentration (the same lines in this trial are higher than in the previous trial).



