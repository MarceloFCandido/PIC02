#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]) {

    int x_points, y_points;
    float x_ofst, y_ofst;
    float x, y;

    // Creating objects for conversion of arguments
    stringstream convert0(argv[1]);
    stringstream convert1(argv[2]);
    stringstream convert2(argv[3]);
    stringstream convert3(argv[4]);

    // Putting arguments on variables
    convert0 >> x_points;
    convert1 >> x_ofst;
    convert2 >> y_points;
    convert3 >> y_ofst;

    cout << "X points: " << x_points << "\n";
    cout << "X offset: " << x_ofst << "\n";
    cout << "Y points: " << y_points << "\n";
    cout << "Y offset: " << y_ofst << "\n";

    mat A(x_points, y_points);
    rowvec parameters(4);

    // Storing parameters in a vector for a file
    parameters(0) = x_points; parameters(1) = x_ofst;
    parameters(2) = y_points; parameters(3) = y_ofst;

    // Calculating function
    double start = omp_get_wtime();
    for (int i = 0; i < x_points; i++) {
        for (int j = 0; j < y_points; j++) {
            x = x_ofst * i;
            y = y_ofst * j;
            float x_3 = x * x * x;
            float y_2 = y * y;
            A(i, j) = x_3 + y_2;    // Doing f(x, y) = x^3 + y^2
        }
    }
    double end = omp_get_wtime();

    printf("Elapsed time: %f\n", end - start);

    parameters.save("pmts.dat", raw_ascii);
    A.save("A.dat", raw_binary);

    return 0;
}
