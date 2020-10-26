// newton1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define eps 0.00000001 // ε

double M[3][3];
double c[3];

// 点xにおける目的関数値を計算
double comp_val(double *x);

// 点x, において探索方向d に対するアルミホ探索，g = x 勾配ベクトル
double line_search(double *x, double *g, double *d);

int _tmain(int argc, _TCHAR *argv[])
{
	int i, j, k;					  // for，実行回数
	double norm, expval;			  // 目的関数値，ノルム
	double x[3], d[3], g[3], h[3][3]; // ベクトル，探索方向，勾配ベクトル，ヘッセ行列
	double inverse_matrix;			  // ヘッセ行列の逆行列の係数
	char fname[128];

	errno_t error;
	FILE *infile;

	printf("input filename:");
	fgets(fname, sizeof(fname), stdin);
	fname[strlen(fname) - 1] = '\0';
	fflush(stdin);

	if (error = fopen_s(&infile, fname, "r") != 0)
	{
		printf("ファイルがありません\n");
	}

	else
	{
		// ファイルからデータを読み込む
		for (i = 1; i <= 2; i++)
		{
			for (j = 1; j <= 2; j++)
			{
				fscanf_s(infile, " %lf", &M[i][j]);
			}
		}
		for (i = 1; i <= 2; i++)
		{
			fscanf_s(infile, " %lf", &c[i]);
		}
		for (i = 1; i <= 2; i++)
		{
			fscanf_s(infile, " %lf", &x[i]);
		}
		fclose(infile);

		// 主要部分：各自作成
		k = 0; // 初期化
		expval = 0;

		// 初期設定の表示
		printf("Q =\n");
		for (i = 1; i <= 2; i++)
		{
			for (j = 1; j <= 2; j++)
			{
				printf(" %5.1f", M[i][j]);
			}
			printf("\n");
		}

		printf("c =\n");
		for (i = 1; i <= 2; i++)
		{
			printf(" %5.1f", c[i]);
		}
		printf("\n");

		printf("x =\n");
		for (i = 1; i <= 2; i++)
		{
			printf(" %5.1f", x[i]);
		}
		printf("\n");

		while (1)
		{
			// 勾配ベクトルの計算
			g[1] = M[1][1] * x[1] + M[1][2] * x[2] + c[1] + 2 * (x[1] - x[2]) * exp(pow(x[1] - x[2], 2));
			g[2] = M[2][1] * x[1] + M[2][2] * x[2] + c[2] - 2 * (x[1] - x[2]) * exp(pow(x[1] - x[2], 2));

			//勾配ベクトルのノルムの計算
			norm = sqrt(pow(g[1], 2) + pow(g[2], 2));

			if (norm < eps)
			{ // 収束条件を満たしたら終了
				break;
			}

			// ヘッセ行列
			h[1][1] = M[1][1] + 2 * exp(pow(x[1] - x[2], 2)) + 4 * pow(x[1] - x[2], 2) * exp(pow(x[1] - x[2], 2));
			h[1][2] = M[1][2] - 2 * exp(pow(x[1] - x[2], 2)) - 4 * pow(x[1] - x[2], 2) * exp(pow(x[1] - x[2], 2));
			h[2][1] = M[1][2] - 2 * exp(pow(x[1] - x[2], 2)) - 4 * pow(x[1] - x[2], 2) * exp(pow(x[1] - x[2], 2));
			h[2][2] = M[2][2] + 2 * exp(pow(x[1] - x[2], 2)) + 4 * pow(x[1] - x[2], 2) * exp(pow(x[1] - x[2], 2));

			// 正則条件
			if (h[1][1] * h[2][2] - h[1][2] * h[2][1] == 0)
			{ // ヘッセ行列が正則で無かったら終了する
				break;
			}

			// ヘッセ行列の逆行列の計算
			inverse_matrix = 1 / (h[1][1] * h[2][2] - h[1][2] * h[2][1]);

			// 探索方向
			d[1] = -inverse_matrix * (h[2][2] * g[1] - h[1][2] * g[2]);
			d[2] = -inverse_matrix * (-h[2][1] * g[1] + h[1][1] * g[2]);

			// x_kを更新する
			x[1] = x[1] + d[1];
			x[2] = x[2] + d[2];

			// 目的関数値を代入
			expval = comp_val(x);

			// kを更新する
			k += 1;

			if (k > 1000)
			{ // 反復回数1000回超えると終了
				break;
			}

			// 出力
			printf("------------------------------------\n");
			printf("回復回数：%d \n現在点x_k = (%f,%f) \n目的関数値 = %f \n勾配ベクトル = (%f,%f) \nノルム = %f\n", k, x[1], x[2], expval, g[1], g[2], norm);
			printf("ヘッセ行列 = %6.1f %6.1f\n　　　  　　 %6.1f %6.1f\n", h[1][1], h[1][2], h[2][1], h[2][2]);
		}

		// 最終結果の出力
		printf("\n☆ -・-・-・-・ FINAL ・-・-・-・- ☆\n");
		printf("回復回数：%d \n現在点x_k = (%f,%f) \n目的関数値 = %f \n勾配ベクトル = (%f,%f) \nノルム = %f\n", k, x[1], x[2], expval, g[1], g[2], norm);
		printf("ヘッセ行列 = %6.1f %6.1f\n　　　 　 　 %6.1f %6.1f\n", h[1][1], h[1][2], h[2][1], h[2][2]);
	}
	return 0;
}

// 点xにおける目的関数値を計算
double comp_val(double *x)
{
	double val;

	val = 0.5 * (M[1][1] * pow(x[1], 2) + 2 * M[1][2] * x[1] * x[2] + M[2][2] * pow(x[2], 2)) + (c[1] * x[1] + c[2] * x[2]) + exp(pow(x[1] - x[2], 2));

	return val;
}
