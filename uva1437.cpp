#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory.h>
using namespace std;
char A[200], B[200];
int N, mc[200][200], mopt[200], vc[200][200], vopt[200];

// Compute the cost of painting a completely mismatched 
// string to the target string B
int cost(int i, int j);
int _cost(int i, int j)
{
  int ans = 0xfffff;
  if (i == j) return 1; // Basecase: Charge for a single painting operation
  else if (B[i] != B[j]) // Divide into two sub-intervals
    for(int k = i; k < j; ++k) {
      ans = min(ans, cost(i, k) + cost(k+1, j));
    } 
  else // If two ends are the same, only charge a single end
    ans = cost(i, j-1); // charging the rightmost piece = charging the leftmost piece
//    ans = max(cost(i+1, j), cost(i, j-1));
//    ans = cost(i+1, j);
//    ans = min(cost(i+1, j), cost(i, j-1));
  return ans;
}
int cost(int i, int j)
{
  if (vc[i][j]) return mc[i][j];
  else {
    vc[i][j] = 1;
    return mc[i][j] = _cost(i, j);
  }
}

// Compute the optimal cost of painting string A to target string B
int opt(int n);
int _opt(int n)
{
  if (n == 0) // basecase: cost=1 if A[0]!=B[0]
    return A[0] != B[0];
  else { // Find an optimal index towards the left of the string
    int ans = cost(0, n);
    for(int k = 0; k < n; ++k)
      ans = min(ans, opt(k) + cost(k+1, n));
    if (A[n] == B[n])
      ans = min(ans, opt(n-1));
    return ans;
  }
}
int opt(int n)
{
  if (vopt[n]) return mopt[n];
  else {
    vopt[n] = 1;
    return mopt[n] = _opt(n);
  }
}

int main()
{
  while (scanf("%s%s", A, B) == 2) {
    memset(mc, 0, sizeof(mc));
    memset(mopt, 0, sizeof(mopt));
    memset(vc, 0, sizeof(vc));
    memset(vopt, 0, sizeof(vopt));
    N = strlen(A); 
    if (N != strlen(B)) return 1;
    printf("%d\n", opt(N - 1)); 
  }
  return 0;
}

