#include <stdio.h>
#include <stdlib.h>
#define ll long long int

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

void produce_simple_cycle_mat(int n, ll mat[n][n]){

  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      mat[i][j] = (i+j)%n;
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
