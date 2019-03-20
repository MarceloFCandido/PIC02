#include "stdio.h"
#include "util/util.h"
#include "wave/_2DWave.h"

using namespace std;

// TODO: traduzir para o ingles

int main(int argc, char const *argv[]) {

    double Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp;
    int N, aux;

    printf("Seja bem-vindo ao plotter de ondas via MDF\n");

    printf("Insira o tamanho em x: \n");
    aux = scanf("%lf", &Lx);

    printf("Insira o tamanho em y: \n");
    aux = scanf("%lf", &Ly);

    printf("Insira o tempo maximo de animacao: \n");
    aux = scanf("%lf", &tMax);

    printf("Insira o numero de pontos em x: \n");
    aux = scanf("%lf", &Mx);

    printf("Insira o numero de pontos em y: \n");
    aux = scanf("%lf", &Ny);

    printf("Insira o omega: \n");
    aux = scanf("%lf", &w);

    printf("Insira a Amplitude da onda: \n");
    aux = scanf("%lf", &A);

    printf("Insira em a posicao em x do pico do pulso da onda: \n");
    aux = scanf("%lf", &Xp);

    printf("Insira em a posicao em y do pico do pulso da onda: \n");
    aux = scanf("%lf", &Yp);

    printf("Insira o tempo de pico do pulso da fonte: \n");
    aux = scanf("%lf", &Tp);

    printf("Digite o numero de interfaces/velocidades (interfaces + 1) \\
        que voce deseja: \n");
    aux = scanf("%d", &N);

    double vl[N + 1][3];
    double it[N][2];

    for (int i = 0; i < N; i++) {
        printf("Digite os coeficientes da funcao de velocidade da camada %d:\n", i);
        scanf("%lf %lf %lf", &vl[i][0], &vl[i][1], &vl[i][2]);
        printf("Digite os coeficientes da reta que descreve a interface %d:\n", i);
        scanf("%lf %lf", &it[i][0], &it[i][1]);
    }

    printf("Digite os coeficientes da funcao de velocidade da camada %d:\n", N);
    aux = scanf("%lf %lf %lf", &vl[N][0], &vl[N][1], &vl[N][2]);

    int snaps;
    printf("Would you like snapshots? (traces will be generated anyway) (1/0)");
    aux = scanf("%d\n", &snaps);
    if (snaps) {
        printf("How many snapshots would you like? ");
        aux = scanf("%d", &snaps);
    }

    int nSrcs;
    double offset_srcs;
    printf("How many sources would you like?"); scanf("%d", &nSrcs);
    printf("Which offset between sources would like?"); scanf("%lf", &offset_srcs);

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
    printf("Number of interfaces/velocities (interfaces + 1): %d\n", N);
    for (int i = 0; i < N; i++) {
        printf("%lf %lf %lf\n", vl[i][0], vl[i][1], vl[i][2]);
        printf("%lf %lf\n", it[i][0], it[i][1]);
    }
    printf("%lf %lf %lf\n", vl[N][0], vl[N][1], vl[N][2]);
    printf("%d\n", snaps);

    ofstream wOut("data/specs/wOut.dat", ios::out | ios::binary);
    _2DWave wv(Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp);
    wv.serialize(&wOut);
    wOut.close();

    ofstream vOut("data/specs/vOut.dat", ios::out | ios::binary);
    for (int i = 0; i < N + 1; i++) {
        velocity v(vl[i][0], vl[i][1], vl[i][2]);
        v.serialize(&vOut);
    }
    vOut.close();

    ofstream iOut("data/specs/iOut.dat", ios::out | ios::binary);
    for (int i = 0; i < N; i++) {
        interface j(it[i][0], it[i][1]);
        j.serialize(&iOut);
    }
    iOut.close();

    ofstream nInt("data/specs/nInt.dat", ios::out);
    nInt << N << '\n';
    nInt << snaps << '\n';
    nInt << nSrcs << '\n';
    nInt << offset_srcs;

    nInt.close();

    return 0;
}
