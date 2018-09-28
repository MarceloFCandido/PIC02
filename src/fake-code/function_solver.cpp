#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]) {

    int x_lenght = 1350, y_lenght = 950;
    float x, y;
    float x_ofst = .5, y_ofst = .5;

    x_lenght = x_lenght << 3;
    y_lenght = x_lenght << 3;

    cout << x_lenght << "\n";
    cout << y_lenght << "\n";

    mat A(x_lenght, y_lenght);

    double inicio = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < x_lenght; i++) {
        #pragma omp parallel for
        for (int j = 0; j < y_lenght; j++) {
            x = x_ofst * i;
            y = y_ofst * j;
            float x_3 = x * x * x;
            float y_2 = y * y;
            A(i, j) = x_3 + y_2;    // Doing f(x, y) = x^3 + y^2
        }
    }
    double fim = omp_get_wtime();

    printf("Elapsed time: %f\n", fim - inicio);

    // cout << A;

    return 0;
}
