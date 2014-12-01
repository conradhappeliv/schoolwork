// Conrad Appel
// MATH 3316
// 2 Dec 2014

#include "carbon.cpp"
#include "mat.h"
#include "steffensen.cpp"

#include <iomanip>

// problem constants
const double rtoler = 1e-14;
const double atoler = 1e-15;
const double depth = .002; // m
const double temperature = 1e3; // Kelvin

// t is the answer when this function
// is 0.
// basically a reconfiguration of C(x, t, T) = .5%
double solve_me(const double t) {
    return carbon(depth, t, temperature, rtoler, atoler)-.005;
}

int main() {
    double time = steffensen(solve_me, 39000, 100, 1e-6);
    int hours = time/3600;
    int minutes = (time - hours*3600)/60;
    double seconds = time - hours*3600 - minutes*60;

    std::cout << "Result: " << std::endl;
        std::cout << '\t' << std::setprecision(7) << std::fixed << time << " seconds" << std::endl;
        std::cout << '\t' << hours << " hours, " << minutes << " minutes, " << std::setprecision(7) << std::fixed << seconds << " seconds" << std::endl;
}
