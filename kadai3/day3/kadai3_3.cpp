//4619055 辰川力駆
#include <random> // 乱数生成
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

#define N 7         //符号化後のビット数
#define K 4         //デジタル情報の分けるブロックのビット数
#define seed 55     //学籍番号下２桁
#define SIM 1000000 //シミュレーション回数

mt19937 mt(seed); //メルセンヌ・ツイスタ

int main()
{
    uniform_real_distribution<double> rand_real(0, 1);
    normal_distribution<double> rand_n(0, 0.3);

    int w[K];                  //4ビットの情報w
    int x[N];                  //7ビットの符号語x
    int e[N];                  //7ビットの雑音ベクトルe
    int y[N];                  //7ビットの受信語y
    int s[3];                  //シンドロームs
    int bit_count = 0;         //シミュレーションごとの毎回のビット誤り数を計算
    int total_bit_count = 0;   //誤ったビットの総数
    int total_block_count = 0; //ブロック単位の誤りの総数
    int EstimationPosition;    //誤り位置推定場所
    double ep;                 //誤り率

    cout << "# SIM:" << SIM << endl;
    cout << "#BSCの誤り率 #復号後ビット誤り率 #復号後ブロック誤り率" << endl;

    for (int k = 0; k < 5; k++)
    {
        ep = 0.005 + k * 0.004;
        total_bit_count = 0;
        total_block_count = 0;

        for (int sim = 0; sim < SIM; sim++)
        {
            bit_count = 0;

            for (int i = 0; i < K; i++) //K=4 ビットの情報 w を乱数を用いて生成
            {
                w[i] = rand_real(mt) * 2;
            }

            for (int i = 0; i < K; i++) //符号化により, w から x を生成
            {
                x[i] = w[i];
            }
            x[N - K + 1] = w[0] ^ w[1] ^ w[2];
            x[N - K + 2] = w[1] ^ w[2] ^ w[3];
            x[N - K + 3] = w[0] ^ w[1] ^ w[3];

            for (int i = 0; i < N; i++) //乱数を用いて N =7 ビットの雑音ベクトル e を生成
            {
                if (rand_real(mt) <= ep)
                {
                    e[i] = 1;
                }
                else
                {
                    e[i] = 0;
                }
            }

            for (int i = 0; i < N; i++) //xとeの排他的論理和を計算してyとする
            {
                y[i] = x[i] ^ e[i];
            }

            s[0] = y[0] ^ y[1] ^ y[2] ^ y[4]; //yから復号してxハット、wハットを得る
            s[1] = y[1] ^ y[2] ^ y[3] ^ y[5];
            s[2] = y[0] ^ y[1] ^ y[3] ^ y[6];

            int point = 0;
            for (int i = 0; i < 3; i++)
            {
                point += s[i] * pow(2, 2 - i);
            }
            switch (point)
            {
            case 5:
                EstimationPosition = 1;
                break;
            case 7:
                EstimationPosition = 2;
                break;
            case 6:
                EstimationPosition = 3;
                break;
            case 3:
                EstimationPosition = 4;
                break;
            case 4:
                EstimationPosition = 5;
                break;
            case 2:
                EstimationPosition = 6;
                break;
            case 1:
                EstimationPosition = 7;
                break;
            default:
                EstimationPosition = -1;
                break;
            }
            if (EstimationPosition != -1)
            {
                y[EstimationPosition - 1] = y[EstimationPosition - 1] ^ 1;
            }

            for (int i = 0; i < K; i++) //w と wハットを比較し、 ビット誤り数をカウント(つまり4ビットまでを見れば良い)
            {
                bit_count += w[i] ^ y[i];
            }

            total_bit_count += bit_count;

            if (bit_count != 0)
            {
                total_block_count += 1;
            }
        }
        cout << ep;
        cout << fixed << setprecision(8) << "        " << (double)total_bit_count / (K * SIM);
        cout << fixed << setprecision(6) << "          " << (double)total_block_count / SIM << endl;
        cout.unsetf(ios::fixed); //体裁を整えている
    }
    return 0;
}
