/* program for generating random Q and c of  f(x) = 1/2x^TQx + c^Tx+exp((x_1-x_2)^2) */
/* three instances of Q and c are generated along with three initial solutions for each Q,c */ 
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

int main(void)
{
  int bangou;
  int i, j, k;
  int numb;
  int p, q, r;
  double Q[2][2];
  double c[2], x[2]; 
  char fname[128], idnum[128];
  FILE *outfile;

  printf("学籍番号を入力してください:");
  fgets(idnum, sizeof(idnum), stdin);
  idnum[strlen(idnum)-1] = '\0';
  fflush(stdin);

  bangou = atoi(idnum);
  printf("乱数シード = %d\n", bangou);
  srand(bangou);

  printf("出力ファイルを指定してください:");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname)-1] = '\0';
  fflush(stdin);

  outfile = fopen(fname,"w");  

  for (numb=1; numb<=3; numb++){
    p = rand()%10+1;
    r = rand()%17-8;
    q = rand()%10 + 1 + r*r/p;
    Q[0][0] = (double)p;
    Q[1][1] = (double)q;
    Q[0][1] = Q[1][0] = (double)r;
    for (i=0; i<2; i++){c[i] = (double)(rand()%17-8);}
  
    fprintf(outfile, "data set %d\n", numb);
    fprintf(outfile, "matrix Q\n");
    for (i=0; i<2; i++){
      for (j=0; j<2; j++){fprintf(outfile, " %6.1lf", Q[i][j]);}
      fprintf(outfile, "\n");
    }
    fprintf(outfile, "\n");
    fprintf(outfile, "vector c\n");
    for (i=0; i<2; i++){fprintf(outfile, " %6.1lf", c[i]);}
    fprintf(outfile, "\n");
    fprintf(outfile, "\n");

    fprintf(outfile, "three initial solutions\n");
    for (k=1; k<=3; k++){
      x[0] = (double)(rand()%31-15);
      x[1] = (double)(rand()%7-3)+x[1];
      for (i=0; i<2; i++){fprintf(outfile, " %6.1lf", x[i]);}
      fprintf(outfile, "\n");
    }
    fprintf(outfile, "\n");
    fprintf(outfile, "\n");
  } 
  fclose(outfile);
  return 0;
}

