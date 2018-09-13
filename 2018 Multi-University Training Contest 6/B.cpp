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

const LL mod = 1000000007;
int fib[2000005], fact[2000005], ifact[2000005], inv[2000005];
int cnt[2000005];
int n, k;

LL powmod(LL b, LL e) {
  LL r = 1;
  while (e) {
    if (e & 1) r = r * b % mod;
    b = b * b % mod;
    e >>= 1;
  }
  return r;
}

LL minv(LL x) {
  return powmod(x, mod - 2);
}

void init() {
  fib[0] = 1; fib[1] = 2;
  for (int i = 2; i <= 2000000; i++) {
    fib[i] = 1ll * fib[i-1] * fib[i-2] % mod;
  }
  for (int i = 0; i <= 2000000; i++) {
    fib[i] += mod - 1;
    if (fib[i] >= mod) fib[i] -= mod;
  }
  fact[0] = 1;
  Rep (i, 2000000) fact[i] = 1ll * fact[i-1] * i % mod;
  inv[1] = 1;
  for (int i = 2; i <= 2000000; i++) 
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
  ifact[0] = 1;
  Rep (i, 2000000) ifact[i] = 1ll * ifact[i-1] * inv[i] % mod;
}

LL binom(LL m, LL n) {
  return 1ll * fact[m] * ifact[n] % mod * ifact[m-n] % mod;
}

LL subsolve(LL n, LL m) {
  if (m < 0) return 0;
  return binom(m+n-1, n-1);
}

int main() {
  int T; scanf("%d", &T);
  init();
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      if (n % i) continue;
      cnt[i] = subsolve(k, n/i);
    }
    
    for (int i = n; i; i--) {
      if (n % i) continue;
      for (int j = i + i; j <= n; j += i) {
        cnt[i] += mod - cnt[j];
        if (cnt[i] >= mod) cnt[i] -= mod;
      }
    } 
    LL tot = 0, cc = 0;
    for (int i = 1; i <= n; i++) {
      if (cnt[i] == 0) continue;
      tot += 1ll * fib[i] * cnt[i] % mod;
      cc += cnt[i];
      cnt[i] = 0;
    }
    tot %= mod; cc %= mod;

    cout << tot * minv(cc) % mod << endl;
  }
  return 0;
}
