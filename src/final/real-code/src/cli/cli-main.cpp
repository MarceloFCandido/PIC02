#include "stdio.h"
#include "util.h"
#include "_2DWave.h"

#define SPECS_DIR "./specs/"

using namespace std;

// TODO: Create, at least, an introduction
int main(int argc, char const *argv[]) {

    double Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp, sDx;
    int N, aux;
    char buffer[64];

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &Lx);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &Ly);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &tMax);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &Mx);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &Ny);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &w);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &A);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &Xp);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &Yp);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &Tp);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &sDx);

    aux = scanf("%s",  buffer);
    aux = scanf("%d", &N);

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
    aux = scanf("%d\n", &snaps);
    if (snaps) {
	aux = scanf("%s", buffer);
        aux = scanf("%d", &snaps);
    }

    int nRecs;
    double offset_recs;

    aux = scanf("%s", buffer);
    aux = scanf("%d", &nRecs);

    aux = scanf("%s",  buffer);
    aux = scanf("%lf", &offset_recs);

    int threads;
    aux = scanf("%s", buffer);
    aux = scanf("%d", &threads);

    printf("\n\n");
    printf("Lenght in x: %lf\n", Lx);
    printf("Lenght in y: %lf\n", Ly);
    printf("Lenght in time: %lf\n", tMax);
    printf("Points in x: %lf\n", Mx);
    printf("Points in y: %lf\n", Ny);
    printf("Frequency of the wave: %lf\n", w);
    printf("Amplitude of the wave: %lf\n", A);
    printf("Peak's X coordinate: %lf\n", Xp);
    printf("Peak's Y coordinate: %lf\n", Yp);
    printf("Peak's time instant: %lf\n", Tp);
    printf("Source offset: %lf\n", sDx);
    printf("Number of interfaces/velocities (interfaces + 1): %d\n", N);
    for (int i = 0; i < N; i++) {
        printf("vl0 vl1 vl2: %lf %lf %lf\n", vl[i][0], vl[i][1], vl[i][2]);
        printf("it0 it1:     %lf %lf\n",     it[i][0], it[i][1]);
    }
    printf("vl0 vl1 vl2: %lf %lf %lf\n", vl[N][0], vl[N][1], vl[N][2]);
    printf("Snaps: %d\n", snaps);
    printf("Nbr. receivers: %d\n", nRecs);
    printf("Ofst. receivers: %f\n", offset_recs);
    printf("Nbr. threads: %d\n", threads);
    printf("\n\n");

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
    nInt.close();

    ofstream ctrl( SPECS_DIR "ctrl.dat", ios::out);
    ctrl << snaps       << '\n';
    ctrl << nRecs       << '\n';
    ctrl << offset_recs << '\n';
    ctrl << threads     << '\n';
    ctrl << sDx;
    ctrl.close();

    return 0;
}
