#include "stdio.h"
#include "util/util.h"
#include "wave/_2DWave.h"

using namespace std;

int main(int argc, char const *argv[]) {

    double Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp;
    int N;

    // TODO: traduzir para o ingles

    printf("Seja bem-vindo ao plotter de ondas via MDF\n");

    printf("Insira o tamanho em x: \n");
    scanf("%lf", &Lx);

    printf("Insira o tamanho em y: \n");
    scanf("%lf", &Ly);

    printf("Insira o tempo maximo de animacao: \n");
    scanf("%lf", &tMax);

    printf("Insira o numero de pontos em x: \n");
    scanf("%lf", &Mx);

    printf("Insira o numero de pontos em y: \n");
    scanf("%lf", &Ny);

    printf("Insira o omega: \n");
    scanf("%lf", &w);

    printf("Insira a Amplitude da onda: \n");
    scanf("%lf", &A);

    printf("Insira em a posicao em x do pico do pulso da onda: \n");
    scanf("%lf", &Xp);

    printf("Insira em a posicao em y do pico do pulso da onda: \n");
    scanf("%lf", &Yp);

    printf("Insira o tempo de pico do pulso da fonte: \n");
    scanf("%lf", &Tp);

    printf("Digite o numero de interfaces/velocidades (interfaces + 1) \\
        que voce deseja: \n");
    scanf("%d", &N);

    double vl[N + 1][3];
    double it[N][2];

    for (int i = 0; i < N; i++) {
        printf("Digite os coeficientes da funcao de velocidade da camada %d:\n", i);
        scanf("%lf %lf %lf", &vl[i][0], &vl[i][1], &vl[i][2]);
        printf("Digite os coeficientes da reta que descreve a interface %d:\n", i);
        scanf("%lf %lf", &it[i][0], &it[i][1]);
    }

    printf("Digite os coeficientes da funcao de velocidade da camada %d:\n", N);
    scanf("%lf %lf %lf", &vl[N][0], &vl[N][1], &vl[N][2]);

    printf("%lf\n", Lx);
    printf("%lf\n", Ly);
    printf("%lf\n", tMax);
    printf("%lf\n", Mx);
    printf("%lf\n", Ny);
    printf("%lf\n", w);
    printf("%lf\n", A);
    printf("%lf\n", Xp);
    printf("%lf\n", Yp);
    printf("%lf\n", Tp);
    printf("%d\n", N);
    for (int i = 0; i < N; i++) {
        printf("%lf %lf %lf\n", vl[i][0], vl[i][1], vl[i][2]);
        printf("%lf %lf\n", it[i][0], it[i][1]);
    }
    printf("%lf %lf %lf\n", vl[N][0], vl[N][1], vl[N][2]);

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
    nInt << N;
    nInt.close();

    return 0;
}
