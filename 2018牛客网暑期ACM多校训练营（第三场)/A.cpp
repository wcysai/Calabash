#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
 
#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;
 
int n;
int p[40], a[40], c[40], m[40], g[40];
int P, A, C, M;
int8_t dp[40][40][40][40][40], sel[40][40][40][40][40];
 
int main() {
  scanf("%d", &n);
  Rep (i, n) scanf("%d%d%d%d%d", p+i, a+i, c+i, m+i, g+i);
  scanf("%d%d%d%d", &P, &A, &C, &M);
  Rep (i, n) {
    for (int pp = p[i]; pp <= P; pp++) {
      for (int aa = a[i]; aa <= A; aa++) {
        for (int cc = c[i]; cc <= C; cc++) {
          for (int mm = m[i]; mm <= M; mm++) {
            dp[i][pp][aa][cc][mm] = dp[i-1][pp][aa][cc][mm];
            if (dp[i-1][pp-p[i]][aa-a[i]][cc-c[i]][mm-m[i]] + g[i]
                > dp[i][pp][aa][cc][mm]) {
              dp[i][pp][aa][cc][mm] =
                dp[i-1][pp-p[i]][aa-a[i]][cc-c[i]][mm-m[i]] + g[i];
              sel[i][pp][aa][cc][mm] = 1;
            }
          }
        }
      }
    }
  }
  int maxv = -1;
  int _p = 0, _a = 0, _c = 0, _m = 0;
  for (int pp = 0; pp <= P; pp++) {
    for (int aa = 0; aa <= A; aa++) {
      for (int cc = 0; cc <= C; cc++) {
        for (int mm = 0; mm <= M; mm++) {
          if (dp[n][pp][aa][cc][mm] > maxv) {
            maxv = dp[n][pp][aa][cc][mm];
            _p = pp; _a = aa; _c = cc; _m = mm;
          }
        }
      }
    }
  }
  vector<int> ans;
  for (int i = n; i; i--) {
    if (sel[i][_p][_a][_c][_m]) {
      ans.push_back(i);
      _p -= p[i]; _a -= a[i]; _c -= c[i]; _m -= m[i];
    }
  }
  printf("%d\n", int(ans.size()));
  for (int v : ans) {
    printf("%d ", v-1);
  }
  puts("");
  return 0;
}
