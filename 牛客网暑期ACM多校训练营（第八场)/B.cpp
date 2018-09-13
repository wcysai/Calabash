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
 
const LL mod = 998244353;
 
LL powmod(LL b, LL e) {
  LL r = 1;
  while (e) {
    if (e & 1) r = r * b % mod;
    b = b * b % mod;
    e >>= 1;
  }
  return r;
}
 
LL inv(LL x) {
  return powmod(x, mod - 2);
}
 
int main() {
  int N; cin >> N;
  vector<LL> ans = {1, 2};
  for (int n = 3; n <= N; n++) {
    LL p1 = ans.rbegin()[0], p2 = ans.rbegin()[1];
    ans.push_back(
        (p1 * (6 * n - 9) % mod + mod - (n - 3) * p2 % mod) % mod
        * inv(n) % mod
      );
  }
  cout << ans[N-1] << endl;
  return 0;
}
