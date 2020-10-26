
/* program for generating random coefficients of f(x) = x^4 + ax^3 + bx^2 + cx + y^2 + dy + exy */
/* three instances of a, b, c, d, e are generated along with three initial solutions for each */ 
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
  double A[5][3];
  double a, b, c, d, e;
  double x[2];
  char fname[128], idnum[128];
  FILE *outfile;

  printf("Input your ID number:");
  fgets(idnum, sizeof(idnum), stdin);
  idnum[strlen(idnum)-1] = '\0';
  fflush(stdin);
  bangou = atoi(idnum);
  printf("seed = %d\n", bangou);

  srand(bangou);

  printf("Specify file name:");
  fgets(fname, sizeof(fname), stdin);
  fname[strlen(fname)-1] = '\0';
  fflush(stdin);

  outfile = fopen(fname,"w");  

  for (numb=1; numb<=2; numb++){
    for (i=0; i<5; i++){
      for (j=0; j<3; j++){
        A[i][j] = 0.0;
      }
    }
    a = (double)(rand()%21-10);
    b = (double)(rand()%41-20);
    c = (double)(rand()%81-40);
    d = (double)(rand()%161-80);
    e = (double)(rand()%81-40);

    A[4][0] = 1.0;
    A[3][0] = a;
    A[2][0] = b;
    A[1][0] = c;
    A[0][1] = d;
    A[1][1] = e;
    A[0][2] = 1.0;
    fprintf(outfile, "data set %d\n", numb);
    fprintf(outfile, "coefficient matrix A\n");
    for (i=0; i<5; i++){
      for (j=0; j<3; j++){ fprintf(outfile, " %6.1lf", A[i][j]);}
      fprintf(outfile, "\n");
    }
    fprintf(outfile, "\n");
    fprintf(outfile, "three initial solutions\n");
    for (k=1; k<=3; k++){
      x[0] = (double)(rand()%81-40);
      x[1] = (double)(rand()%81-40);
      for (i=0; i<2; i++){fprintf(outfile, " %6.1lf", x[i]);}
      fprintf(outfile, "\n");
    }
    fprintf(outfile, "\n");
    fprintf(outfile, "\n");
  } 
  fclose(outfile);

  return 0;
}


