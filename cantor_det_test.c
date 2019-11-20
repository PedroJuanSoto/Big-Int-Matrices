#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cantorpairs.c"
#include "big_int_determinant.c"
// #define ll long long int
#define ll __int128

int main(int argc, char *argv[]){
  int n = atoi(argv[1]);
  ll det(int n, ll mat[n][n]);
  void produce_cantorpairs(int n, ll cantor[n][n]);
  void produce_cycle_mat(int n, int k, ll mat[n][n]);
  void prinmat(int n, ll mat[n][n]);
  void memoize_cantor_pairs(int n, ll cantor[n][n], ll memo[n*n][2]);
  void prinmemo(int n, ll ray[n*n][2]);
  ll cantor[n][n];

  if (n>14)
    produce_cycle_mat(n, 2, cantor);
  else
    produce_cantorpairs(n, cantor);

  printf("\n\n\n");
  if (n<10){
    prinmat(n, cantor);
    printf("\n\n\n");
    ll memo[n*n][2];
    printf("\n\n\n");
    memoize_cantor_pairs(n, cantor, memo);
    prinmemo(n, memo);
    printf("\n\n\n");
  }
  clock_t t;
  t = clock();
  ll x = det(n, cantor);
  t = clock() - t;
  printf("determinant is %lld, ", x);
  double time_taken = ((double)t)/CLOCKS_PER_SEC;
  printf("det() took %f seconds to execute \n", time_taken);
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
