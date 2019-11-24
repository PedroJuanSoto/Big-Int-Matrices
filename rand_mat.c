#include <stdio.h>
#include <stdlib.h>
// #define ll long long int
#define ll __int128


void produce_cantorpairs(int n, int cantor[n][n]){

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

void memoize_cantor_pairs(int n, int cantor[n][n], int memo[n*n][2]){
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

void produce_rand_mat(int n, ll mat[n][n], int memo_cantor_pairs[n*n][2]){
  int *forbidden = malloc(sizeof(int));
  srand(time(0));
  int legal = 0;
  int next_up = -1;
  forbidden[0] = -1;
  size_t size;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++){
      forbidden = realloc(forbidden, (n*i+j+1)*sizeof(int));
      size = sizeof(forbidden)/sizeof(forbidden[0]);
      while (legal == 0){
        next_up = (rand() % 25)+1;
        int found_one = 0;
        for (int i = 0; i < size; i++)
          if (forbidden[i] == next_up)
            found_one = 1;
        if (found_one == 0)
          legal = 1;
      }
      forbidden[i*n+j] = next_up;
      mat[memo_cantor_pairs[next_up][0]][memo_cantor_pairs[next_up][1]] = (ll) i+1;
      legal = 0;
    }
}

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
