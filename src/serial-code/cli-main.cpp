#include "stdio.h"
// #include "util/util.h"
// #include "wave/_2DWave.h"

int main(int argc, char const *argv[]) {

    double Lx, Ly, tMax, Mx, Ny, w, A, Xp, Yp, Tp;
    int N;

    // TODO: traduzir para o ingles

    printf("Seja bem-vindo ao plotter de ondas via MDF\n");

    printf("Insira o tamanho em x: \n");
    scanf("%lf", &Lx);

    printf("Insira o tamanho em y: \n");
    scanf("%lf", &Ly);

    printf("Insira o tempo maximo de animacao: ");
    scanf("%lf", &tMax);

    printf("Insira o numero de pontos em x: ");
    scanf("%lf", &Mx);

    printf("Insira o numero de pontos em y: ");
    scanf("%lf", &Ny);

    printf("Insira o omega: ");
    scanf("%lf", &w);

    printf("Insira a Amplitude da onda: ");
    scanf("%lf", &A);

    printf("Insira em a posicao em x do pico do pulso da onda: ");
    scanf("%lf", &Xp);

    printf("Insira em a posicao em y do pico do pulso da onda: ");
    scanf("%lf", &Yp);

    printf("Insira o tempo de pico do pulso da fonte: ");
    scanf("%lf", &Tp);

    printf("Digite o numero de interfaces/velocidades (interfaces + 1) \\
        que voce deseja: \n");
    scanf("%d", &N);

    double vl[N + 1][3];
    double it[N][2];

    for (int i = 0; i < N; i++) {
        printf("Digite os coeficientes da funcao de velocidade da camada %d:\n", i);
        scanf("%lf %lf %lf", vl[i][0], vl[i][1], vl[i][2]);
        printf("Digite os coeficientes da reta que descreve a interface %d:\n", i);
        scanf("%lf %lf", it[i][0], it[i][1]);
    }

    

    return 0;
}
