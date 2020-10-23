#include<stdio.h>
#define N 10000
int main()
{
    int K[2]={2,3};
    double Ca[2]={0.1,0.3};
    double Mg[2]={0.1,0.1};
    double yen[2]={0.1,0.15};
    int i,j;
    double a;
    int b,c;
    int d=10000000;
    int ans1,ans2,ans3,ans4;
    for(i=1;i<N;i++)
    {
        for(j=1;j<N;j++)
        {
            ans1=yen[1]*i+yen[2]*j;
            ans2=K[1]*i+K[2]*j;
            ans3=Ca[1]*i+Ca[2]*j;
            ans4=Mg[1]*i+Mg[2]*j;
            if(ans1<d&&ans2>=2500&&ans3>=650&&ans4>=350)
            {
                d=ans1;
                b=i;
                c=j;
            }
        }
    }
    printf("最適値%d,最適解(%d,%d)\n",d,b,c);
    return 0;
}