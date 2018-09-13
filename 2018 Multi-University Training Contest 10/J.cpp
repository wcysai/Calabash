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

int n, m, k;
int sm[100005], ss[100005], xm[100005][8], xs[100005][8];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    rep (i, n) {
      scanf("%d", sm+i);
      rep (j, k) scanf("%d", xm[i]+j);
    }
    rep (i, m) {
      scanf("%d", ss+i);
      rep (j, k) scanf("%d", xs[i]+j);
    }
    LL ans = 0;
    for (unsigned mask = 0; mask < (1u << k); mask++) {
      LL max1 = LLONG_MIN / 3, max2 = LLONG_MIN / 3;
      rep (i, n) {
        LL cur = sm[i];
        rep (j, k) 
          if (mask & (1u << j)) cur += xm[i][j]; else cur -= xm[i][j];
        max1 = max(max1, cur);
      }
      rep (i, m) {
        LL cur = ss[i];
        rep (j, k)
          if (mask & (1u << j)) cur -= xs[i][j]; else cur += xs[i][j];
        max2 = max(max2, cur);
      }
      ans = max(ans, max1 + max2);
    }
    cout << ans << endl;
  }
  return 0;
}
