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
