import numpy as np
from scipy import linalg
import time
import sys

def permute_mat(i, j, k, l, mat):
  c = mat[i][j]
  mat[i][j] = mat[k][l]
  mat[k][l] = c
  return mat


def sim_anneal(boltz_cons, n, curr_time, total_time, curr_ener, mat, matty, box):
  perm_ind = np.random.randint(0, n, (4))
  matty = np.copy(mat)
  permute_mat(perm_ind[0], perm_ind[1], perm_ind[2], perm_ind[3], matty);
  box = np.copy(matty)
  new = linalg.det(matty)
  if (new*new>curr_ener*curr_ener):
    mat = np.copy(box)
    return new
  coin_flip = np.random.uniform()
  temp = boltz_cons*((total_time/ curr_time) - 0.99)
  prob_of_state_change = np.exp((np.absolute(new) - np.absolute(curr_ener))/temp)
  if (prob_of_state_change>coin_flip):
    mat = np.copy(box)
    return new
  else:
    return new

def produce_cantorpairs(n, cantor):

    for k in range(n):
      i = k
      j = 0
      cantor[k][0] = ((i+j+1)*(i+j))//2
      while (j<k):
        i = i-1
        j = j+1
        cantor[i][j] = cantor[i+1][j-1]+1

    for k in range(n, 2*n-2):
      i = n-1
      j = k-i
      cantor[i][j] = cantor[j-1][i]+1
      while (j<n-1):
        i = i-1
        j = j+1
        cantor[i][j] = cantor[i+1][j-1]+1

    cantor[n-1][n-1] = n*n-1;

def memoize_cantor_pairs(n, cantor, memo):

  for k in range(n):
    i = k
    j = 0
    memo[((i+j+1)*(i+j))//2][0]=k
    memo[((i+j+1)*(i+j))//2][1]=0
    while (j<k):
      i = i-1
      j = j+1
      memo[cantor[i+1][j-1]+1][0]=i
      memo[cantor[i+1][j-1]+1][1]=j


  for k in range(n, 2*n-2):
    i = n-1
    j = k-i
    memo[cantor[j-1][i]+1][0]=i
    memo[cantor[j-1][i]+1][1]=j
    while (j<n-1):
      i = i-1
      j = j+1
      memo[cantor[i+1][j-1]+1][0]=i
      memo[cantor[i+1][j-1]+1][1]=j


  memo[n*n-1][0]=n-1
  memo[n*n-1][1]=n-1

def produce_rand_mat(n, mat, memo_cantor_pairs):
  forbidden = np.arange(n*n+1)
  for i in range(n*n):
    next_up = np.random.randint(0,n*n-i)
    mat[memo_cantor_pairs[forbidden[next_up]][0]][memo_cantor_pairs[forbidden[next_up]][1]] =  (i//n)+1
    for j in range(next_up, n*n):
      forbidden[j] = forbidden[j+1]


s = time.time()

if len(sys.argv) > 1:
  n= int(sys.argv[1])
  if len(sys.argv) > 2:
    iterations = int(sys.argv[2])
  else:
    iterations = 100000
else:
  n=9
  iterations = 100000

mat = np.random.randint(1,n,(n,n))
cantor = np.random.randint(1,n,(n,n))
memo = np.random.randint(1,n,(n*n,2))

produce_cantorpairs(n, cantor)
memoize_cantor_pairs(n, cantor, memo)
produce_rand_mat(n, mat, memo)

new = np.linalg.det(mat)
max = np.linalg.det(mat)

super_max = 0x3704d007
new_mat = np.copy(mat)
matty = np.copy(mat)
for i in range(iterations):
    new = sim_anneal(1000000, n, i+1, iterations+1, new, new_mat, mat, matty)
    if (new*new>max*max):
      max = new;
      max_mat = np.copy(new_mat)
      print("current max is ", max)
      print(max_mat)

print("max det is ", max)
print(max_mat)


if (max*max>super_max*super_max):
  printf("\n\n\n\nEUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
  printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
  printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
  printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
  printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
  printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
  printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!");
  printf("EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!EUREKA!!!\n\n\n\n");


t = time.time()
print("search time = ", t-s)
