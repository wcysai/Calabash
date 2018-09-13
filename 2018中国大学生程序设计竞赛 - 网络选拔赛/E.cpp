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

namespace sieve {
  constexpr int MAXN = 1000007;
  bool p[MAXN];
  int prime[MAXN], sz;
  int pval[MAXN], pcnt[MAXN];
  int f[MAXN];

  void exec(int N = MAXN) {
    p[0] = p[1] = 1;
    
    pval[1] = 1;
    pcnt[1] = 0;
    f[1] = 1;

    for (int i = 2; i < N; i++) {
      if (!p[i]) {
        prime[sz++] = i;
        for (LL j = i; j < N; j *= i) {
          int b = j / i;
          pval[j] = i * pval[b];
          pcnt[j] = pcnt[b] + 1;
          f[j] = f[b] * (pcnt[j] & 1 ? 1 : i); // f[j] = f(i^pcnt[j])
        }
      }
      for (int j = 0; i * prime[j] < N; j++) {
        int x = i * prime[j]; p[x] = 1;
        if (i % prime[j] == 0) {
          pval[x] = pval[i] * prime[j];
          pcnt[x] = pcnt[i] + 1;
        } else {
          pval[x] = prime[j];
          pcnt[x] = 1;
        }
        if (x != pval[x]) {
          f[x] = f[x / pval[x]] * f[pval[x]];
        }
        if (i % prime[j] == 0) break;
      }
    }
  }
}

LL p, A, B, n;
typedef pair<LL, LL> num;

inline num mknum(LL a, LL b) {
  a %= p; b %= p;
  if (a < 0) a += p;
  if (b < 0) b += p;
  return {a, b};
}

inline num operator + (num a, num b) {
  return {(a.first + b.first) % p,
          (a.second + b.second) % p};
}

inline num operator - (num a, num b) {
  return {(p + a.first - b.first) % p,
          (p + a.second - b.second) % p};
}

inline num operator - (num b) {
  return {(p - b.first) % p,
          (p - b.second) % p};
}

inline num operator * (num a, num b) {
  LL x1, y1, x2, y2;
  tie(x1, y1) = a; tie(x2, y2) = b;
  return {(x1 * x2 % p + y1 * y2 % p * B % p) % p,
          (x2 * y1 + x1 * y2) % p};
}

num powmod(num b, LL e) {
  num r = {1, 0};
  while (e) {
    if (e & 1) r = r * b;
    b = b * b;
    e >>= 1;
  }
  return r;
}

int main() {
  sieve::exec();
  int T; scanf("%d", &T);

  while (T--) {
    scanf("%lld%lld%lld%lld", &A, &B, &n, &p);
    p *= 2;
    num a = powmod(mknum(A, 1), n), b = powmod(mknum(A, -1), n);
    num res = a - b;
    assert(res.first == 0);
    
    LL a1 = res.second / 2; p /= 2;
    LL b1 = B;
    a1 = a1 * sieve::f[B] % p;
    b1 /= sieve::f[B] * sieve::f[B];

    printf("1 %d %d\n", int(a1), int(b1));
  }
  return 0;
}
