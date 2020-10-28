//4619055 辰川力駆
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 1000
#define res 0.00000001 ///停止条件

double func(double *x);                         ///f1の式を用いている
double Armijo(double *x, double *d, double *g); //Armijo

double Q[2][2]; //Qのデータを保存
double c[2];    //cのデータを保存

int main()
{
    char fname[128];
    double x[2];
    double p, q, r;
    double d[2], norm;
    double nabla[2];
    double f;
    FILE *fp;
    int i, j, k;
    double alpha;

    printf("input filename:");
    fgets(fname, sizeof(fname), stdin);
    fname[strlen(fname) - 1] = '\0';
    fflush(stdin);
    fp = fopen(fname, "r");

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            fscanf(fp, "%lf", &Q[i][j]);
        }
    }
    for (i = 0; i < 2; i++)
    {
        fscanf(fp, "%lf", &c[i]);
    }
    for (i = 0; i < 2; i++)
    {
        fscanf(fp, "%lf", &x[i]);
    }
    fclose(fp);

    printf("Q=\n");
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("%4.lf", Q[i][j]);
        }
        printf("\n");
    }
    printf("C=\n");
    for (i = 0; i < 2; i++)
    {
        printf("%4.lf", c[i]);
    }
    printf("\n");
    printf("x=\n");
    for (i = 0; i < 2; i++)
    {
        printf("%4.lf", x[i]);
    }
    printf("\n");
    printf("-----\n");

    p = Q[0][0];
    q = Q[0][1];
    r = Q[1][1];
    k = 0;
    while (1)
    {
        nabla[0] = p * x[0] + q * x[1] + c[0] + 2 * (x[0] - x[1]) * exp((x[0] - x[1]) * (x[0] - x[1]));
        nabla[1] = q * x[0] + r * x[1] + c[1] - 2 * (x[0] - x[1]) * exp((x[0] - x[1]) * (x[0] - x[1]));

        d[0] = -nabla[0];
        d[1] = -nabla[1];

        norm = sqrt(nabla[0] * nabla[0] + nabla[1] * nabla[1]); ///ノルムを計算

        f = func(x);
        alpha = Armijo(x, d, nabla);

        if (k <= 5 || (k <= 100 && k % 10 == 0) || k % 100 == 0) //5回目までと10n回目,100n回目(n=1,2,3,...10)を表示
        {
            printf("%d回目\n", k);
            printf("現在位置=(%.8lf,%.8lf)\n目的関数=%.8lf\n勾配ベクトル=(%.8lf,%.8lf)\nノルム=%.8lf\n", x[0], x[1], f, nabla[0], nabla[1], norm);
            printf("-----\n");
        }

        x[0] = x[0] + alpha * d[0];
        x[1] = x[1] + alpha * d[1];
        k++;

        if (norm < res) ///nablaのノルムが10^{-8}を越えていたら停止
        {
            break;
        }
        if (k > N) ///反復回数が1000回越えたら停止
        {
            break;
        }
    }

    printf("--結果--\n");
    printf("%d回\n現在位置=(%.8lf,%.8lf)\n目的関数=%.8lf\n勾配ベクトル=(%.8lf,%.8lf)\nノルム=%.8lf\n", k - 1, x[0], x[1], f, nabla[0], nabla[1], norm);
    return 0;
}

double Armijo(double *x, double *d, double *nabla)
{
    double alpha = 1.0;
    double xi = 0.1;  ///今回の課題条件
    double tau = 0.5; ///今回の課題条件
    double fx, fy;
    double y[2];

    ///f(x_k)を求める
    fx = func(x);

    while (1)
    {
        ///新しいalphaに対してのfyを求める
        y[0] = x[0] + alpha * d[0];
        y[1] = x[1] + alpha * d[1];
        fy = func(y);

        if (fy <= fx + xi * (nabla[0] * d[0] + nabla[1] * d[1]) * alpha) //Armijo条件
        {
            break;
        }

        alpha = tau * alpha; //alphaの更新
    }
    return alpha;
}

// f1の式を用いている
double func(double *x)
{
    double p, q, r;
    p = Q[0][0];
    q = Q[0][1];
    r = Q[1][1];
    return 0.5 * (p * x[0] * x[0] + 2 * q * x[0] * x[1] + r * x[1] * x[1]) + c[0] * x[0] + c[1] * x[1] + exp((x[0] - x[1]) * (x[0] - x[1]));
}