#include "steffensen.cpp"

#include <iostream>

using namespace std;

double f(const double, void*);

int main() {
    int guesses[3] = { -1, 2, 3 };
    double tols[3] = { 10e-3, 10e-7, 10e-11 };
    int maxit = 20;

    for(unsigned int i = 0; i < 3; i++) {
        for(unsigned int j = 0; j < 3; j++) {
            int guess = guesses[i];
            double tol = tols[j];
            double res = steffensen(f, guess, maxit, tol, true, NULL);
            cout << res;
        }
    }

    cout << "steff" << endl;
    return 0;
}

double f(const double x, void *data) {
    return .20 * (x - 5) * (x + 2) * (x + 3);
}
