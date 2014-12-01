// Conrad Appel
// MATH 3316
// 2 Dec 2014

#include "carbon.cpp"

const double rtoler = 1e-12;
const double atoler = 1e-14;

int main() {
    Mat x = Linspace(0, .004, 300); // m
    Mat t = Linspace(0, 172800, 500); // seconds
    Mat c900 = Mat(300, 500);
    Mat c1100 = Mat(300, 500);
    Mat c900_1 = Mat(300);
    Mat c900_6 = Mat(300);
    Mat c900_12 = Mat(300);
    Mat c900_24 = Mat(300);
    Mat c900_48 = Mat(300);
    Mat c1100_1 = Mat(300);
    Mat c1100_6 = Mat(300);
    Mat c1100_12 = Mat(300);
    Mat c1100_24 = Mat(300);
    Mat c1100_48 = Mat(300);

    // c900
    for(unsigned int i = 0; i < 300; i++)
        for(unsigned int j = 0; j < 500; j++)
            c900(i, j) = carbon(x(i), t(j), 900, rtoler, atoler);

    // c1100
    for(unsigned int i = 0; i < 300; i++)
        for(unsigned int j = 0; j < 500; j++)
            c1100(i, j) = carbon(x(i), t(j), 1100, rtoler, atoler);

    // c900_1hour
    for(unsigned int i = 0; i < 300; i++)
        c900_1(i) = carbon(x(i), 3600, 900, rtoler, atoler);

    // c900_6hour
    for(unsigned int i = 0; i < 300; i++)
        c900_6(i) = carbon(x(i), 21600, 900, rtoler, atoler);

    // c900_12hour
    for(unsigned int i = 0; i < 300; i++)
        c900_12(i) = carbon(x(i), 43200, 900, rtoler, atoler);

    // c900_24hour
    for(unsigned int i = 0; i < 300; i++)
        c900_24(i) = carbon(x(i), 86400, 900, rtoler, atoler);

    // c900_48hour
    for(unsigned int i = 0; i < 300; i++)
        c900_48(i) = carbon(x(i), 172800, 900, rtoler, atoler);

    // c1100_1hour
    for(unsigned int i = 0; i < 300; i++)
        c1100_1(i) = carbon(x(i), 3600, 1100, rtoler, atoler);

    // c1100_6hour
    for(unsigned int i = 0; i < 300; i++)
        c1100_6(i) = carbon(x(i), 21600, 1100, rtoler, atoler);

    // c1100_12hour
    for(unsigned int i = 0; i < 300; i++)
        c1100_12(i) = carbon(x(i), 43200, 1100, rtoler, atoler);

    // c1100_24hour
    for(unsigned int i = 0; i < 300; i++)
        c1100_24(i) = carbon(x(i), 86400, 1100, rtoler, atoler);

    // c1100_48hour
    for(unsigned int i = 0; i < 300; i++)
        c1100_48(i) = carbon(x(i), 172800, 1100, rtoler, atoler);

    x.Write("./x.txt");
    t.Write("./t.txt");
    c900.Write("./c900.txt");
    c1100.Write("./c1100.txt");
    c900_1.Write("./c900_1hour.txt");
    c900_6.Write("./c900_6hour.txt");
    c900_12.Write("./c900_12hour.txt");
    c900_24.Write("./c900_24hour.txt");
    c900_48.Write("./c900_48hour.txt");
    c1100_1.Write("./c1100_1hour.txt");
    c1100_6.Write("./c1100_6hour.txt");
    c1100_12.Write("./c1100_12hour.txt");
    c1100_24.Write("./c1100_24hour.txt");
    c1100_48.Write("./c1100_48hour.txt");
}
