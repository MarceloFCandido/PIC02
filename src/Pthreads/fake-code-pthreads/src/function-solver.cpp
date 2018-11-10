#include <iostream>
#include <stdio.h>
#include <armadillo>
#include <pthread.h>

using namespace std;
using namespace arma;

#define NUM_THREADS 4
#define PI 3.14159265359

typedef struct {
    mat *A;
    int num_p_x_sub_mtx, num_p_y_sub_mtx_start, num_p_y_sub_mtx_end;
    float x_start, y_start;
    float x_ofst, y_ofst;
} kit;

void *calculate(void *p) {

    kit *m = ((kit *) p);

    float x = m->x_start, y = m->y_start;

    printf("%d %d\n", m->num_p_x_sub_mtx, m->num_p_y_sub_mtx_end);

    for (int i = 0; i < m->num_p_x_sub_mtx; i++) {
        for (int j = m->num_p_y_sub_mtx_start; j < m->num_p_y_sub_mtx_end; j++) {
            (*(m->A))(i, j) = /*2. * */x * x + y * y;
            y += m->y_ofst;
        }
        x += m->x_ofst;
        y = m->y_start;
    }

    pthread_exit(NULL);

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

    mat A(x_points, y_points); // the matrix to be used for calculating
    rowvec parameters(6);

    // Storing parameters in a vector for a file
    parameters(0) = x_points; parameters(1) = x_ofst; parameters(2) = x;
    parameters(3) = y_points; parameters(4) = y_ofst; parameters(5) = y;

    // Initing Pthreads tools
    pthread_t threads[NUM_THREADS];
    long t;

    // Defining threads as joinable threads
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Creating kit for calculate()
    kit m[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS - 1; i++) {
        m[i].A = &A;
        m[i].x_ofst = x_ofst;
        m[i].y_ofst = y_ofst;
        m[i].x_start = x;
        m[i].y_start = y + i * (y_points / NUM_THREADS) * y_ofst;
        m[i].num_p_x_sub_mtx = x_points;
        m[i].num_p_y_sub_mtx_start = i * ceil(y_points / NUM_THREADS);
        m[i].num_p_y_sub_mtx_end = (i + 1) * ceil(y_points / NUM_THREADS);
    }

    m[NUM_THREADS - 1].A = &A;
    m[NUM_THREADS - 1].x_ofst = x_ofst;
    m[NUM_THREADS - 1].y_ofst = y_ofst;
    m[NUM_THREADS - 1].x_start = x;
    m[NUM_THREADS - 1].y_start = y + (NUM_THREADS - 1) * (y_points / NUM_THREADS) * y_ofst;
    m[NUM_THREADS - 1].num_p_x_sub_mtx = x_points;
    m[NUM_THREADS - 1].num_p_y_sub_mtx_start = (NUM_THREADS - 1) * ceil(y_points / NUM_THREADS);
    m[NUM_THREADS - 1].num_p_y_sub_mtx_end = y_points;

    // Calculating function

    for (t = 0; t < NUM_THREADS; t++) {
        if (pthread_create(&threads[t], &attr, calculate, (void *) &m[t])) {
            printf("error: creation of thread %ld failed. Aborting...\n", t);
            exit(-1);
        }
    }

    // Joining threads
    void *status;
    for (t = 0; t < NUM_THREADS; t++) {
      if (pthread_join(threads[t], &status)) {
          printf("error: joining of thread %ld failed. Aborting...\n", t);
          exit(-1);
      }
    }

    // cout << size(A);

    parameters.save("data/outputs/pmts.dat", raw_ascii);
    A.save("data/outputs/A.dat", raw_binary);

    pthread_exit(NULL);

    return 0;
}
