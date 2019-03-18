#include <iostream>
#include <stdio.h>
#include <armadillo>
#include <pthread.h>

using namespace std;
using namespace arma;

#define NUM_THREADS 12
#define PI 3.14159265359

typedef struct kit_t {
    int x_pt_start;
    int x_pt_end;
    int j;
} KIT_t;

// some global variables to be used in the calculations
float A,
      R,
      t_w/*ave */,
      x_w/*ave */,
      pi2_freq2,
      x_ofst_2,
      t_ofst_2,
      termA;

float fxt(float x, float t) {
	float Dx = x - x_w;
	float Dx2 = Dx * Dx;
	float Dt = t - t_w;
	float Dt2 = Dt * Dt;
	// printf("%f %f\n", x, t);
	float result = ((1. - 2. * pi2_freq2 * Dt2) * exp(-pi2_freq2 * Dt2)) * \
				   ((1. - 2. * pi2_freq2 * Dx2) * exp(-pi2_freq2 * Dx2));
	return result;
}

void *eval(void *void_kit) {
    KIT_t *kit = (KIT_t *) void_kit;


}

int main(int argc, char const *argv[]) {

    int   x_points   , t_points   ;
	float x_ofst     , t_ofst, x_t;
	float x_b/*egin*/, t_t/*otal*/;

    // auxiliary variables
    float freq,
          freq2,
          pi2 = PI * PI;

	// Creating objects for conversion of arguments
	stringstream convert0(argv[1]);
	stringstream convert1(argv[2]);
	stringstream convert2(argv[3]);
	stringstream convert3(argv[4]);
	stringstream convert4(argv[5]);
	stringstream convert5(argv[6]);
	stringstream convert6(argv[7]);

    // Putting arguments on variables
  	convert0 >> x_points;
	convert1 >> x_b;
  	convert2 >> x_t;
	convert3 >> x_w;
	convert4 >> t_t;
	convert5 >> t_w;
	convert6 >> freq;

	x_ofst    = x_t / x_points;
	t_ofst    = .5 * x_ofst;
	t_points  = (int) t_t / t_ofst;
	freq2     = freq * freq;
	pi2_freq2 = pi2 * freq2;

	cout << "X points    : " << x_points          << "\n";
	cout << "T points    : " << t_points          << "\n";
	cout << "X offset    : " << x_ofst            << "\n";
	cout << "T offset    : " << t_ofst            << "\n";
	cout << "X total     : " << x_points * x_ofst << "\n";
  	cout << "T total     : " << t_t               << "\n";
	cout << "X wave's pic: " << x_w               << "\n";
  	cout << "T wave's pic: " << t_w               << "\n";

    // creating the matrix for calculations and a row vector for saving
    // parameters
  	mat A(t_points, x_points);
	A.fill(0.);
  	rowvec parameters(5);

  	// Storing parameters in a vector for a file
  	parameters(0) = x_points;
	parameters(1) = x_ofst;
	parameters(2) = x_b;
  	parameters(3) = t_t;
	parameters(4) = t_points;

  	// Calculating function
	float x_j = x_b;
	float t_i = 0.;

    // setting some calculation variables
	x_ofst_2 = x_ofst * x_ofst;
	t_ofst_2 = t_ofst * t_ofst;
	termA = t_ofst_2 / x_ofst_2;

    // creating threads
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

    // creating kits for the threads
    KIT_t kits[NUM_THREADS];

    // initializing ptheads attribute and setting threads as joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // determining how many points each thread will have to take care of
    int x_pts_per_thread = (x_points - 2) / NUM_THREADS;

    // distributing information for kits
    for(int i = 0; i < NUM_THREADS - 1; i++) {
        kits[i].x_pt_start = i * x_pts_per_thread + 1;
        kits[i].x_pt_end   = i * x_pts_per_thread + x_pts_per_thread;
    }
    kits[NUM_THREADS - 1].x_pt_start = (NUM_THREADS - 1) * x_pts_per_thread + 1;
    kits[NUM_THREADS - 1].x_pt_end   = t_points - 2;

    // creating threads
    // TODO: put actual j inside the creation of the threads

    // joining threads


    return 0;
}
