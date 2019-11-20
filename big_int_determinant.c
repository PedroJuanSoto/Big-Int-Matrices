#include <stdio.h>
#include <stdlib.h>
#define ll __int128

ll gcd(ll n, ll k){
  if(n<0 || k<0)
    if(n<0 && k<0)
      return gcd(-n, -k);
    else if (k<0)
      return gcd(n, -k);
    else if (n<0)
      return gcd(-n, k);

  if (n<k){
    ll z = n;
    n = k;
    k = z;
  }

  if (n == k)
    return k;
  else if (k == 0)
    return n;
  else if (k == 1)
    return 1;

  n = n%k;

  return gcd(n, k);
}

void row_i_to_j_reduced(int i, int j, int n, ll mat[n][n], ll reduced[n], ll r[(n*(n-1))/2], int* u){
  ll d = gcd(mat[i][i], mat[j][i]);
  ll fst = mat[i][i]/d;
  ll snd = mat[j][i]/d;
  r[(*u)] = mat[i][i]/d;
  (*u)++;

  for (int k=0; k<n; k++)
    reduced[k] = fst*mat[j][k] - snd*mat[i][k];
}


ll det(int n, ll mat[n][n]){
  void row_i_to_j_reduced(int i, int j, int n, ll mat[n][n], ll reduced[n], ll r[(n*(n-1))/2], int* u);
  int is_rank_zero(int i, int n, ll mat[n][n]);
  void switch_i_with_j(int i, int j, int n, ll mat[n][n]);
  void simplfy_fraction(int n, ll r[(n*(n-1))/2], ll acc[n]);
  ll d;
  ll r[(n*(n-1))/2];
  ll sig = 1;
  int t;
  int u=0;

  for (int i=0; i<n; i++){
    t = is_rank_zero(i, n, mat);
    if (t == 0)
      return 0;
    else if (t>0)
      sig = sig*(-1), switch_i_with_j(i, t, n, mat);
    for (int j=i+1; j<n; j++)
      row_i_to_j_reduced(i, j, n, mat, mat[j], r, &u);
  }

  ll acc[n];
  for (int k=0; k<n; k++)
    acc[k] = mat[k][k];

  simplfy_fraction(n, r, acc);

  ll bot=1;
  for (int k=0; k<(n*(n-1))/2; k++){
    bot = bot*r[k];
  }

  ll top=1;
  for (int k=0; k<n; k++){
    top = top*acc[k];
  }

  return sig*top/bot;
}

void switch_i_with_j(int i, int j, int n, ll mat[n][n]){
  ll switchy[n];
  for (int k=0; k<n; k++)
    switchy[k] = mat[i][k];
  for (int k=0; k<n; k++)
    mat[i][k] = mat[j][k];
  for (int k=0; k<n; k++)
    mat[j][k] = switchy[k];
}

int is_rank_zero(int i, int n, ll mat[n][n]){
  if (mat[i][i] !=0)
    return -1;
  else
    for (int j=i; j<n; j++)
      if (mat[j][i] !=0)
        return j;
    return 0;
}

void simplfy_fraction(int n, ll big[(n*(n-1))/2], ll small[n]){
  ll d;
  for (int i=0; i<(n*(n-1))/2; i++)
    for (int j=0; j<n; j++)
      if ((d=gcd(big[i], small[j]))>1)
        big[i] = big[i] / d, small[j] = small[j] / d;
}
