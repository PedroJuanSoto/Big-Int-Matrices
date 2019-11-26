#include <stdio.h>
#include <stdlib.h>
#include "rand_mat.c"
#include "big_int_determinant.c"
#define ll __int128

int main(int argc, char const *argv[]) {
  int n,k;
  if (argc>2){
    n = atoi(argv[1]);
    k = atoi(argv[2]);
  }
  else{
    n=2;
    k = 3;
  }
  int params[] = {n,k};
  int num_of_strings = mult_fact(n+k,2,params);
  int strang[n+k];
  for (int j = 0; j < n; j++)
    strang[j] = 1;
  for (int j = n; j < n+k; j++)
    strang[j] = 0;
  printf("-----------------------------\n\n");
  for (int i = 0; i < n+k; i++)
    printf("%d", strang[i]);
  printf("\n\n------------------------------");
  for (int t = 0; t < num_of_strings; t++) {
    printf("-----------------------------\n\n");
    printf("%d\n", gen_next_bin_str(n, k, strang));
    for (int i = 0; i < n+k; i++)
      printf("%d", strang[i]);
    printf("\n\n------------------------------");
  }
  int bin1[]= {1,1,1,1,0,0,0,0,0};
  int bin2[]= {1,1,0,0,0,0};
  int bin3[]= {1,1,1};
  int* abby[] = {bin1, bin2, bin3};
  int num_1s[] = {4,2,3};
  int num_0s[] = {5,4,0};
  int paramaaas[] = {3,3};
  for (int v = 0; v < mult_fact(6,2,paramaaas)+4; v++) {
    printf("%d\n", gen_next_abacus(3, 0, num_1s, num_0s, abby));
    for (int t = 0; t < 3; t++) {
      printf("-----------------------------\n\n");
      for (int i = 0; i < num_1s[t]+num_0s[t]; i++)
        printf("%d", abby[t][i]);
      printf("\n\n------------------------------");
    }
  }
  return 0;
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
