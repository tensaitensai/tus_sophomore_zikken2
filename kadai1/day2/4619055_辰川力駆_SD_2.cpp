//4619055 辰川力駆
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 1000
#define eps 0.00000001 //停止条件
double M[5][3];
double func(double *x); //f2の式を用いている
double Armijo(double *x, double *d, double *g);
int main()
{
    int i, j, k;
    double alpha;
    char fname[128];
    double x[2];
    double p, q, r;
    double g[3], d[2], norm;
    double f;
    FILE *fp;

    printf("input filename:");
    fgets(fname, sizeof(fname), stdin);
    fname[strlen(fname) - 1] = '\0';
    fflush(stdin);
    fp = fopen(fname, "r");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fscanf(fp, "%lf", &M[i][j]);
        }
    }
    for (i = 0; i < 2; i++)
    {
        fscanf(fp, "%lf", &x[i]);
    }
    fclose(fp);
    //初期化表示
    printf("a=\n");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%5.lf", M[i][j]);
        }
        printf("\n");
    }
    printf("x=\n");
    for (i = 0; i < 2; i++)
    {
        printf("%5.lf", x[i]);
    }
    printf("\n");
    printf("------------------------------------\n");
    k = 0;
    while (1)
    {
        g[0] = M[1][0] + M[1][1] * x[1] + 2 * M[2][0] * x[0] + 3 * M[3][0] * pow(x[0], 2) + 4 * M[4][0] * pow(x[0], 3);
        g[1] = M[0][1] + 2 * M[0][2] * x[1] + M[1][1] * x[0];
        norm = sqrt((pow(g[0], 2) + pow(g[1], 2)));
        f = function(x);
        d[0] = -g[0];
        d[1] = -g[1];
        alpha = Armijo(x, d, g);
        if (norm < eps)
        {
            break;
        }
        if (k <= 100 && k % 10 == 0)
        {
            printf("%d回目\n", k);
            printf("現在の位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n", x[0], x[1], f, g[0], g[1], norm);
            printf("------------------------------------\n");
        }
        else if (k > 100 && k % 100 == 0)
        {
            printf("%d回目\n", k);
            printf("現在の位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n", x[0], x[1], f, g[0], g[1], norm);
            printf("------------------------------------\n");
        }

        x[0] = x[0] + alpha * d[0];
        x[1] = x[1] + alpha * d[1];
        k++;
        if (k > N)
        {
            break;
        }
    }
    printf("最終結果\n");
    printf("回数=%d\n現在の位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n", k - 1, x[0], x[1], f, g[0], g[1], norm);
    return 0;
}

double Armijo(double *x, double *d, double *g)
{
    double alpha = 1.0;
    double xi = 0.1;
    double tau = 0.5;
    double f1, f2, f3;
    double z;
    double y[2];
    while (1)
    {
        y[0] = x[0] + alpha * d[0];
        y[1] = x[1] + alpha * d[1];
        f1 = func(y);
        f2 = func(x);
        z = xi * (g[0] * d[0] + g[1] * d[1]) * alpha;
        if (f1 <= f2 + z)
        {
            break;
        }
        else
        {
            alpha = tau * alpha;
        }
    }
    return alpha;
}

//f2の式を用いている
double func(double *x)
{
    return M[0][1] * x[1] + M[0][2] * pow(x[1], 2) + M[1][0] * x[0] + M[1][1] * x[0] * x[1] + M[2][0] * pow(x[0], 2) + M[3][0] * pow(x[0], 3) + M[4][0] * pow(x[0], 4);
}