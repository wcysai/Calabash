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
 
int n, k;
LL s[1000005], c[1000005];
LL val[1000005];
 
bool check(LL kk) {
  rep (i, n) val[i] = -s[i] * (c[i] - kk);
  sort(val, val+n);
  LL tot = 0;
  rep (i, n-k) {
    tot -= val[i];
    if (tot < 0) return false;
  }
  return true;
}
 
int main() {
  scanf("%d%d", &n, &k);
  rep (i, n) scanf("%lld", s+i);
  rep (i, n) scanf("%lld", c+i), c[i] *= 1000000;
  LL l = 0, r = 1000000000, mid;
  do {
    mid = (l+r+1)/2;
    if (check(mid)) l = mid; else r = mid-1;
  } while (r - l > 1);
  printf("%.8f\n", mid / 1000000.0);
  return 0;
}
