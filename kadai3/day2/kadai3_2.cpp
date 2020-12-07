//4619055 辰川力駆
#include <random> // 乱数生成
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

#define N 7 //符号化後のビット数
#define K 4 //デジタル情報の分けるブロックのビット数

int main()
{
    int w[K] = {0, 1, 0, 1}; //4ビットの情報w
    int x[N];                //7ビットの符号語x
    int y[N];                //7ビットの受信語y
    int ErrorPosition;       //誤り位置(1から7)
    int s[3];                //シンドロームs
    int EstimationPosition;  //誤り位置推定場所
    int cnt = 0;             //復号後のビット誤り数

    cout << "情報w : ";
    for (int i = 0; i < K; i++)
    {
        cout << w[i];
    }
    cout << endl;

    for (int i = 0; i < K; i++)
    {
        x[i] = w[i];
    }
    x[N - K + 1] = w[0] ^ w[1] ^ w[2];
    x[N - K + 2] = w[1] ^ w[2] ^ w[3];
    x[N - K + 3] = w[0] ^ w[1] ^ w[3];
    cout << "符号語x : ";
    for (int i = 0; i < N; i++)
    {
        cout << x[i];
    }
    cout << endl;

    cout << "誤り位置(1から7) : ";
    cin >> ErrorPosition;

    cout << "受信語y : ";
    for (int i = 0; i < N; i++)
    {
        y[i] = x[i];
        if (i == ErrorPosition - 1)
        {
            y[i] = x[i] ^ 1; //誤り位置は反転する
        }
        cout << y[i];
    }
    cout << endl;

    s[0] = y[0] ^ y[1] ^ y[2] ^ y[4];
    s[1] = y[1] ^ y[2] ^ y[3] ^ y[5];
    s[2] = y[0] ^ y[1] ^ y[3] ^ y[6];
    cout << "シンドロームs : ";
    for (int i = 0; i < 3; i++)
    {
        cout << s[i];
    }
    cout << endl;

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

    if (EstimationPosition == -1)
    {
        cout << "誤りはなし" << endl;
    }
    else
    {
        cout << EstimationPosition << "ビット目を反転" << endl;
    }

    y[EstimationPosition - 1] = y[EstimationPosition - 1] ^ 1;
    cout << "推定語hat(x) : ";
    for (int i = 0; i < N; i++)
    {
        cout << y[i];
    }
    cout << endl;

    for (int i = 0; i < N; i++)
    {
        cnt += x[i] ^ y[i];
    }
    cout << "複号後のビット誤り数 : " << cnt << endl;

    return 0;
}
