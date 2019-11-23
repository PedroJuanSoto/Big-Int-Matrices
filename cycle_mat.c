#include <stdio.h>
#include <stdlib.h>
// #define ll long long int
#define ll __int128

void produce_cycle_mat(int n, int k, ll mat[n][n]){

  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      mat[i][j] = ((i+j+k)%n)+1;
}

void copy_mat(int n, ll mat[n][n], ll copy_cat[n][n]){
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      copy_cat[i][j] = mat[i][j];
}

void permute_mat(int i, int j, int k, int l, int n, ll mat[n][n]){
  ll c = mat[i][j];
  mat[i][j] = mat[k][l];
  mat[k][l] = c;
}

void prinmat(int n, ll mat[n][n]){
  printf("\n");
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++)
      printf("%lld, ", mat[i][j]);
    printf("\n");
  }
  printf("\n");
}
