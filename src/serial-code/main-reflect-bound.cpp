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
    mat velocities;
    velocities.load("data/velocities/velocities.dat", raw_ascii);

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

    // TODO: apply border conditions

    // https://stackoverflow.com/questions/31607692/armadillo-create-vector-with-colon-range
    rowvec ii = linspace<rowvec>(1, wv.getMx(), wv.getMx()); // +1 to get the end value
    colvec jj = linspace<colvec>(1, wv.getNy(), wv.getNy()); // +1 to get the end value

    // FIXME: Problema com esses indices (repensar meshgrid!)

    mat XX(size(ii)[1], size(jj)[0]);
    mat YY(size(ii)[1], size(jj)[0]);

    cout << size(ii) << '\n';
    cout << size(jj) << '\n';
    cout << size(XX) << '\n';
    cout << size(YY) << '\n';
    cout << size(velocities) << '\n';

    // Imitate meshgrid
    for (int i = 0; i < size(ii)[1]; i++) {
        // cout << size(XX.row(i)) << '\n';
        XX.row(i) = ii;
    }

    // for (int j = 0; j < size(jj)[0]; j++) {
    //     YY.col(j) = jj;
    // }

    //
    // // Criando dx2
    // double dx2 = wv.getDx() * wv.getDx();
    //
    // mat d(size(velocities));
    // for (int i = 0; i < size(d)[0]; i++) {
    //     for (int j = 0; j < size(d)[1]; j++) {
    //
    //     }
    // }


    return 0;

}
