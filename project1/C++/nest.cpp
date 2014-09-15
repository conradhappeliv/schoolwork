/* Conrad Appel
 * MATH3316
 * 9/16/14
 */

#include "mat.h"

#include <iostream>

double nest(Mat &a, double x) {
    /*double sum = 0;
    for(int i = a.Cols()-1; i > 0; i--) {
        sum += a(i);
        sum *= x;
    }
    sum += a(0);
    return sum;*/
    int n = a.Cols()-1;
    double p = a(n);
    for(int i = n - 1; i >= 0; i--) {
        p = a(i) + x*p;
    }
    return p;
}
