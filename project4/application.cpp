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
