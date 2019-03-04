#include <iostream>
#include <stdio.h>
#include <armadillo>

using namespace std;
using namespace arma;

/** solver.cpp
  * usage: make run 0=a 1=b 2=c 3=d 4=e 5=f 6=g 7=h
  * where
  * 0 - x points
  *	1 - x ofset
  *	2 - x start
  * 3 - wave's peak position
  * 4 - time steps
  * 5 - total time
  * 6 - wave's peak time
  * 7 - Amplitude\
  * 8 - R
**/

#define FRAMES_PER_SECOND 24
#define PI 3.14159265359
#define FREQ 1.25

// some global variables to be used in the calculations
float A, R, t_w/*ave */, x_w/*ave */;

float fxt(float x, float t) {
	// float termT = R * (t - t_w) * (t - t_w);
	// float D = (x - x_w) * (x - x_w) + (t - t_w) * (t - t_w);
	// float termD = R * D;
	// float result = A * exp(-termT) * (1. - 2. * termD) * exp(-termD);
	// float result = .00001* (sin(termT) / cos(termD) + .001);
	float result = (1 - 2 * PI * PI * FREQ * FREQ * (t - t_w) * (t - t_w)) * \
		exp(-PI * PI * FREQ * FREQ * (t - t_w) * (t - t_w)) * (1 - 2 * PI * PI * \
		FREQ * FREQ * (x - x_w) * (x - x_w)) * exp(-PI * PI * FREQ * FREQ * \
		(x - x_w) * (x - x_w));
	// printf("%f ", result);
    return result;
}

int main(int argc, char const *argv[]) {

    int   x_points   , t_points;
    float x_ofst     , t_ofst;
    float x_b/*egin*/, t_t/*otal*/;

    // Creating objects for conversion of arguments
    stringstream convert0(argv[1]);
    stringstream convert1(argv[2]);
    stringstream convert2(argv[3]);
    stringstream convert3(argv[4]);
    stringstream convert4(argv[5]);
    stringstream convert5(argv[6]);
	stringstream convert6(argv[7]);
	stringstream convert7(argv[8]);
	stringstream convert8(argv[9]);

    // Putting arguments on variables
    convert0 >> x_points;
    convert1 >> x_ofst;
    convert2 >> x_b;
	convert3 >> x_w;
	convert4 >> t_points;
    convert5 >> t_t;
	convert6 >> t_w;
	convert7 >> A;
	convert8 >> R;

	t_ofst = /*t_t / t_points*/.5 * x_ofst;
	t_points = (int) t_t / t_ofst;
	printf("%d\n", t_points);

	cout << "X points:     " << x_points << "\n";
    cout << "X offset:     " << x_ofst   << "\n";
    cout << "T size:       " << t_t      << "\n";
    cout << "T wave's pic: " << t_w      << "\n";

    mat A(t_points, x_points);
	A.fill(0.);
	// mat A(3, 4);
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

    float x_ofst_2 = x_ofst * x_ofst;
    float t_ofst_2 = t_ofst * t_ofst;
    float termA = t_ofst_2 / x_ofst_2;

	// printf("%f\n", termA);

    for (int i = 1; i < t_points - 1; i++) {
        for (int j = 1; j < x_points - 1; j++) {
	    	A(i + 1, j) = termA * (A(i, j - 1) - 2. * A(i, j) + A(i, j + 1)) \
				- A(i - 1, j) + 2. * A(i, j) + t_ofst_2 * fxt(x_j, t_i);
            x_j += x_ofst;
        }
        t_i += t_ofst;
        x_j = x_b;
    }

    parameters.save("data/outputs/pmts.dat", raw_ascii);
    A.save("data/outputs/A.dat", raw_binary);

    return 0;
}
