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

int n, m, p;
int dp[96][96][8192];

void clear() {
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k <= n * m; k++) {
        dp[i][j][k] = 0;
      }
    }
  }
}

void inc(int& x, int y) {
  x += y;
  if (x >= p) x -= p;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &p);
    clear();
    dp[1][1][1] = m * n % p;
    Rep (k, n * m) {
      Rep (i, n) {
        Rep (j, m) {
          if (i * j < k) continue;
          inc(dp[i+1][j][k+1], 1ll * dp[i][j][k] * (n - i) * j % p);
          inc(dp[i][j+1][k+1], 1ll * dp[i][j][k] * (m - j) * i % p);
//          inc(dp[i+1][j+1][k+1],  dp[i][j][k] * (n - i) * (m - j) % p);
          inc(dp[i][j][k+1], 1ll * dp[i][j][k] * (i * j - k) % p);
        }
      }
    }
    cout << dp[n][m][n*m] << endl;
  }
  return 0;
}
