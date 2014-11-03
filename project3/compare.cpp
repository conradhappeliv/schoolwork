#include "mat.h"
#include "newton_interp.cpp"
#include "lagrange.cpp"

#include <cmath>
#include <chrono>

void testLagrange(unsigned int n, Mat& x, Mat& y, Mat& z) {
    Mat p(n);
    for(unsigned int i = 0; i < n; i++) {
        lagrange(x, y, z(i));
    }
}

void testNewton(unsigned int n, Mat& x, Mat& y, Mat& z) {
    Mat p(n);
    Mat c(n+1);
    newton_coeffs(x, y, c);
    for(int i = 0; i < n; i++) {
        p(i) = newton_eval(x, c, z(i));
    }
}

int main()
{
    unsigned int n_possible[4] = {5, 10, 20, 40};
    unsigned int m_possible[4] = {500, 5000, 50000, 500000};
    for(unsigned int i = 0; i < 4; i++) {
        for(unsigned int j = 0; j < 4; j++) {
            unsigned int n = n_possible[i];
            unsigned int m = m_possible[j];

            Mat x = Linspace(-1, 1, n+1);
            Mat y(n+1);
            for(unsigned int k = 0; k < n+1; k++) {
                y(k) = std::sinh(std::pow(x(k), 3)/2.0);
            }
            Mat z = Linspace(-1, 1, m+1);

            auto start = std::chrono::system_clock::now();
            testLagrange(n, x, y, z);
            auto stop = std::chrono::system_clock::now();
            double LGTime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();

            start = std::chrono::system_clock::now();
            testNewton(n, x, y, z);
            stop = std::chrono::system_clock::now();
            double NewTime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();

            std::cout << "With n = " << n << " and m = " << m << ": " << std::endl;
            std::cout << '\t' << "Lagrange time: " << LGTime << " nanoseconds" << std::endl;
            std::cout << '\t' << "Newton time:   " << NewTime << " nanoseconds" << std::endl;
            std::cout << std::endl;
        }
    }

    return 0;
}
