/* Daniel R. Reynolds
   SMU Mathematics
   Math 3316
   5 October 2014 */

// Inclusions
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "mat.h"

using namespace std;


// Utility function to evaluate a given Lagrange basis function at a point, phi_i(z).
//
// Usage: l = lagrange_basis(x, i, z);
//
// inputs:   x     Mat vector of length n+1, containing the interpolation nodes
//           i     integer indicating which Lagrange basis function to evaluate
//           z     double location to evaluate basis function
// outputs:  p     value of phi_i(z)
// 
double lagrange_basis(Mat &x, int i, double z) {
  double l = 1.0;              // initialize basis function
  double *xd = x.get_data();   // access data array (for increased speed)
  for (int j=0; j<x.Size(); j++)
     if (j != i)  l *= (z - xd[j]) / (xd[i] - xd[j]);
  return l;
}



// This routine evaluates the Lagrange interpolating polynomial, 
// defined over a set of data points (x_i,y_i), i=0,...,n, at a point z.
//
// Usage: p = lagrange(x, y, z);
//
// inputs:   x     Mat vector of length n+1, containing the interpolation nodes
//           y     Mat vector of length n+1, containing the interpolation data
//           z     double location to evaluate polynomial
// outputs:  p     value of p(z)
// 
double lagrange(Mat &x, Mat &y, double z) 
{

  // check input arguments (lengths of x and y)
  if (x.Size() != y.Size()) {
    cerr << "lagrange error: x and y have different lengths!\n";
    return 0.0;
  }

  // evaluate p
  double p = 0.0;                       // initialize result
  for (int i=0; i<x.Size(); i++)        // loop over data values
    p += y(i)*lagrange_basis(x, i, z);  // update result with next term

  // return final result
  return p;

} // end of function
