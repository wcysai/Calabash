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

int n, k, nn;
char str[32];

vector<int> ones[32];

LL src[1 << 20], dst[1 << 20], ans[1 << 20];

void yield(int ans) {
  for (int i = 0; i < k; i++) {
    str[k-i-1] = (ans & 1) + '0';
    ans >>= 1;
  }
// _debug("%d", ans);
  printf("%s", str);
  exit(0);
}

int toint() {
  int val = 0;
  for (int i = 0; i < k; i++) {
    val <<= 1;
    if (str[i] == '1') val++;
  }
  return val;
}

void fwt(LL *a, int n) {
  for (int d = 1; d < n; d <<= 1) {
    for (int i = 0; i < n; i += d << 1) {
      rep (j, d) {
        LL x = a[i+j], y = a[i+j+d];
        a[i+j] = x+y, a[i+j+d] = x-y;
      }
    }
  }
}

void ifwt(LL *a, int n) {
  for (int d = 1; d < n; d <<= 1) {
    for (int i = 0; i < n; i += d << 1) {
      rep (j, d) {
        LL x = a[i+j], y = a[i+j+d];
        a[i+j] = (x+y)/2, a[i+j+d] = (x-y)/2;
      } 
    }
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < (1 << k); i++) 
    ones[__builtin_popcount(i)].push_back(i);
  
  nn = 1 << k;

  rep (i, n) {
    scanf("%s", str);
    src[toint()]++;
//    _debug("%d", toint());
  }
  
//  rep (i, nn) cout << src[i] << ' '; cout << endl;

  fwt(src, 1 << k);
  for (int i = k; i; i--) {
    for (int mask : ones[i]) dst[mask] = 1;
    rep (i, nn) ans[i] = dst[i];
//  rep (i, nn) cout << dst[i] << ' '; cout << endl;
    fwt(ans, nn);
    rep (i, nn) ans[i] *= src[i];
    ifwt(ans, nn);
    for (int i = 0; i <= nn; i++) {
//  rep (i, nn) cout << ans[i] << ' '; cout << endl;
      if (ans[i] == n) yield(i);
    }
  }
  yield(0);
  return 0;
}
