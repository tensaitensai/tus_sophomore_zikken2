//4619055 辰川力駆
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 1000
#define eps 0.00000001 //停止条件

double func(double *x);                         //f1の式を用いている
double Armijo(double *x, double *d, double *g); //Armijo

double Q[2][2]; //Qのデータを保存
double C[2];    //cのデータを保存

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

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            fscanf(fp, "%lf", &Q[i][j]);
        }
    }
    for (i = 0; i < 2; i++)
    {
        fscanf(fp, "%lf", &C[i]);
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
            printf("%5.lf", Q[i][j]);
        }
        printf("\n");
    }
    printf("C=\n");
    for (i = 0; i < 2; i++)
    {
        printf("%5.lf", C[i]);
    }
    printf("\n");
    printf("x=\n");
    for (i = 0; i < 2; i++)
    {
        printf("%5.lf", x[i]);
    }
    printf("\n");
    printf("------------------------------------\n");

    k = 0;
    p = Q[0][0];
    q = Q[0][1];
    r = Q[1][1];
    while (1)
    {
        //勾配ベクトル
        g[0] = p * x[0] + q * x[1] + C[0] + 2 * (x[0] - x[1]) * exp(pow(x[0] - x[1], 2));
        g[1] = r * x[1] + q * x[0] + C[1] - 2 * (x[0] - x[1]) * exp(pow(x[0] - x[1], 2));
        //探索方向
        d[0] = -g[0];
        d[1] = -g[1];
        norm = sqrt((pow(g[0], 2) + pow(g[1], 2)));
        f = func(x);
        alpha = Armijo(x, d, g);
        if (norm < eps)
        {
            break;
        }
        if (k <= 100 && k % 5 == 0)
        {
            printf("%d回目\n", k);
            printf("現在位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n", x[0], x[1], f, g[0], g[1], norm);
            printf("------------------------------------\n");
        }
        else if (k > 100 && k % 100 == 0)
        {
            printf("%d回目\n", k);
            printf("現在位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n", x[0], x[1], f, g[0], g[1], norm);
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

    printf("--結果--\n");
    printf("回数=%d\n現在位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n", k - 1, x[0], x[1], f, g[0], g[1], norm);
    return 0;
}

double Armijo(double *x, double *d, double *g)
{
    double alpha = 1.0;
    double xi = 0.1;
    double tau = 0.5;
    double f1, f2, f3;
    double z;
    double p, q, r;
    double y[2];
    p = Q[0][0];
    q = Q[0][1];
    r = Q[1][1];
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

//f1の式を用いている
double func(double *x)
{
    double f;
    double p, q, r;
    p = Q[0][0];
    q = Q[0][1];
    r = Q[1][1];
    f = 0.5 * (p * pow(x[0], 2) + 2 * q * x[0] * x[1] + r * pow(x[1], 2)) + C[0] * x[0] + C[1] * x[1] + exp(pow((x[0] - x[1]), 2));
    return f;
}