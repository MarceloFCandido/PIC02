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

    // Getting external data
    ifstream wf("data/specs/wOut.dat",  ios::in | ios::binary);
    ifstream vf("data/specs/vOut.dat",  ios::in | ios::binary);
    ifstream ifl("data/specs/iOut.dat", ios::in | ios::binary);

    vector<interface> it;
    vector<velocity> vl;
    for (int i = 0; i < 4; i++) {
        interface auxI(0., 0.);
        velocity auxV(0., 0., 0.);
        auxI.deserialize(&ifl);
        auxV.deserialize(&vf);
        it.push_back(auxI);
        vl.push_back(auxV);
    }
    velocity auxV(0., 0., 0.);
    auxV.deserialize(&vf);
    vl.push_back(auxV);

    _2DWave wv(0., 0., 0., 0., 0., 0., 0., 0., 0., 0.);

    wv.deserialize(&wf);

    // Creating velocities matrix
    mat v;
    v.load("data/velocities/velocities.dat", raw_ascii);

    // Creating arrays for space dimensions X e Y and for time
    vec X = linspace<vec>(0., wv.getLx(), wv.getMx());
    vec Y = linspace<vec>(0., wv.getLy(), wv.getNy());
    vec T = linspace<vec>(0., wv.getTMax(), wv.getOt());

    // Saving arrays of dimensions in space
    X.save("data/specs/X.dat", raw_ascii);
    Y.save("data/specs/Y.dat", raw_ascii);

    // Creating matrix for aplication of the Finite Difference Method (FDM)
    cube U((int) wv.getMx(), (int) wv.getNy(), (int) wv.getOt());

    // Applying initial conditions U = 0. and dt(U) = 0.
    U.slices(0, 1).zeros();

    double a = wv.getDt() * wv.getDt();
    double b = a / (wv.getDx() * wv.getDx());
    double c = a / (wv.getDy() * wv.getDy());

    for (int k = 1; k < wv.getOt() - 1; k++) {
        for (int i = 1; i < wv.getMx() - 1; i++) {
            for (int j = 1; j < wv.getNy() - 1; j++) {
                // TODO: arrumar a equacao
                U(i, j, k + 1) = (1 / (v(i, j) * v(i, j))) *
                (b * (U(i - 1, j, k) - 2 * U(i, j, k) + U(i + 1, j, k)) +
                c * (U(i, j - 1, k) - 2 * U(i, j, k) + U(i, j - 1, k))) +
                a * wv.evaluateFXYT(X(i), Y(j), T(k)) - U(i, j, k - 1) +
                2 * U(i, j, k);
                // (1 / (v(i, j) * v(i, j))) * (U(i - 1, j, k) -
                // 4 * U(i, j, k) + U(i + 1, j, k) + U(i, j - 1, k) +
                // U(i, j + 1, k)) - U(i, j, k - 1) + 2 * U(i, j, k) +
                // wv.evaluateFXYT(X(i), Y(j), T(k));
            }
        }
    }

    // Saving snaps of the FD cube
    int nSnaps = 8;
    cube snaps((int) wv.getMx(), (int) wv.getNy(), nSnaps);
    int h = size(U)[2] / nSnaps;
    for (int i = 1; i < nSnaps; i++) {
        snaps.slice(i - 1) = U.slice(h * i);
    }
    vec d(6);
    d(0) = (int) wv.getMx(); d(1) = (int) wv.getNy(); d(2) = (int) wv.getOt();
    d(3) = nSnaps          ; d(4) = wv.getLx()      ; d(5) = wv.getLy();
    d.save("data/outputs/d.dat", raw_ascii);
    snaps.save("data/outputs/U.dat", raw_ascii);

    return 0;

}
