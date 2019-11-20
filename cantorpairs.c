#include <stdio.h>
#include <stdlib.h>
// #define ll long long int
#define ll __int128

void produce_cantorpairs(int n, ll cantor[n][n]){

    int i,j;
    for (int k = 0; k< n; k++){
      i = k, j = 0;
      cantor[k][0] = ((i+j+1)*(i+j))/2;
      while (j<k){
        i--, j++;
        cantor[i][j] = cantor[i+1][j-1]+1;
      }
    }

    for (int k = n; k< 2*n-2; k++){
      i = n-1, j = k-i;
      cantor[i][j] = cantor[j-1][i]+1;
      while (j<n-1){
        i--, j++;
        cantor[i][j] = cantor[i+1][j-1]+1;
      }
    }

    cantor[n-1][n-1] = n*n-1;
}

void memoize_cantor_pairs(int n, ll cantor[n][n], ll memo[n*n][2]){
  int i,j;
  for (int k = 0; k< n; k++){
    i = k, j = 0;
    memo[((i+j+1)*(i+j))/2][0]=k;
    memo[((i+j+1)*(i+j))/2][1]=0;
    while (j<k){
      i--, j++;
      memo[cantor[i+1][j-1]+1][0]=i;
      memo[cantor[i+1][j-1]+1][1]=j;
    }
  }

  for (int k = n; k< 2*n-2; k++){
    i = n-1, j = k-i;
    memo[cantor[j-1][i]+1][0]=i;
    memo[cantor[j-1][i]+1][1]=j;
    while (j<n-1){
      i--, j++;
      memo[cantor[i+1][j-1]+1][0]=i;
      memo[cantor[i+1][j-1]+1][1]=j;
    }
  }

  memo[n*n-1][0]=n-1;
  memo[n*n-1][1]=n-1;

}

void produce_cycle_mat(int n, int k, ll mat[n][n]){

  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      mat[i][j] = ((i+j+k)%n)+1;
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

void prinmemo(int n, ll ray[n*n][2]){
  printf("\n");
  for (int i=0; i<n*n; i++){
    printf("(%lld, ", ray[i][0]);
    printf("%lld,), ", ray[i][1]);
  }
  printf("\n");
}
