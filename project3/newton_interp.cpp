#include <iostream>

#include "mat.h"

int newton_coeffs(Mat&, Mat&, Mat&);
double newton_eval(Mat&, Mat&, double);

int newton_coeffs(Mat& x, Mat& y, Mat& c) {
    unsigned int n = x.Cols();
    // algorithm described in book (summarized on page 166)
    for(unsigned int i = 0; i < n; i++) {
        c(i) = y(i);
    }
    for(unsigned int i = 1; i < n; i++) {
        for(unsigned int j = n-1; j >= i; j--) {
            c(j) = (c(j) - c(j-1))/(x(j) - x(j-i));
        }
    }
}

double newton_eval(Mat& x, Mat& c, double z) {
    unsigned int n = x.Cols();
    double sum = 0;
    for(int i = 0; i < n; i++) {
        double product = 1;
        for(unsigned int j = 0; j < i; j++) {
            product *= (z - x(j));
        }
        sum += c(i)*product;
    }
    return sum;
}
