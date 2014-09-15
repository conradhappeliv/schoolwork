/* Conrad Appel
 * MATH3316
 * 9/16/14
 */

#include "mat.h"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// f'(5) = (-2)*5^(-3) = -0.016
const double fPrime5 = -0.016;

// f'' = 6*x^-4
// f''(5) = .0096
const double fDoublePrime5 = .0096;

int main() {
    // δ−f(5)
    Mat h = Mat(1, 52);
    Mat n = Mat(1, 52);
    Mat r = Mat(1, 52);
    Mat R = Mat(1, 52);
    for(int i = 0; i < 52; i++) {
        // using equation (1) for backwards difference of f'(a) where a is 5 and h is 2^-(1, 2, ..., 52)
        h(i) = pow(2,-(i+1));
        n(i) = (pow(5, -2) - pow(5-h(i), -2)) / h(i);

        // TODO: delete one
        // errors
        // guess 1: f''(a)/2*h
        r = fDoublePrime5 * h(i);

        //guess 2: (f0 - f) / f0
        //r = (fPrime5 - backDiffFPrime5(i)) / fPrime5;

        // f''(5)/2/f'(5) = -0.3
        //f(5) * eDP / f'(5) = 5^-2 * 2^-52 / -0.016 = -5.5511151 * 10^-16
        R(i) = (-0.3)*h(i) + (-5.5511151 * pow(10, -16))*(1/h(i));
    }

    h.Write("../h.txt");
    n.Write("../n.txt");
    r.Write("../r.txt");
    R.Write("../R.txt");

    return 0;
}
