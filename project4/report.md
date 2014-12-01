Project 4 - Numerical Integration
=================================

Conrad Appel - 12/02/2014 - MATH 3316

In this project, I will design a function used to approximate an integral over a given interval with a certain number of subintervals. Then, in an effort to reduce wasted computational effort, I will create another method that only calls the first method up until a certain number of intervals, determined by the accuracy gain between two subsequent calculations. Then, using this more efficient implementation, I will attempt to model concentrations of carbon relative to iron in an alloy during the process of carburizing. Finally, using this model, I should be able solve a given problem of finding a time needed to reach a certain concentration with certain given variables.

Part 1: High-order Numerical Integration
----------------------------------------

In this first section, I need to inplement an algorithm for approximating an integral with a convergence rate of at least h^7.

Part 2: Adaptive Numerical Integration
---------------------------------------


Part 3: Application
-------------------


Part 4: Problem
---------------



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
      1.0e-04 | 1.0e-07 |  26 |    81 | 6.503399e+01 |  4.4e-04  |   6.5e-03
      1.0e-06 | 1.0e-09 |  60 |   325 | 6.503355e+01 |  2.1e-07  |   6.5e-05
      1.0e-08 | 1.0e-11 |  80 |   465 | 6.503355e+01 |  1.7e-08  |   6.5e-07
      1.0e-10 | 1.0e-13 | 141 |   898 | 6.503355e+01 |  1.6e-10  |   6.5e-09
      1.0e-12 | 1.0e-15 | 250 |  1665 | 6.503355e+01 |  1.5e-12  |   6.5e-11
    



`./carbon.out`




`./application.out`

    Result: 
    	30 seconds
    	0 hours, 0 minutes, 30 seconds



Appendix B: Code
----------------

`./adaptive_int.cpp`

    #include <cmath>
    
    #include "composite_int.cpp"
    
    int adaptive_int(double (*f)(const double), const double a, const double b, const double rtol, const double atol, double& R, int& n, int& nTot) {
        int k = 5;
        n = 15;
        double cur, next;
        next = composite_int(f, a, b, n);
        do {
            if(n >= 10000000) return 1;
            nTot += 2*n + k;
            cur = next;
            n = n + k;
            next = composite_int(f, a, b, n);
            k = n/3;
        } while(std::abs(next-cur) >= (rtol*std::abs(next) + atol));
        R = next;
        return 0;
    }



`./application.cpp`

    #include "carbon.cpp"
    #include "mat.h"
    
    
    const double rtoler = 1e-14;
    const double atoler = 1e-15;
    
    int main() {
        const double depth = 2; // mm
        const double temperature = 1e3; // Kelvin
        double time = 30; // seconds
    
        //carbon(depth, time, temperature, rtoler, atoler);
    
        std::cout << "Result: " << std::endl;
            std::cout << '\t' << time << " seconds" << std::endl;
            std::cout << '\t' << (int) time/3600 << " hours, " << (int) time/60 << " minutes, " << ((int) time)%60 << " seconds" << std::endl;
    }



`./carbon.cpp`

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
        }, 0, y, 2500);*/
        adaptive_int([](const double z){
            return std::exp(-(z*z));
        }, 0, y, rtol, atol, R, n, nTot);
        R *= 2.0/std::sqrt(PI);
        return R;
    }
    
    double D(const double T) {
        return 6.2e-7*std::exp(-8e4/(8.31*T));
    }
    
    double carbon(const double x, const double t, const double T, const double rtol, const double atol) {
        return Cs - (Cs-C0)*erf((x/std::sqrt(4*t*D(T))), rtol, atol);
    }
    



`./carbon.py`

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
    imshow(c900)
    xlabel('x')
    ylabel('t')
    colorbar(orientation='horizontal')
    savefig('c900.png')
    
    figure(2)
    imshow(c1100)
    xlabel('x')
    ylabel('t')
    colorbar(orientation='horizontal')
    savefig('c1100.png')
    
    figure(3)
    plot(x, c900_1)
    plot(x, c900_6)
    plot(x, c900_12)
    plot(x, c900_24)
    plot(x, c900_48)
    savefig('c900_fixedt.png')
    
    figure(4)
    plot(x, c1100_1)
    plot(x, c1100_6)
    plot(x, c1100_12)
    plot(x, c1100_24)
    plot(x, c1100_48)
    savefig('c1100_fixedt.png')
    
    show()


`./composite_Gauss2.cpp`

    /* Daniel R. Reynolds
       SMU Mathematics
       Math 3316
       28 October 2014 */
    
    // Inclusions
    #include <stdlib.h>
    #include <stdio.h>
    #include <iostream>
    #include <math.h>
    
    using namespace std;
    
    // This routine numerically approximates the integral
    //    int_a^b fun(x) dx
    // using the composite Gaussian quadrature rule with 2 points per 
    // subinterval (i.e. O(h^4) accurate), over n subintervals.  We 
    // require that fun have the calling syntax 
    //    y = fun(x)
    // where y is a double and x is a const double.
    //
    // Usage: F = composite_Gauss2(fun, a, b, n);
    //
    // inputs:   fun     integrand
    //           a       lower limit of integration
    //           b       upper limit of integration
    //           n       number of subintervals
    //
    // outputs:  F       value of numerical integral
    // 
    double composite_Gauss2(double (*f)(const double), const double a, 
    			const double b, const int n)
    {
    
      // check input arguments
      if (b < a) {
        cerr << "error: illegal interval, b < a\n";
        return 0.0;
      }
      if (n < 1) {
        cerr << "error: illegal number of subintervals, n < 1\n";
        return 0.0;
      }
    
      // set subinterval width
      double h = (b-a)/n;
    
      // set nodes/weights defining the quadrature method
      double x1 = -sqrt(1.0/3.0);
      double x2 =  sqrt(1.0/3.0);
      double w1 =  1.0;
      double w2 =  1.0;
    
      // initialize result
      double F = 0.0;
    
      // loop over subintervals, accumulating result
      double xmid, node1, node2;
      for (int i=0; i<n; i++) {
       
        // determine evaluation points within subinterval
        xmid  = a + (i+0.5)*h;
        node1 = xmid + 0.5*h*x1;
        node2 = xmid + 0.5*h*x2;
    
        // add Gauss2 approximation on this subinterval to result
        F += w1*f(node1) + w2*f(node2);
    
      } // end loop
    
      // return final result
      return (0.5*h*F);
    
    } // end of function



`./composite_int.cpp`

    #include <cmath>
    
    #include "mat.h"
    
    double newton4(double (*f)(const double), const double left, double h) {
        double midpoint = left + h/2;
        double x0, x1, x2, x3;
        x0 = midpoint - .5*h * std::sqrt(1.0/7*(3 - 4 * std::sqrt(.3)));
        x1 = midpoint - .5*h * std::sqrt(1.0/7*(3 + 4 * std::sqrt(.3)));
        x2 = midpoint + .5*h * std::sqrt(1.0/7*(3 - 4 * std::sqrt(.3)));
        x3 = midpoint + .5*h * std::sqrt(1.0/7*(3 + 4 * std::sqrt(.3)));
    
        return (  (.5 + 1.0/12*std::sqrt(10.0/3))*f(x0)
                + (.5 - 1.0/12*std::sqrt(10.0/3))*f(x1)
                + (.5 + 1.0/12*std::sqrt(10.0/3))*f(x2)
                + (.5 - 1.0/12*std::sqrt(10.0/3))*f(x3));
    }
    
    double composite_int(double (*f)(const double), const double a, const double b, const int n) {
        const double h = (b - a) / n;
        double sum = 0;
        for(unsigned int i = 0; i < n; i++) {
            sum += newton4(f, a + i*h, h);
        }
        return sum*h*.5;
    }



`./test_adapt.cpp`

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
    
        double rtols[] = { 1e-2, 1e-4, 1e-6, 1e-8, 1e-10, 1e-12 };
        double atols[] = { 1e-5, 1e-7, 1e-9, 1e-11, 1e-13, 1e-15 };
        //adaptive_int(f, a, b, rtol, atol, R, n, nTot);
    
        std::cout << "    rtol     atol      n    nTot        R         |I(f)-R(f)|  rtol|I(f)|+atol" << std::endl;
        for(unsigned int i = 0; i < 6; i++) { // for each pair of tols
            double R;
            int n, nTot = 0;
            int res = adaptive_int(f, a, b, rtols[i], atols[i], R, n, nTot);
            double err = std::abs(trueVal - R);
            double errBound = rtols[i] * std::abs(trueVal) + atols[i];
            printf("  %2.1e | %2.1e | %3u | %5u | %12.6e |  %7.1e  |   %7.1e\n", rtols[i], atols[i], n, nTot, R, err, errBound);
        }
        std::cout << std::endl;
    }



`./test_carbon.cpp`

    #include "carbon.cpp"
    
    const double rtoler = 1e-12;
    const double atoler = 1e-14;
    
    int main() {
        Mat x = Linspace(0, 4, 300);
        Mat t = Linspace(0, 48, 500);
        Mat c900 = Mat(300, 500);
        Mat c1100 = Mat(300, 500);
        Mat c900_1 = Mat(300);
        Mat c900_6 = Mat(300);
        Mat c900_12 = Mat(300);
        Mat c900_24 = Mat(300);
        Mat c900_48 = Mat(300);
        Mat c1100_1 = Mat(300);
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

![](/home/conrad/Development/MATH3316/project4/c1100.png)
Figure 1:

![](/home/conrad/Development/MATH3316/project4/c1100_fixedt.png)
Figure 2:

![](/home/conrad/Development/MATH3316/project4/c900.png)
Figure 3:

![](/home/conrad/Development/MATH3316/project4/c900_fixedt.png)
Figure 4:

