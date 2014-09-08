#include "mat.h"

#include <iostream>

double nest(Mat &a, double x) {
    double sum = a(a.Cols() - 1);
    for(unsigned int i = a.Cols() - 2; i > 0; i--) {
        sum = a(i) + x*sum;
    }
    return sum;
}
