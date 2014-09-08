#include "nest.cpp"
#include "mat.h"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    // -4, -3.99, -3.98, ..., 3.98, 3.99, 4
    Mat z = Linspace(-4, 4, 801);

    // Compute the vector p5 as the value of the Taylor polynomial p 5 (x) for all points x ∈ z.
    double p5Data[] = {0, 1, 0, -1.0/6, 0, 1.0/120};
    Mat p5Coeffs = Mat(1, 6, p5Data);
    Mat p5Res = Mat(1, 801);
    for(int i = 0; i < 801; i++) { p5Res(i) = nest(p5Coeffs, z(i)); }

    // Compute the vector p9 as the value of p 9 (x) for all x ∈ z.
    double p9Data[] = {0, 1, 0, -1.0/6, 0, 1.0/120, 0, -1.0/5040, 0, 1.0/362880};
    Mat p9Coeffs = Mat(1, 9, p9Data);
    Mat p9Res = Mat(1, 801);
    for(int i = 0; i < 801; i++) { p9Res(i) = nest(p9Coeffs, z(i)); }

    // Compute the vector p13 as the value of p 13 (x) for all x ∈ z.
    double p13Data[] = {0, 1, 0, -1.0/6, 0, 1.0/120, 0, -1.0/5040, 0, 1.0/362880, 0, -1.0/39916800, 0, 1.0/6227020800};
    Mat p13Coeffs = Mat(1, 13, p13Data);
    Mat p13Res = Mat(1, 801);
    for(int i = 0; i < 801; i++) { p13Res(i) = nest(p13Coeffs, z(i)); }

    // Compute the vector f by evaluating sin(x) at all x ∈ z.
    Mat fRes = Mat(1, 801);
    for(int i = 0; i < 801; i++) { fRes(i) = sin(z(i)); }

    // Compute the vector err5 as | sin(x) − p 5 (x)| for each x ∈ z.
    Mat err5 = Mat(1, 801);
    for(int i = 0; i < 801; i++) { err5(i) = abs(fRes(i) - p5Res(i)); }

    // Compute the vector err9 as | sin(x) − p 9 (x)| for each x ∈ z.
    Mat err9 = Mat(1, 801);
    for(int i = 0; i < 801; i++) { err9(i) = abs(fRes(i) - p9Res(i)); }

    // Compute the vector err13 as | sin(x) − p 13 (x)| for each x ∈ z.
    Mat err13 = Mat(1, 801);
    for(int i = 0; i < 801; i++) { err13(i) = abs(fRes(i) - p13Res(i)); }

    z.Write("z.txt");
    p5Res.Write("p5.txt");
    p9Res.Write("p9.txt");
    p13Res.Write("p13.txt");
    fRes.Write("f.txt");
    err5.Write("err5.txt");
    err9.Write("err9.txt");
    err13.Write("err13.txt");

    return 0;
}
