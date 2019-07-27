#include "util.h"
#include "_2DWave.h"

#define SPECS_DIR "./specs/"
#define VEL_DIR   "./velocity/"

/**
    This program has the purpouse of generate the velocities model.
    That consists in a matrix with the values of velocity of each point that
    the matrix aims to represent.
 */

int main(int argc, char const *argv[]) {

    // Getting external data
    ifstream wf ( SPECS_DIR "wOut.dat", ios::in | ios::binary);
    ifstream vf ( SPECS_DIR "vOut.dat", ios::in | ios::binary);
    ifstream ifl( SPECS_DIR "iOut.dat", ios::in | ios::binary);

    vector<interface> it;
    vector<velocity> vl;
    ifstream nInt( SPECS_DIR "nInt.dat", ios::in);
    int N;
    nInt >> N;
    nInt.close();
    for (int i = 0; i < N; i++) {
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
    wf.close();
    vf.close();
    ifl.close();

    // Creating velocities matrix
    mat velocities((int) wv.getMx(), (int) wv.getNy());
    velocities = wv.getVelocitiesMatrix(it, vl);

    // Saving velocities matrix
    velocities.save( VEL_DIR "velocity.dat", raw_ascii);

    return 0;
}
