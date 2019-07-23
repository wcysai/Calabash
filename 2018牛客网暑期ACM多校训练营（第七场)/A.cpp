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
 
int a[500005];
 
inline void arrange(int l, int r) {
  for (int i = l, j = r; i <= r; i++, j--) {
    a[i] = j;
  }
}
 
int clz(int x) {
  int n = 0;
  while (x > 0) {
    x <<= 1;
    n++;
  }
  return n;
}
 
int main() {
  int n, nn; cin >> n; nn = n;
  while (n > 1) {
    int right = n - 1;
    int left = ~right & ((1ll << (31 - __builtin_clz(right))) - 1);
//   cout << n << ' ' << left <<  ' ' << right << endl;
//    _debug("n=%d, left=%d, right=%d", n, left, right);
    arrange(left, right);
    n = left;
  }
  if (n > 1) a[0] = 1;
  rep (i, nn) printf("%d%c", a[i], i == nn-1 ? '\n' : ' ' );
  rep (i, nn) assert((a[i] & i) == 0);
  return 0;
}
