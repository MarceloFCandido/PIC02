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
    ifstream wf("wOut.dat",  ios::in | ios::binary);
    ifstream vf("vOut.dat",  ios::in | ios::binary);
    ifstream ifl("iOut.dat", ios::in | ios::binary);

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
    mat velocities((int) wv.getMx(), (int) wv.getNy());
    velocities = wv.getVelocitiesMatrix(it, vl);

    // Creating arrays for space dimensions X e Y and for time
    vec X = linspace<vec>(0., wv.getLx(), wv.getMx());
    vec Y = linspace<vec>(0., wv.getLy(), wv.getNy());
    vec T = linspace<vec>(0., wv.getTMax(), wv.getOt());

    // Creating matrix for aplication of the Finite Difference Method (FDM)
    cube U((int) wv.getMx(), (int) wv.getNy(), (int) wv.getOt());

    // Applying initial conditions U = 0. and dt(U) = 0.
    U.slices(0, 1).zeros();

    // TODO: apply border conditions

    // https://stackoverflow.com/questions/31607692/armadillo-create-vector-with-colon-range
    vec i = linspace<vec>(1, wv.getMx() - 1, wv.getMx() - 1); // +1 to get the end value
    vec j = linspace<vec>(1, wv.getNy() - 1, wv.getNy() - 1); // +1 to get the end value

    

    // cout << j << endl;

    // cout << it[0].getA() << "\n";
    // cout << it[0].getB() << "\n";
    // cout << it[1].getA() << "\n";
    // cout << it[1].getB() << "\n";
    // cout << it[2].getA() << "\n";
    // cout << it[2].getB() << "\n";
    // cout << it[3].getA() << "\n";
    // cout << it[3].getB() << "\n";
    //
    // cout << vl[0].getA() << '\n';
    // cout << vl[0].getB() << '\n';
    // cout << vl[0].getC() << '\n';
    // cout << vl[1].getA() << '\n';
    // cout << vl[1].getB() << '\n';
    // cout << vl[1].getC() << '\n';
    // cout << vl[2].getA() << '\n';
    // cout << vl[2].getB() << '\n';
    // cout << vl[2].getC() << '\n';
    // cout << vl[3].getA() << '\n';
    // cout << vl[3].getB() << '\n';
    // cout << vl[3].getC() << '\n';
    // cout << vl[4].getA() << '\n';
    // cout << vl[4].getB() << '\n';
    // cout << vl[4].getC() << '\n';

    // cout << wv.getLx() << "\n";
    // cout << wv.getLy() << "\n";
    // cout << wv.getTMax() << "\n";
    // cout << wv.getMx() << "\n";
    // cout << wv.getNy() << "\n";
    // cout << wv.getW() << "\n";
    // cout << wv.getA() << "\n";
    // cout << wv.getXp() << "\n";
    // cout << wv.getYp() << "\n";
    // cout << wv.getTp() << "\n";

    return 0;

}
