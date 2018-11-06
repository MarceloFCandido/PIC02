#include <iostream>
#include <stdio.h>
#include <armadillo>
#include <pthread.h>

using namespace std;
using namespace arma;

#define NUM_THREADS 4

typedef struct {
    mat *A;
    float x_ofst, y_ofst;
} kit;

void *calculate(void *p) {

    kit *m = ((kit *) p);

    float x, y;

    for (int i = 0; i < size(*(m->A))(0); i++) {
        x += m->x_ofst;
        for (int j = 0; j < size(*(m->A))(1); j++) {
            y += m->y_ofst;
            (*(m->A))(i, j) = sin(exp(x)) * cos(log(y));
        }
    }

}

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

    // Initing Pthreads tools
    pthread_t threads[NUM_THREADS];
    long t;

    kit m;
    m.A = &A;
    m.x_ofst = x_ofst;
    m.y_ofst = y_ofst;

    // Calculating function
    for (t = 0; t < NUM_THREADS; t++) {
        if (pthread_create(&threads[t], NULL, calculate, (void *) &m)) {
            printf("error: creation of thread %ld failed. Aborting...\n", t);
        }
    }

    parameters.save("../data/outputs/pmts.dat", raw_ascii);
    A.save("../data/outputs/A.dat", raw_binary);

    return 0;
}
