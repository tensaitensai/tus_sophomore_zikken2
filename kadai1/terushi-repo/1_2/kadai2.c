#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define inf 10000000000000
#define N 500
#define eps 0.00000001
double M[2][2];
double C[2];
double h[2][2];
double function(double *x);
double h_s(double *x,double *d);//ヘッセ行列を求める
double N_T(double *x,double *d,double *g);
int main()
{
    int i,j,k;
    char fname[128];
    double x[2];
    double p,q,r;
    double g[2],d[2],norm; 
    double f;             
    FILE *fp;                     
    //ファイル操作
    printf("input filename:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    fflush(stdin);
    fp = fopen(fname, "r");
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
            fscanf(fp, "%lf", &M[i][j]); 
        } 
    }
    for(i=0;i<2;i++)
    {
        fscanf(fp, "%lf", &C[i]); 
    }
    for(i=0;i<2;i++)
    {
        
        fscanf(fp, "%lf", &x[i]); 
    }
    fclose(fp);
    //初期化表示
    printf("Q=\n");
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
            printf("%5.lf",M[i][j]);
        }
        printf("\n");
    }
    printf("C=\n");
    for(i=0;i<2;i++)
    {
        printf("%5.lf",C[i]);
    }
    printf("\n");
    printf("x=\n");
    for(i=0;i<2;i++)
    {
        printf("%5.lf",x[i]);
    }
    printf("\n");
    printf("------------------------------------\n");
    //ここから開始
    k=0;
    p=M[0][0];
    q=M[0][1];
    r=M[1][1];
    while(1)
    {
        g[0]=p*x[0]+q*x[1]+C[0]+2*(x[0]-x[1])*exp(pow(x[0]-x[1],2));
        g[1]=r*x[1]+q*x[0]+C[1]-2*(x[0]-x[1])*exp(pow(x[0]-x[1],2));
        N_T(x,d,g);
        norm=sqrt((pow(g[0],2)+pow(g[1],2)));
        f=function(x);
        if(norm<eps||d[0]==inf)
        {
            break;
        }
        
            printf("%d回目\n",k);
            printf("現在の位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n",x[0],x[1],f,g[0],g[1],norm);
            printf("------------------------------------\n");
        
        
        x[0]=x[0]+d[0];
        x[1]=x[1]+d[1];
        if(k>N)
        {
            break;
        }
        k++;
    }
    printf("最終結果\n");
    printf("回数=%d\n現在の位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n",k,x[0],x[1],f,g[0],g[1],norm);
    return 0;
}
double function(double *x)
{
    double fun;
    double p,q,r;
    p=M[0][0];
    q=M[0][1];
    r=M[1][1];
    fun=0.5*(p*pow(x[0],2)+2*q*x[0]*x[1]+r*pow(x[1],2))+C[0]*x[0]+C[1]*x[1]+exp(pow((x[0]-x[1]),2));
    return fun;
}
double h_g(double *x,double *d)
{
    double p,q,r;
    p=M[0][0];
    q=M[0][1];
    r=M[1][1];
    h[0][0]=p+2*exp(pow(x[0]-x[1],2))*(1+2*pow(x[0]-x[1],2));
    h[0][1]=q-2*exp(pow(x[0]-x[1],2))*(1+2*pow(x[0]-x[1],2));
    h[1][0]=h[0][1];
    h[1][1]=r+2*exp(pow(x[0]-x[1],2))*(1+2*pow(x[0]-x[1],2));
}
double N_T(double *x,double *d,double *g)
{
    double h_gg[2][2];
    h_g(x,d);
    if(h[0][0]*h[1][1]-h[0][1]*h[1][0]==0)//正則かどうかの判定
    {
        d[0]=inf;
        d[1]=inf;
        printf("非正則\n");
    }
    else
    {
        h_gg[0][0]=1/(h[0][0]*h[1][1]-h[0][1]*h[1][0])*h[1][1];
        h_gg[1][0]=1/(h[0][0]*h[1][1]-h[0][1]*h[1][0])*-h[1][0];
        h_gg[1][1]=1/(h[0][0]*h[1][1]-h[0][1]*h[1][0])*h[0][0];
        h_gg[0][1]=1/(h[0][0]*h[1][1]-h[0][1]*h[1][0])*-h[0][1];
        d[0]=-g[0]*h_gg[0][0]-g[1]*h_gg[1][0];
        d[1]=-g[0]*h_gg[0][1]-g[1]*h_gg[1][1];
    }
} 