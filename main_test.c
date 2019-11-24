#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cycle_mat.c"
#include "big_int_determinant.c"
// #define ll long long int
#define ll __int128
#define ld long double

int main(int argc, char *argv[]){
  int n, iterations;
  if (argc>1){
    n = atoi(argv[1]);
    if (argc>2)
      iterations = atoi(argv[2]);
    else
      iterations = 100000;
  }
  else{
    n=9;
    iterations = 100000;
  }

  ll det(int n, ll mat[n][n]);
  void produce_cycle_mat(int n, int k, ll mat[n][n]);
  void prinmat(int n, ll mat[n][n]);
  void permute_mat(int i, int j, int k, int l, int n, ll mat[n][n]);
  void copy_mat(int n, ll mat[n][n], ll copy_cat[n][n]);
  ll sim_anneal(ld boltz_cons, int n, int curr_time, int total_time, ll curr_ener, ll mat[n][n], ll cantor[n][n], ll box[n][n], int perm_ind[]);
  ll cantor[n][n];
  ll super_max = 0x3704d007;

  srand((int) time(NULL));
  int perm_ind[] = {-1,-1,-1,-1};
  for (int k=0; k<4; k++)
    perm_ind[k] = rand()%n;
  produce_cycle_mat(n, rand()%n, cantor);
  permute_mat(perm_ind[0], perm_ind[1], perm_ind[2], perm_ind[3], n, cantor);
  ll max_mat[n][n];
  copy_mat(n, cantor, max_mat);
  ll max = det(n, cantor);
  printf("\ndeterminant is %lld\n", max);
  ll new = max;
  ll new_mat[n][n];
  ll matty[n][n];
  produce_cycle_mat(n, rand()%n, cantor);
  copy_mat(n, cantor, new_mat);
  for (int i=0; i<iterations; i++){
    new = sim_anneal(100, n, i, iterations, new, new_mat, cantor, matty, perm_ind);
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
}


ll sim_anneal(ld boltz_cons, int n, int curr_time, int total_time, ll curr_ener, ll mat[n][n], ll cantor[n][n], ll box[n][n], int perm_ind[]){
  for (int k=0; k<4; k++)
    perm_ind[k] = rand()%n;
  copy_mat(n, mat, cantor);
  permute_mat(perm_ind[0], perm_ind[1], perm_ind[2], perm_ind[3], n, cantor);
  copy_mat(n, cantor, box);
  ll new = det(n, cantor);
  if (new*new>curr_ener*curr_ener){
    copy_mat(n, box, mat);
    return new;
  }
  ld coin_flip = ((ld)rand())/RAND_MAX;
  ld temp = boltz_cons*(1 - (((ld) total_time)/(((ld) curr_time))));
  ld prob_of_state_change = exp2(-(((ld) new)-((ld) curr_ener))/temp);
  if (prob_of_state_change>coin_flip){
    copy_mat(n, box, mat);
    return new;
  }
  else
    return new;
}
