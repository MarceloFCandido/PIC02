#include "util/util.h"
#include "wave/_2DWave.h"

/*
 *    This program aims to solve the bidimensional wave equation
 *    by the finite differences method. This methods will be im-
 *    plemented with the help of Eigen library, that provides the
 *    necessary tools of the Linear Algebra, mainly the vectors
 *    and matrices thats will be used to store and manipulate data,
 *    as well the methods that are necessary to this.
 */

int main () {

    double Lx = 5.;
    double Ly = 5.;
    double tMax = 30.;
    int Mx = 50;
    int Ny = 50;
    double w = 1.;
    double A = 1.;
    double Xp = 0.;
    double Yp = 0.;
    double Tp = .1;

    _2DWave wv(Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp);

    vector<interface> it;
    vector<velocity> vl;

    it.push_back(interface(0., 0.));
    it.push_back(interface(0., 1.));
    it.push_back(interface(0., 2.));
    it.push_back(interface(0., 3.));
    it.push_back(interface(0., 4.));

    vl.push_back(velocity(0., 2. , 1. ));
    vl.push_back(velocity(0., 2.5, 1.5));
    vl.push_back(velocity(0., 2.3, 1.4));
    vl.push_back(velocity(0., 2.1, 1.2));
    vl.push_back(velocity(0., 2.2, 1.3));

    cout << wv.getVelocitiesMatrix(it, vl) << "\n";

    // Testing (de)serialization of interface objects
    // ofstream of("test.dat", ios::out | ios::binary);

    // interface i(1., 2.);

    // i.serialize(&of);

    // of.close();

    // ifstream fi("test.dat", ios::in | ios::binary);

    // interface j(0., 0.);

    // j.deserialize(&fi);

    // cout << j.getA() << "\n";
    // cout << j.getB() << "\n";

    // return 0;

}
