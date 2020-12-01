//4619055 辰川力駆
#include <random> // 乱数生成
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

#define SIM 1000000

#define real_rand (double)rand() / RAND_MAX; //RAND_MAXで割ることで0から1を返すようにしている。
#define seed 55                              //学籍番号下２桁
#define K 4                                  //系列長

int main()
{
    srand(seed);
    int w[4], e[4], y[4];

    cout << "# SIM:" << SIM << endl;
    cout << "# ep   # BER" << endl;

    double ep = 0;
    int count = 0;
    for (int i = 0; i < 12; i++) //12回で設定
    {
        count = 0;
        ep = 0.0001 * (i + 1);

        for (int s = 0; s < SIM; s++)
        {
            for (int j = 0; j < K; j++)
            {
                double rd = real_rand; //乱数発生
                w[j] = rd * 2;         //2倍することで0.5より大きいか小さいかを判定できる。
            }
            for (int j = 0; j < K; j++)
            {
                double rd = real_rand; //乱数発生
                if (rd <= ep)
                {
                    e[j] = 1;
                }
                else
                {
                    e[j] = 0;
                }
            }
            for (int j = 0; j < K; j++)
            {
                y[j] = w[j] ^ e[j];
                count += w[j] ^ y[j];
            }
        }
        cout << fixed << setprecision(4) << ep;
        cout.unsetf(ios::fixed);
        cout << fixed << setprecision(7) << " " << (double)count / (K * SIM) << endl;
    }

    return 0;
}