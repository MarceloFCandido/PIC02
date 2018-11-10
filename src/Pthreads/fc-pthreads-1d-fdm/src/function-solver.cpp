#include <iostream>
#include <stdio.h>
#include <armadillo>
#include <pthread.h>

using namespace std;
using namespace arma;

#define NUM_THREADS 4
#define PI 3.14159265359
#define TIME_STEPS_PER_SCND 24
#define DT 0.04166666666
#define W 1.
#define AMP 1.

typedef struct {
    mat *A;
    int num_p_x_sub_mtx, num_p_t_sub_mtx_start, num_p_t_sub_mtx_end;
    float x_start, t_start;
    float x_ofst, t_ofst;
} kit;

double _2DWave::evaluateFXYT(double x, double t) {
    // Defining Tterm
    double tTerm = t;
    tTerm *= tTerm;
    tTerm *= PI * PI + W * W;

    // Defining Xterm
    double xTerm = x;
    xTerm *= xTerm;

    // Defining Dterm
    double dTerm = xTerm;
    dTerm *= PI * PI + W * W;

    // CAUTION: the minus in front of Tterm and Dterm
    return AMP * exp(-tTerm) * ((1 - 2 * dTerm) * exp(-dTerm));

}

void *calculate(void *p) {

    kit *m = ((kit *) p);
    float x = m->x_start, t = m->t_start;
    mat *U = m->A;

    for (int i = 0; i < m->num_p_x_sub_mtx; i++) {
        for (int j = m->num_p_y_sub_mtx_start; j < m->num_p_y_sub_mtx_end; j++) {
            (*U)(i, j + 1) = -(*U)(i, j - 1) + 2. * (*U)(i, j) +
                (DT * DT) / (x_ofst * x_ofst) * ((*U)(i - 1, j) - 2. * (*U)(i, j) +
                (*U)(i + 1, j)) + f(x, t);
            t += m->t_ofst;
        }
        x += m->x_ofst;
        t = m->t_start;
    }

    pthread_exit(NULL);

}

int main(int argc, char const *argv[]) {

    int x_points, t_points;
    float x_ofst;
    float x, t;

    // Creating objects for conversion of arguments
    stringstream convert0(argv[1]);
    stringstream convert1(argv[2]);
    stringstream convert2(argv[3]);
    stringstream convert3(argv[4]);

    // Putting arguments on variables
    convert0 >> x_points;
    convert1 >> x_ofst;
    convert2 >> x;
    convert5 >> t;

    t_points = t * TIME_STEPS_PER_SCND;

    cout << "X points: " << x_points << "\n";
    cout << "X offset: " << x_ofst << "\n";
    cout << "T: " << t << "\n";
    cout << "T points: " << t_points << "\n";

    mat A(x_points, t_points);
    rowvec parameters(6);

    // Storing parameters in a vector for a file
    parameters(0) = x_points; parameters(1) = x_ofst; parameters(2) = x;
    parameters(3) = y_points; parameters(4) = y_ofst; parameters(5) = y;

    // Initing Pthreads tools
    pthread_t threads[NUM_THREADS];
    long k;

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
        m[i].t_start = t + i * (t_points / NUM_THREADS) * t_ofst;
        m[i].num_p_x_sub_mtx = x_points;
        m[i].num_p_t_sub_mtx_start = i * ceil(t_points / NUM_THREADS);
        m[i].num_p_t_sub_mtx_end = (i + 1) * ceil(t_points / NUM_THREADS);
    }

    m[NUM_THREADS - 1].A = &A;
    m[NUM_THREADS - 1].x_ofst = x_ofst;
    m[NUM_THREADS - 1].t_ofst = t_ofst;
    m[NUM_THREADS - 1].x_start = x;
    m[NUM_THREADS - 1].t_start = y + (NUM_THREADS - 1) * (t_points / NUM_THREADS) * t_ofst;
    m[NUM_THREADS - 1].num_p_x_sub_mtx = x_points;
    m[NUM_THREADS - 1].num_p_t_sub_mtx_start = (NUM_THREADS - 1) * ceil(t_points / NUM_THREADS);
    m[NUM_THREADS - 1].num_p_t_sub_mtx_end = t_points;

    // Calculating function
    for (k = 0; k < NUM_THREADS; k++) {
        if (pthread_create(&threads[k], &attr, calculate, (void *) &m[k])) {
            printf("error: creation of thread %ld failed. Aborting...\n", k);
            exit(-1);
        }
    }

    // Joining threads
    void *status;
    for (k = 0; k < NUM_THREADS; k++) {
      if (pthread_join(threads[k], &status)) {
          printf("error: joining of thread %ld failed. Aborting...\n", k);
          exit(-1);
      }
    }

    // cout << size(A);

    parameters.save("data/outputs/pmts.dat", raw_ascii);
    A.save("data/outputs/A.dat", raw_binary);

    pthread_exit(NULL);

    return 0;
}
