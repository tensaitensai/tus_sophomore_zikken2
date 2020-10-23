#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>//expとpowを使うため
#define N 1000//反復回数の最大
#define eps 0.00000001
double M[2][2];
double C[2];
double function(double *x);//目的関数
double Armijo(double *x,double *d,double *g);//アルミホ条件
int main()
{
    int i,j,k;
    double alpha;
    char fname[128];
    double x[2];
    double p,q,r;
    double g[3],d[2],norm; 
    double f;             
    FILE *fp;                     
    //データのファイル操作
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
        //勾配ベクトル
        g[0]=p*x[0]+q*x[1]+C[0]+2*(x[0]-x[1])*exp(pow(x[0]-x[1],2));
        g[1]=r*x[1]+q*x[0]+C[1]-2*(x[0]-x[1])*exp(pow(x[0]-x[1],2));
        //探索方向
        d[0]=-g[0];
        d[1]=-g[1];
        norm=sqrt((pow(g[0],2)+pow(g[1],2)));
        f=function(x);
        alpha=Armijo(x,d,g);
        if(norm<eps)
        {
            break;
        }
        if(k<=100&&k%5==0)
        {
            printf("%d回目\n",k);
            printf("現在の位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n",x[0],x[1],f,g[0],g[1],norm);
            printf("------------------------------------\n");
        }
        else if(k>100&&k%100==0)
        {
            printf("%d回目\n",k);
            printf("現在の位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n",x[0],x[1],f,g[0],g[1],norm);
            printf("------------------------------------\n");
        }
        
        x[0]=x[0]+alpha*d[0];
        x[1]=x[1]+alpha*d[1];
        k++;
        if(k>N)
        {
            break;
        }
    }
    printf("最終結果\n");
    printf("回数=%d\n現在の位置=(%lf,%lf)\n目的関数=%lf\n勾配ベクトル=(%lf,%lf)\n,ノルム=%lf\n",k-1,x[0],x[1],f,g[0],g[1],norm);
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
double Armijo(double *x,double *d,double *g)
{
    double alpha=1.0;
    double xi=0.1;
    double tau=0.5;
    double f1,f2,f3;
    double z;
    double p,q,r;
    double y[2];
    p=M[0][0];
    q=M[0][1];
    r=M[1][1];    
    while(1)
    {
        y[0]=x[0]+alpha*d[0];
        y[1]=x[1]+alpha*d[1];
        f1=function(y);
        f2=function(x);
        z=xi*(g[0]*d[0]+g[1]*d[1])*alpha;
        if(f1<=f2+z)
        {
            break;
        }
        else
        {
            alpha=tau*alpha;
        }
    }
    return alpha;
} 