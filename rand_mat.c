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
  int forbidden[n*n];
  srand(time(0));
  int next_up;
  for (int l = 0; l < n*n; l++)
    forbidden[l]=l;
  for (int i=0; i < n*n; i++){
    next_up = rand() % (n*n-i);
    mat[memo_cantor_pairs[forbidden[next_up]][0]][memo_cantor_pairs[forbidden[next_up]][1]] = (ll) (i/n)+1;
    for(int j=next_up; j<n*n; j++)
      forbidden[j] = forbidden[j+1];
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
  printf("\n-Matrix is-----------------------------------------------------------\n");
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++)
      printf("%lld, ", mat[i][j]);
    printf("\n");
  }
  printf("\n---------------------------------------------------------------------\n");
}

void prin_int_mat(int n, int mat[n][n]){
  printf("\n-Matrix is-----------------------------------------------------------\n");
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++)
      printf("%d, ", mat[i][j]);
    printf("\n");
  }
  printf("\n---------------------------------------------------------------------\n");
}

void prin_int_memo(int n, int ray[n*n][2]){
  printf("\n-Memo is-------------------------------------------------------------\n");
  for (int i=0; i<n*n; i++){
    printf("(%d, ", ray[i][0]);
    printf("%d,), ", ray[i][1]);
  }
  printf("\n---------------------------------------------------------------------\n");
}


void prin_int_ray(int n, int ray[n]){
  printf("\n-Array is------------------------------------------------------------\n");
  for (int i=0; i<n; i++)
    printf("%d, ", ray[i]);
  printf("\n---------------------------------------------------------------------\n");
}
