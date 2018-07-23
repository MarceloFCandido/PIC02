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
    ifstream nInt("data/specs/nInt.dat", ios::in);
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

    wf.close(); vf.close(); ifl.close();

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

    printf("How many snapshots would you like? ");
    int h = scanf("%d", &N);
    h = (int) wv.getOt() / N;
    queue <int> numSnaps;
    for (int i = 1; h * i < wv.getOt(); i++) { numSnaps.push(h * i); }

    // Creating 3 matrices for application of the Finite Difference Method (FDM)
    mat U1((int) wv.getMx(), (int) wv.getNy());
    mat U2((int) wv.getMx(), (int) wv.getNy());
    mat U3((int) wv.getMx(), (int) wv.getNy());

    // Filling the matrices with zeros
    U1.fill(0.);
    U2.fill(0.);
    U3.fill(0.);

    // Creating a queue for administrating the arrays of FDM
    queue <mat> U;
    U.push(U1); U.push(U2); U.push(U3);

    double a = wv.getDt() * wv.getDt();
    double b = a / (wv.getDx() * wv.getDx());
    double c = a / (wv.getDy() * wv.getDy());

    // @TODO criar planos de memoria
    for (int k = 1; k < wv.getOt() - 1; k++) {
        U3 = U.front(); U.pop(); // t - 1
        U2 = U.front(); U.pop(); // t
        U1 = U.front(); U.pop(); // t + 1
        // 2 1 3
        for (int i = 1; i < wv.getMx() - 1; i++) {
            for (int j = 1; j < wv.getNy() - 1; j++) {
                // TODO: Conferir se os calculos batem
                U1(i, j) = (1 / (v(i, j) * v(i, j))) *
                (b * (U2(i - 1, j) - 2 * U2(i, j) + U2(i + 1, j)) +
                c * (U2(i, j - 1) - 2 * U2(i, j) + U2(i, j - 1))) +
                a * wv.evaluateFXYT(X(i), Y(j), T(k)) - U3(i, j) +
                2 * U2(i, j);
            }
        }
        if (k == numSnaps.front()) {
            ostringstream oss;
            int save = numSnaps.front();
            oss << "data/outputs/snap" << save << ".dat";
            numSnaps.pop(); numSnaps.push(save);
            cout << *oss << '\n';
            U2.save(oss, raw_ascii);
        }
        U.push(U2); U.push(U1); U.push(U3);
    }

    // vec d(6);
    // d(0) = (int) wv.getMx(); d(1) = (int) wv.getNy(); d(2) = (int) wv.getOt();
    // d(3) = nSnaps          ; d(4) = wv.getLx()      ; d(5) = wv.getLy();
    // d.save("data/outputs/d.dat", raw_ascii);
    // snaps.save("data/outputs/U.dat", raw_ascii);

    return 0;

}
