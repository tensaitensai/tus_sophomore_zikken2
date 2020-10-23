#include<stdio.h>
#define N 5
#define inf -100000000
#define value 300
int main()
{
    int a[N]={10,5,7,6,3};//嬉しさ
    int b[N]={140,80,130,70,30};//値段
    char okashi[N]={'C','c','p','G','g'};
    int c=1;//論理積につかう値
    int i,j;//for文に使う
    int ans1,ans2;//嬉しさと値段の合計
    int max=inf,f=value;//嬉しさの最大値と制約条件である300円
    int x,k;

    for(i=0;i<32;i++)//嬉しさと値段の合計を求めて最適値を出す
    {
        ans1=0;
        ans2=0;
        for(j=0;j<5;j++)
        {
            if(((i>>j)&c)==1)
            {
                ans1+=a[j];
                ans2+=b[j];
            }
           
        }
        if(ans1>max&&ans2<=f)
        {
            max=ans1;
            x=i;
        }
    }
    printf("Cはチョコ,cはクッキーpはポテト,Gはグミ,gはガムです.\n");
    printf("嬉しさの最高の値は%d\n",max);
    for(int i=0;i<N;i++)
    {
        k=x&c;  
        if(k==1)
        {
            printf("お菓子は,%c\n",okashi[i]);
        }
        x=x>>1;
    }
    return 0;
}