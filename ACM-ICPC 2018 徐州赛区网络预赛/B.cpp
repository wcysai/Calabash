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

int n, m, l, k;
int a[1024], b[1024], c[1024];

int clamp(int x) {
  if (x > 200) return 200;
  if (x < 0) return 0;
  return x;
}

int neg(int x) {
  return clamp(-(x - 100) + 100);
}

#define GOOD    3
#define NORMAL  2
#define BAD     1

int dp[1024][256];

int main() {
  scanf("%d%d%d%d", &n, &m, &k, &l);
  m += 100; l += 100; k += 100;
  rep (i, n) scanf("%d%d%d", a+i, b+i, c+i);
  rep (i, 201) {
    if (i <= l) dp[n][i] = BAD;
    else if (i >= k) dp[n][i] = GOOD;
    else dp[n][i] = NORMAL;
  }
  for (int i = n - 1; i >= 0; i--) {
    rep (j, 201) {
      if (i & 1) {  // to bad
        int worst = 3;
        if (a[i]) worst = min(worst, dp[i+1][clamp(j+a[i])]);
        if (b[i]) worst = min(worst, dp[i+1][clamp(j-b[i])]);
        if (c[i]) worst = min(worst, dp[i+1][neg(j)]);
        dp[i][j] = worst;
      } else {      // to good
        int best = 1;
        if (a[i]) best = max(best, dp[i+1][clamp(j+a[i])]);
        if (b[i]) best = max(best, dp[i+1][clamp(j-b[i])]);
        if (c[i]) best = max(best, dp[i+1][neg(j)]);
        dp[i][j] = best; 
      }
    }
  }
  const char result[4][64] = { "", "Bad Ending", "Normal Ending", "Good Ending" };
  printf("%s\n", result[dp[0][m]]);
  return 0;
}
