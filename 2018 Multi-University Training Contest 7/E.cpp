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

int m, n;
LL mod;
int maxv;
LL inv[1000005];
LL f[1000005];

const int MAXX = 1000006;
bool p[MAXX];
int prime[MAXX], sz;

void sieve() {
  p[0] = p[1] = 1;
  for (int i = 2; i < MAXX; i++) {
    if (!p[i]) prime[sz++] = i;
    for (int j = 0; j < sz && i * prime[j] < MAXX; j++) {
      p[i*prime[j]] = 1;
      if (i%prime[j] == 0) break;
    }
  }
}

void init() {
  inv[1] = 1;
  for (int i = 2; i <= maxv; i++) 
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  
  Rep (i, maxv) f[i] = 1;
  for (int i = 0; i < sz; i++) {
    LL mf = prime[i] * inv[prime[i]-1] % mod;
    for (int j = prime[i]; j <= maxv; j += prime[i]) {
      f[j] = f[j] * mf % mod;
    }
  }
}

LL gcnt[1000005];

int main() {
  sieve();
  int T; cin >> T;
  while (T--) {
    cin >> m >> n >> mod;
    maxv = min(m, n);
    init();
    Rep (i, maxv) gcnt[i] = LL(n / i) * (m / i) % mod;
    for (int i = maxv; i; i--) {
      for (int j = i + i; j <= maxv; j += i) 
        gcnt[i] -= gcnt[j];
    }
    LL tot = 0;
    Rep (i, maxv) {
      tot = tot + gcnt[i] * f[i] % mod;
      if (tot >= mod) tot -= mod;
    }
    cout << tot << endl;
  }
  return 0;
}
