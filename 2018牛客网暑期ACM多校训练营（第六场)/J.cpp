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
 
unsigned x, y, z;
inline unsigned next() {
  unsigned t;
  x ^= x << 16;
  x ^= x >> 5;
  x ^= x << 1;
  t = x;
  x = y;
  y = z;
  z = t ^ x ^ y;
  return z;
}
 
int n;
unsigned arr[10000005];
 
ULL gcd(ULL x, ULL y) {
  if (x == 0) return y;
  return gcd(y%x, x);
}
 
ULL lcm(ULL x, ULL y) {
  return x / gcd(x, y) * y;
}
 
int main() {
  int T; cin >> T;
  for (int t = 1; t <= T; t++) {
    cin >> n >> x >> y >> z;
    rep (i, n) arr[i] = next();
    ULL maxv = 0;
    if (n <= 100) {
      rep (i, n) rep (j, i) maxv = max(maxv, lcm(arr[i], arr[j]));
    } else {
      nth_element(arr, arr+100, arr+n, greater<unsigned>());
      rep (i, 100) rep (j, i) maxv = max(maxv, lcm(arr[i], arr[j]));
    }
    cout << "Case #" << t << ": " << maxv << endl;
 
  }
  return 0;
}
