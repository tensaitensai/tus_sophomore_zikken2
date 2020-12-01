//4619055 辰川力駆
#include <random> // 乱数生成
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

#define SIM 1000000

#define seed 55 //学籍番号下２桁
#define K 4     //系列長

mt19937 mt(seed); //メルセンヌ・ツイスタ

int main()
{
    srand(seed);
    int w[4], e[4], y[4];

    uniform_real_distribution<double> rand_real(0, 1);
    normal_distribution<double> rand_n(0, 0.3);

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
                w[j] = rand_real(mt) * 2; //2倍することで0.5より大きいか小さいかを判定できる。
            }
            for (int j = 0; j < K; j++)
            {
                if (rand_real(mt) <= ep)
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