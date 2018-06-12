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

    ifstream wf("wOut.dat",  ios::in | ios::binary);
    ifstream vf("vOut.dat",  ios::in | ios::binary);
    ifstream ifl("iOut.dat", ios::in | ios::binary);

    // long begin, end;
    // begin = ifl.tellg();
    // ifl.seekg (0, ios::end);
    // end = ifl.tellg();
    // cout << "size: " << (end-begin) << " bytes." << endl;

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

    cout << it[3].getA() << "\n";
    cout << wv.getLy() << "\n";
    cout << wv.getTMax() << "\n";
    cout << wv.getMx() << "\n";
    cout << wv.getNy() << "\n";
    cout << wv.getW() << "\n";
    cout << wv.getA() << "\n";
    cout << wv.getXp() << "\n";
    cout << wv.getYp() << "\n";
    cout << wv.getTp() << "\n";

    return 0;

}
