#include <iostream>
#include <stdio.h>
#include <armadillo>

using namespace std;
using namespace arma;

#define NUM_TIMES 100
#define PI 3.14159265359

int main(int argc, char const *argv[]) {

    int x_points, y_points;
    float x_ofst, y_ofst;
    float x, y;

    // Creating objects for conversion of arguments
    stringstream convert0(argv[1]);
    stringstream convert1(argv[2]);
    stringstream convert2(argv[3]);
    stringstream convert3(argv[4]);
    stringstream convert4(argv[5]);
    stringstream convert5(argv[6]);

    // Putting arguments on variables
    convert0 >> x_points;
    convert1 >> x_ofst;
    convert2 >> x;
    convert3 >> y_points;
    convert4 >> y_ofst;
    convert5 >> y;

    cout << "X points: " << x_points << "\n";
    cout << "X offset: " << x_ofst << "\n";
    cout << "Y points: " << y_points << "\n";
    cout << "Y offset: " << y_ofst << "\n";

    mat A(x_points, y_points);
    rowvec parameters(6);

    // Storing parameters in a vector for a file
    parameters(0) = x_points; parameters(1) = x_ofst; parameters(2) = x;
    parameters(3) = y_points; parameters(4) = y_ofst; parameters(5) = y;

    wall_clock timer;

    // Calculating function
    float x_i = x;
    float y_i = y;
    // timer.tic();

    for (int i = 0; i < x_points; i++) {
        // printf("\nx: %.1f\n", x_i);
        for (int j = 0; j < y_points; j++) {
            // printf("y: %.1f ", y_i);
            // printf("%.1f ", );
			A(i, j) = 2. * x_i * x_i + y_i * y_i;
            y_i += y_ofst;
            //  A(i, j) = 2. * x * x + y * y;
        }
        x_i += x_ofst;
        y_i = y;
    }

    // double eTime = timer.toc();
    // printf("Elapsed time: %lf\n", eTime);

    parameters.save("data/outputs/pmts.dat", raw_ascii);
    A.save("data/outputs/A.dat", raw_binary);

    return 0;
}
