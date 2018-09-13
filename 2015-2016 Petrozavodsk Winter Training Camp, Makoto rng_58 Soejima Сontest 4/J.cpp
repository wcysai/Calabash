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

const LL mod = 1000000007, inv2 = (mod + 1) / 2;

int n;
LL a[4];


int main() {
  scanf("%d", &n);
  rep (i, n) {
    int d; scanf("%d", &d);
    a[d]++; 
  }
  if (a[1] + 2 * a[2] + 3 * a[3] != 2 * n - 2 || a[1] != a[3] + 2) {
    cout << 0 << endl;
  } else {
    LL ans = 1;
    Rep (i, n - 2) ans = ans * i % mod;
    rep (i, a[3]) ans = ans * inv2 % mod;
    cout << ans << endl;
  }
  return 0;
}
