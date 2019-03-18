#include <iostream>
#include <stdio.h>
#include <armadillo>

using namespace std;
using namespace arma;

/** solver.cpp
  * usage: make run xp=a xofst=b xb=c xw=d tt=e tw=f f=i
  * where
  * xp - x points
  *	xb - x start
  *	xt - x total
  * xw - wave's peak position
  * tt - total time
  * tw - wave's peak time
  * f - frequency
**/

#define PI 3.14159265359

// some global variables to be used in the calculations
float A, R, t_w/*ave */, x_w/*ave */, freq, freq2, pi2 = PI * PI, pi2_freq2;

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

int main(int argc, char const *argv[]) {

	int   x_points   , t_points   ;
	float x_ofst     , t_ofst, x_t;
	float x_b/*egin*/, t_t/*otal*/;

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

	x_ofst = x_t / x_points;
	t_ofst = .5 * x_ofst;
	t_points = (int) t_t / t_ofst;
	freq2 = freq * freq;
	pi2_freq2 = pi2 * freq2;

	cout << "X points    : " << x_points          << "\n";
	cout << "T points    : " << t_points          << "\n";
	cout << "X offset    : " << x_ofst            << "\n";
	cout << "T offset    : " << t_ofst            << "\n";
	cout << "X total     : " << x_points * x_ofst << "\n";
  	cout << "T total     : " << t_t               << "\n";
	cout << "X wave's pic: " << x_w               << "\n";
  	cout << "T wave's pic: " << t_w               << "\n";

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

	float x_ofst_2 = x_ofst * x_ofst;
	float t_ofst_2 = t_ofst * t_ofst;
	float termA = t_ofst_2 / x_ofst_2;

	// TODO: verificar se t_i e x_j nao deveriam ser iniciados com t_ofst e \
	// x_ofst respectivamente

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
