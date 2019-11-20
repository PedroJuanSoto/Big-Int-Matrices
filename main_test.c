#include <stdio.h>
#include <stdlib.h>
#include "cantorpairs.c"
#include "big_int_determinant.c"
#define ll __int128

int main(int argc, char *argv[]){
  int n = atoi(argv[1]);
  ll det(int n, ll mat[n][n]);
  void produce_cantorpairs(int n, ll cantor[n][n]);
  void produce_cycle_mat(int n, int k, ll mat[n][n]);
  void prinmat(int n, ll mat[n][n]);
  ll cantor[n][n];

  if (n>14)
    produce_cycle_mat(n, 2, cantor);
  else
    produce_cantorpairs(n, cantor);

  printf("\n\n\n");
  if (n<10){
    prinmat(n, cantor);
    printf("\n\n\n");
  }
  ll x = det(n, cantor);
  printf("%lld, ", x);
  if (n<10){
    printf("\n\n\n");
    prinmat(n, cantor);
  }
  printf("\n\n\n");

  produce_cycle_mat(n, 2, cantor);
  if (n<14)
    prinmat(n, cantor);

  return 0;
}
