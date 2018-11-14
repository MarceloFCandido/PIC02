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
#define W 0.025
#define AMP 1.0

typedef struct {
    mat *A;
    int num_p_x_sub_mtx, num_p_t_sub_mtx_start, num_p_t_sub_mtx_end;
    float x_start, t_start;
    float x_ofst, t_ofst;
} kit;

double f(double x, double t) {
    // Defining Tterm
    double tTerm = t;
    tTerm *= tTerm;
    tTerm *= PI * PI + W * W;

    printf("t: %f\n", tTerm);

    // Defining Xterm
    double xTerm = x;
    xTerm *= xTerm;

    printf("x: %f\n", xTerm);

    // Defining Dterm
    double dTerm = xTerm;
    dTerm *= PI * PI + W * W;

    printf("d: %f\n", dTerm);

    // printf("%f %f\n", x, t);
    // printf("%f\n", AMP * exp(-tTerm) * ((1 - 2 * dTerm) * exp(-dTerm)));
    // CAUTION: the minus in front of Tterm and Dterm
    return AMP * exp(tTerm) * ((1 - 2 * dTerm) * exp(dTerm));

}

void *calculate(void *p) {

    kit *m = ((kit *) p);
    float x = m->x_start, t = m->t_start;
    mat *U = m->A;

    // printf("start: %d\n", m->num_p_t_sub_mtx_start);
    // printf("end: %d\n", m->num_p_t_sub_mtx_end);

    for (int j = m->num_p_t_sub_mtx_start; j < m->num_p_t_sub_mtx_end; j++) {
        // printf("j: %d\n", j);
        for (int i = 1; i < m->num_p_x_sub_mtx - 1; i++) {
            // printf("i: %d ", i);
            (*U)(i, j + 1) = -(*U)(i, j - 1) + 2. * (*U)(i, j) +
                (DT * DT) / (m->x_ofst * m->x_ofst) * ((*U)(i - 1, j) - 2. * (*U)(i, j) +
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
    convert3 >> t;

    t_points = t * TIME_STEPS_PER_SCND;

    cout << "X points: " << x_points << "\n";
    cout << "X offset: " << x_ofst << "\n";
    cout << "T: " << t << "\n";
    cout << "T points: " << t_points << "\n";

    mat A(x_points, t_points);
    rowvec parameters(6);

    // Storing parameters in a vector for a file
    parameters(0) = x_points; parameters(1) = x_ofst; parameters(2) = x;
    parameters(3) = t_points; parameters(4) = DT; parameters(5) = t;

    // Initing Pthreads tools
    pthread_t threads[NUM_THREADS];
    long k;

    // Defining threads as joinable threads
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Creating kit for calculate()
    kit m[NUM_THREADS];

    int mtx_start_ignored;
    for (int i = 0; i < NUM_THREADS - 1; i++) {
        m[i].A = &A;
        m[i].x_ofst = x_ofst;
        m[i].t_ofst = DT;
        m[i].x_start = x;
        mtx_start_ignored = i > 0 ? 0 : 1;
        m[i].t_start = t + i * (t_points / NUM_THREADS) * DT;
        m[i].num_p_x_sub_mtx = x_points;
        m[i].num_p_t_sub_mtx_start = i * ceil(t_points / NUM_THREADS) + mtx_start_ignored;
        m[i].num_p_t_sub_mtx_end = (i + 1) * ceil(t_points / NUM_THREADS);
    }

    m[NUM_THREADS - 1].A = &A;
    m[NUM_THREADS - 1].x_ofst = x_ofst;
    m[NUM_THREADS - 1].t_ofst = DT;
    m[NUM_THREADS - 1].x_start = x;
    m[NUM_THREADS - 1].t_start = t + (NUM_THREADS - 1) * (t_points / NUM_THREADS) * DT;
    m[NUM_THREADS - 1].num_p_x_sub_mtx = x_points;
    m[NUM_THREADS - 1].num_p_t_sub_mtx_start = (NUM_THREADS - 1) * ceil(t_points / NUM_THREADS);
    m[NUM_THREADS - 1].num_p_t_sub_mtx_end = t_points - 1;

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
    A.save("data/outputs/A.dat", raw_ascii/*binary*/);

    pthread_exit(NULL);

    return 0;
}
