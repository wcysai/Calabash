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
 
LL p = 998244353;
int n;
LL id[512][512];
LL d[512][512];
 
void floyd() {
  rep (k, n)
    rep (i, n)
      rep (j, n)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
 
int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    rep (i, n) rep (j, n) {
      scanf("%lld", &d[i][j]);
      id[i][j] = d[i][j];
    }
    floyd();
    /*
    rep (i, n) {
      rep (j, n) {
        printf("%lld\t", d[i][j]);
      }
      puts("");
    }
    */
    LL tot = 0;
    rep (i, n) {
      rep (j, i) {
        vector<int> dist(n);
        rep (k, n) {
          dist[k] = min(d[i][k], d[j][k]);
        }
        sort(range(dist));
        rep (k, n)
          tot += (n - k - 1) * dist[k];
        tot %= p;
      }
    }
    LL factor = n * (n-1) / 2 - 1;
    rep (i, n) {
      rep (j, i) {
        tot += id[i][j] * factor;
      }
      tot %= p;
    }
    cout << tot << endl;
  }
  return 0;
}
