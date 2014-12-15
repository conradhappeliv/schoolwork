// Conrad Appel
// MATH 3316
// Nov 4 2014

#include "mat.h"
#include "newton_interp.cpp"
#include "lagrange.cpp"

#include <cmath>
#include <chrono>

// used to easily run the Lagrange method with differing values of n and m
void testLagrange(unsigned int n, Mat& x, Mat& y, Mat& z) {
    Mat p(z.Size());
    for(unsigned int i = 0; i < z.Size(); i++) {
        lagrange(x, y, z(i));
    }
}

// used to easily run Newton's method with differing values of n and m
void testNewton(unsigned int n, Mat& x, Mat& y, Mat& z) {
    Mat p(z.Size());
    Mat c(n+1);
    newton_coeffs(x, y, c);
    for(int i = 0; i < z.Size(); i++) {
        p(i) = newton_eval(x, c, z(i));
    }
}

int main()
{
    unsigned int n_possible[4] = {5, 10, 20, 40}; // possible number of nodes
    unsigned int m_possible[4] = {500, 5000, 50000, 500000}; // possible number of evaluation points
    for(unsigned int i = 0; i < 4; i++) {
        for(unsigned int j = 0; j < 4; j++) {
            unsigned int n = n_possible[i];
            unsigned int m = m_possible[j];

            Mat x = Linspace(-1, 1, n+1);
            Mat y(n+1);
            for(unsigned int k = 0; k < n+1; k++) {
                y(k) = std::sinh(std::pow(x(k), 3)/2.0); // evaluate the function at all nodes
            }
            Mat z = Linspace(-1, 1, m+1);

            // time the evaluation time of running the Lagrange method at selected n and m
            auto start = std::chrono::system_clock::now();
            testLagrange(n, x, y, z);
            auto stop = std::chrono::system_clock::now();
            double LGTime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();

            // time the evaluation time of running the Newton method at selected n and m
            start = std::chrono::system_clock::now();
            testNewton(n, x, y, z);
            stop = std::chrono::system_clock::now();
            double NewTime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();

            std::cout << "With n = " << n << " and m = " << m << ": " << std::endl;
            std::cout << '\t' << "Lagrange time: " << LGTime*1e-6 << " milliseconds" << std::endl;
            std::cout << '\t' << "Newton time:   " << NewTime*1e-6 << " milliseconds" << std::endl;
            std::cout << std::endl;
        }
    }

    return 0;
}
