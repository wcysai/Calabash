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

const int MAXX = 11000;
bool p[MAXX];
int prime[MAXX], sz;

void sieve() {
  p[0] = p[1] = 1;
  for (int i = 2; i < MAXX; i++) {
    if (!p[i]) prime[sz++] = i;
    for (int j = 0; j < sz && i * prime[j] < MAXX; j++) {
      p[i*prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}

const LL mod = 1000000007, inv6 = (mod + 1) / 6;

inline int s2(int n) {
  return 1ll * n * (n+1) / 2 % mod;
}

inline int s3(int n) {
  return 1ll * n * (n+1) % mod * (2*n+1) % mod * inv6 % mod;
}

inline LL func(int k, int m) {
  LL ans = (1ll * k * s2(m / k) % mod + 
      1ll * k * k % mod * s3(m / k) % mod) % mod; 
//  _debug("F[%d, %d] = %lld", k, m, ans);
  return ans;
}

LL solve(int n, int m) {
  vector<int> plist;
  for (int i = 0; prime[i] * prime[i] <= m; i++) {
    if (m % prime[i]) continue;
    plist.push_back(prime[i]);
    while (m % prime[i] == 0) m /= prime[i];
  }
  if (m > 1) plist.push_back(m);
  LL ans = 0;
  int pn = plist.size();
  for (unsigned mask = 0; mask < (1u << pn); mask++) {
    int num = 1;
    for (int i = 0; i < pn; i++) 
      if (mask & (1u << i)) num *= plist[i];
    if (__builtin_popcount(mask) & 1) {
//      _debug("%d (-)", num);
      ans -= func(num, n);
    } else {
//      _debug("%d (+)", num);
      ans += func(num, n);
    }
  }
  ans %= mod; ans += mod; ans %= mod;
  return ans;
}

int main() {
  sieve();
  int n, m;
  int cnt = 0;
  while (scanf("%d%d", &n, &m) != EOF) {
    cnt++;
    LL ans = solve(n, m);
    printf("%lld\n", ans);
  }
  return 0;
}
