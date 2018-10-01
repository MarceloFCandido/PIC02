#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]) {

    // Creating objects for conversion of arguments
    stringstream convert0(argv[1]);
    stringstream convert1(argv[2]);
    stringstream convert2(argv[3]);
    stringstream convert3(argv[4]);

    int x_points, y_points;
    float x_ofst, y_ofst;
    float x, y;

    // Putting arguments on variables
    convert0 >> x_points;
    convert1 >> x_ofst;
    convert2 >> y_points;
    convert3 >> y_ofst;

    cout << "X points: " << argv[1] << "\n";
    cout << "X offset: " << argv[2] << "\n";
    cout << "Y points: " << argv[3] << "\n";
    cout << "Y offset: " << argv[4] << "\n";

    mat A(x_points, y_points);

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

    
    A.save("A.dat", raw_binary);

    return 0;
}
