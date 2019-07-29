#include "stdio.h"
#include "util.h"
#include "_2DWave.h"

#define SPECS_DIR "./specs/"

using namespace std;

int main(int argc, char const *argv[]) {

    double Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp;
    int N, aux;
    char buffer[64];

    aux = scanf("%s",  buffer);
    aux = scanf("Lx: %lf", &Lx);

    aux = scanf("%s",  buffer);
    aux = scanf("Ly: %lf", &Ly);

    aux = scanf("%s",  buffer);
    aux = scanf("tMax: %lf", &tMax);

    aux = scanf("%s",  buffer);
    aux = scanf("Mx: %lf", &Mx);

    aux = scanf("%s",  buffer);
    aux = scanf("Ny: %lf", &Ny);

    aux = scanf("%s",  buffer);
    aux = scanf("w: %lf", &w);

    aux = scanf("%s",  buffer);
    aux = scanf("A: %lf", &A);

    aux = scanf("%s",  buffer);
    aux = scanf("Xp: %lf", &Xp);

    aux = scanf("%s",  buffer);
    aux = scanf("Yp: %lf", &Yp);

    aux = scanf("%s",  buffer);
    aux = scanf("Tp: %lf", &Tp);

    aux = scanf("%s",  buffer);
    aux = scanf("N: %d", &N);

    double vl[N + 1][3];
    double it[N][2];

    for (int i = 0; i < N; i++) {
        aux = scanf("%s", buffer);
        aux = scanf("%lf %lf %lf", &vl[i][0], &vl[i][1], &vl[i][2]);

        aux = scanf("%s", buffer);
        aux = scanf("%lf %lf", &it[i][0], &it[i][1]);
    }

    aux = scanf("%s",  buffer);
    aux = scanf("%lf %lf %lf", &vl[N][0], &vl[N][1], &vl[N][2]);

    int snaps;
    aux = scanf("%s",   buffer);
    aux = scanf("snaps? %d\n", &snaps);
    if (snaps) {

	    aux = scanf("%s", buffer);
        aux = scanf("how many: %d", &snaps);
    }

    int nSrcs;
    double offset_srcs;
        
    aux = scanf("%s", buffer);
    aux = scanf("n_srcs: %d", &nSrcs);

    aux = scanf("%s",  buffer);
    aux = scanf("ofst_srcs: %lf", &offset_srcs);

    ofstream wOut( SPECS_DIR "wOut.dat", ios::out | ios::binary);
    _2DWave wv(Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp);
    wv.serialize(&wOut);
    wOut.close();

    ofstream vOut( SPECS_DIR "vOut.dat", ios::out | ios::binary);
    for (int i = 0; i < N + 1; i++) {
        velocity v(vl[i][0], vl[i][1], vl[i][2]);
        v.serialize(&vOut);
    }
    vOut.close();

    ofstream iOut( SPECS_DIR "iOut.dat", ios::out | ios::binary);
    for (int i = 0; i < N; i++) {
        interface j(it[i][0], it[i][1]);
        j.serialize(&iOut);
    }
    iOut.close();

    ofstream interfaces_ascii( SPECS_DIR "interfaces.dat", ios::out );
    for (int i = 0; i < N; i++) {
      interfaces_ascii << it[i][0] << "  " << it[i][1] << endl;
    }
    interfaces_ascii.close();


    ofstream nInt( SPECS_DIR "nInt.dat", ios::out);
    nInt << N << '\n';
    nInt << snaps << '\n';
    nInt << nSrcs << '\n';
    nInt << offset_srcs;

    nInt.close();

    return 0;
}
