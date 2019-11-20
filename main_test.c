#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cantorpairs.c"
#include "big_int_determinant.c"
// #define ll long long int
#define ll __int128

int main(int argc, char *argv[]){
  int n = atoi(argv[1]);
  int iterations = atoi(argv[2]);
  ll det(int n, ll mat[n][n]);
  void produce_cycle_mat(int n, int k, ll mat[n][n]);
  void prinmat(int n, ll mat[n][n]);
  void permute_mat(int i, int j, int k, int l, int n, ll mat[n][n]);
  void copy_mat(int n, ll mat[n][n], ll copy_cat[n][n]);
  ll cantor[n][n];
  ll super_max = 923062279;
  ll super_maxy = 0x3704d007;

  if (super_max == super_maxy)
      printf("\nohYYYEAAAA\n");

  srand(time(0));
  int positions[] = {-1,-1,-1,-1};
  for (int k=0; k<4; k++)
    positions[k] = rand()%n;
  produce_cycle_mat(n, rand()%n, cantor);
  permute_mat(positions[0], positions[1], positions[2], positions[3], n, cantor);
  ll max_mat[n][n];
  copy_mat(n, cantor, max_mat);
  ll max = det(n, cantor);
  printf("\ndeterminant is %lld\n", max);
  ll new;
  ll new_mat[n][n];
  produce_cycle_mat(n, rand()%n, cantor);
  copy_mat(n, cantor, new_mat);
  for (int i=0; i<iterations; i++){
    for (int k=0; k<4; k++)
      positions[k] = rand()%n;
    copy_mat(n, new_mat, cantor);
    permute_mat(positions[0], positions[1], positions[2], positions[3], n, cantor);
    copy_mat(n, cantor, new_mat);
    new = det(n, cantor);
    if (new*new>max*max){
      max = new;
      copy_mat(n, new_mat, max_mat);
    }
  }

  printf("\nmax determinant is %lld\n", max);
  prinmat(n, max_mat);
  if (max*max>super_max*super_max){
      printf("\n\n\n\nEUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
      printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
      printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
      printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
      printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
      printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
      printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
      printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!\n\n\n\n");
  }

  return 0;
}
