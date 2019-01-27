#include <iostream>
#include <stdio.h>
#include <armadillo>

using namespace std;
using namespace arma;

#define FRAMES_PER_SECOND 24

float fxt(float x, float t) {
    return 0.;
}

int main(int argc, char const *argv[]) {

    int   x_points   , t_points;
    float x_ofst     , t_ofst;
    float x_b/*egin*/, t_t/*otal*/;
	float x_w/*ave */, t_w/*ave */ ;

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
    convert2 >> x_b;
	convert3 >> x_w;
    convert4 >> t_t;
	convert5 >> t_w;

    t_points = (int) t_t * FRAMES_PER_SECOND;
	t_ofst = t_t / t_points;
	
	cout << "X points:     " << x_points << "\n";
    cout << "X offset:     " << x_ofst   << "\n";
    cout << "T size:       " << t_t      << "\n";
    cout << "T wave's pic: " << t_w      << "\n";

    mat A(x_points, t_points);
    rowvec parameters(5);

    // Storing parameters in a vector for a file
    parameters(0) = x_points; parameters(1) = x_ofst; parameters(2) = x_b;
    parameters(3) = t_t; parameters(4) = t_points;// parameters(5) = t_t;

    wall_clock timer;

    // Calculating function
    float x_i = x_b;
    float t_j = 0.;
    // timer.tic();

    float x_ofst_2 = x_ofst * x_ofst;
    float t_ofst_2 = t_ofst * t_ofst;
    float termA = t_ofst_2 / x_ofst_2;

    for (int i = 1; i < x_points - 1; i++) {
        for (int j = 1; j < t_points - 1; j++) {
	    	A(i, j + 1) = termA * (A(i - 1, j) - 2. * A(i, j) + A(i + 1, j)) - \
	      		A(i, j - 1) + 2. * A(i, j) + fxt(x_i, t_j);
            t_j += t_ofst;
        }
        x_i += x_ofst;     
        t_j = 0.;
    }

    // double eTime = timer.toc();
    // printf("Elapsed time: %lf\n", eTime);

    parameters.save("data/outputs/pmts.dat", raw_ascii);
    A.save("data/outputs/A.dat", raw_binary);

    return 0;
}
	
