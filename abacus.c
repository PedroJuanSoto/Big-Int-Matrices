#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "rand_mat.c"
#include "big_int_determinant.c"
#define ll __int128
#define wha 100
#define num_thds 9

struct arg_struct {
  int arg1;
  ll** arg2;
  int arg3;
};

ll dets[num_thds];

void *get_result(void *param){
  struct arg_struct *args = param;
  dets[(*args).arg3] = det((*args).arg1, (*args).arg2);
}

int main(int argc, char const *argv[]) {
  srand((int) time(NULL));
  clock_t t;
  t = clock();
  void abacus_to_mat(int l, int num_1s[l], int num_0s[l], int* abacus[l], ll mat[l][l]);
  int n,threads_or_not;
  if (argc>1){
    n = atoi(argv[1]);
    if (argc>2)
      threads_or_not = atoi(argv[2]);
    else
      threads_or_not = 0;
  }
  else{
    n=3;
    threads_or_not = 0;
  }
  if (threads_or_not == 0){
    ll mat[n][n];
    ll new_mat[n][n];
    int* abby[n];
    int num_1s[n], num_0s[n];

    for (int i = n-1; i >= 0; i--) {
      abby[n-i-1] = (int*) malloc((i+1)*n*sizeof(int));
      num_1s[n-i-1] = n;
      num_0s[n-i-1] = n*i;
      for (int j = 0; j < n; j++)
        abby[n-i-1][j] = 1;
      for (int j = n; j < n*(i+1); j++)
        abby[n-i-1][j] = 0;
    }

    int done;
    ll max = 0;
    ll new_det;
    for (int v = 0; v<wha; v++) {
      done=gen_next_abacus(n, 0, num_1s, num_0s, abby);
      abacus_to_mat(n, num_1s, num_0s, abby, mat);
      copy_mat(n, mat, new_mat);
      new_det = det(n, new_mat);
      if (new_det*new_det > max*max){
        prinmat(n, mat);
        printf("\ndetterminant = %lld\n", det(n, mat));
        max =new_det;
      }
    }
  }
  else if (threads_or_not ==1){
    int* abby[n];
    int num_1s[n], num_0s[n];
    ll mat[num_thds][n][n];
    ll new_mat[num_thds][n][n];

    for (int i = n-1; i >= 0; i--) {
      abby[n-i-1] = (int*) malloc((i+1)*n*sizeof(int));
      num_1s[n-i-1] = n;
      num_0s[n-i-1] = n*i;
      for (int j = 0; j < n; j++)
        abby[n-i-1][j] = 1;
      for (int j = n; j < n*(i+1); j++)
        abby[n-i-1][j] = 0;
    }

    int done=1;
    ll max = 0;
    ll max_mat[n][n];
    ll new_det[num_thds];
    for(int i=0; i<num_thds; i++ )
      new_det[i] = 0;
    pthread_t *tid = malloc( num_thds* sizeof(pthread_t) );
    struct arg_struct {
      int arg1;
      ll** arg2;
      int arg3;
    };
    struct arg_struct args[n];
    for (int i = 0; i < num_thds; i++) {
      args[i].arg1 = n;
      args[i].arg2 = new_mat[i];
      args[i].arg3 = i;
    }

    for (int v = 0; v<wha; v++) {
      for (int i = 0; i < num_thds; i++) {
        abacus_to_mat(n, num_1s, num_0s, abby, mat[i]);
        done=gen_next_abacus(n, 0, num_1s, num_0s, abby);
        if (done!=0)
          copy_mat(n, mat[i], new_mat[i]);
      }
      for(int i=0; i<num_thds; i++ )
        pthread_create( &tid[i], NULL, get_result, &args[i] );
      for(int j=0; j<num_thds; j++ )
        pthread_join( tid[j], NULL );
      for(int k=0; k<num_thds; k++ ){
        if (dets[k]*dets[k] > max*max){
          copy_mat(n, mat[k], max_mat);
          prinmat(n, max_mat);
          printf("\ndeterminant = %lld\n", dets[k]);
          max =dets[k];
        }
      }
    }
  }
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC;
  printf("main() took %f seconds to execute \n", time_taken);
  return 0;
}

void abacus_to_mat(int l, int num_1s[l], int num_0s[l], int* abacus[l], ll mat[l][l]){
  for(int i=0; i<l; i++)
    for(int j=0; j<l; j++)
      mat[i][j] = -1;
  for (int k = 0; k < l; k++) {
    int count = num_1s[k];
    int place = 0;
    for (int i = 0; count > 0; i++)
      for (int j = 0; j < l; j++)
        if (mat[i][j]== -1)
          if (abacus[k][place] == 1) {
            count = count -1;
            mat[i][j] = k+1;
            place++;
          }
          else
            place++;
  }
}

int gen_next_abacus(int l, int stack_f, int num_1s[l], int num_0s[l], int* abacus[l]){
  if (l-stack_f==2)
    return gen_next_bin_str(num_1s[stack_f], num_0s[stack_f], abacus[stack_f]);
  if (gen_next_abacus(l, stack_f+1, num_1s, num_0s, abacus)==0){
    int i,j;
    for (i = 0; i < num_1s[stack_f+1]; i++)
      abacus[stack_f+1][i]=1;
    for (j = num_1s[stack_f+1]; j < num_1s[stack_f+1]+num_0s[stack_f+1]; j++)
      abacus[stack_f+1][j]=0;
    return gen_next_bin_str(num_1s[stack_f], num_0s[stack_f], abacus[stack_f]);
  }
  return 1;
}

int gen_next_bin_str(int n, int k, int bin[n+k]){
  int num_ones = 0;
  int i,j;
  for (i = n+k-1; num_ones < n; i--)
    if (bin[i] == 1)
      num_ones = num_ones + 1;
  if (i == k-1)
    return 0;
  else if (bin[n+k-1] == 1){
    int count = 1;
    for (i = n+k-1; bin[i] == 1; i--)
      count++;
    for (j = i; bin[j] == 0; j--)
      ;
    bin[j] = 0;
    for (i = j+1; count>0; i++)
      bin[i]=1, count--;
    for (j = i; j<n+k; j++)
      bin[j]=0;
    return 1;
  }
  for (i = n+k-1; bin[i] == 0; i--);
  bin[i+1] = 1;
  bin[i] = 0;
  return 1;
}

int mult_fact(int n, int l, int k[l]){
  int x = 1;
  for (int i = n; i>k[0]; i--)
    x = x*i;
  for (int i = 1; i<l; i++)
    for (int j = 1; j<=k[i]; j++)
      x = x/j;
  return x;
}
