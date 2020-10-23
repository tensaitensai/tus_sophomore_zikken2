#include<stdio.h>
int main()
{
    int a[5]={10,5,7,6,3};//嬉しさ
    int b[5]={140,80,130,70,30};//値段
    int c=1;//論理積につかう値
    int d[32][5];//各セルに対して0か1を格納するための配列
    int i,j;//for文に使う
    int k;//論理積の結果を代入する用
    int ans1,ans2;//嬉しさと値段の合計
    int e=-100000000,f=300;//嬉しさの最大値と制約条件である300円
    int g;//10進数表記用

    for(i=0;i<32;i++)//配列dに1~32までの二進数の各ビットの数字を格納
    {
       k=i+1;
       for(j=4;j>=0;j--)
       {
           d[i][j]=k&c;
           k=k >> 1;
       }
    }
    for(i=0;i<32;i++)//嬉しさと値段の合計を求めて最適値を出す
    {
        ans1=0;
        ans2=0;
        for(j=0;j<5;j++)
        {
           ans1+=a[j]*d[i][j];
           ans2+=b[j]*d[i][j];
        }
        if(ans1>e&&ans2<=f&&ans1>0)
        {
            e=ans1;
            g=i+1;
        }
    }
    printf("最適値%d(%dのとき)\n",e,g);
    return 0;
}