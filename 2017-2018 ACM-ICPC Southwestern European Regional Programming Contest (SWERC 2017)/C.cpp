#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
  __func__, ##__VA_ARGS__)
#else
# define _debug(...) (void(0))
#endif

#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long ll;
typedef unsigned long long ull;

int nn;
unsigned n;
ll mm;

const int MAXN = 300;
const ll modular = 1000000000;

struct matrix {
  ll m[MAXN][MAXN];

  void operator *= (matrix& a) {
    static ll t[MAXN][MAXN];
    rep (i, n) {
      rep (j, n) {
        t[i][j] = 0;
        rep (k, n) {
          t[i][j] += (m[i][k] * a.m[k][j]) % modular;
          t[i][j] %= modular;
        }
      }
    }
    memcpy(m, t, sizeof(t));
  }
} mat;

matrix r;
void m_powmod(matrix& b, ll e) {
  memset(r.m, 0, sizeof(r.m));
  rep (i, n) r.m[i][i] = 1;
  while (e) {
    if (e&1) r*= b;
    b*=b;
    e>>=1;  
  }
}

const ll table[10] = {
  1, 1, 2, 3, 5, 8, 13, 21, 34, 55
};

int main() {
  cin >> nn >> mm;
  n = (1 << nn);
  for (unsigned u = 0; u < n; u++) {
    for (unsigned v = 0; v < n; v++) {
      _debug("%d %d", u, v);
      if ((u|v) != v) continue;
      unsigned mask = v ^ u;
      ll ans = 1;
      while (mask) {
//        _debug("%u", mask);
        while ((mask&1) == 0) mask>>=1;
        int cnt = 0;
        while (mask&1) {
          mask>>=1;
          cnt++;
        }
        ans *= table[cnt];
      }
      mat.m[n-1-v][u] = ans % modular;
//      _debug("%d %d", u, v);
    }
  }
  /*
  rep (i, n) {
    rep (j, n) printf("%lld\t", mat.m[i][j]); puts("");
  }*/
  m_powmod(mat, mm);
  /*
  rep (i, n) {
    rep (j, n) printf("%lld\t", mat.m[i][j]); puts("");
  }*/
  cout << r.m[0][0] << endl;
  return 0;
}
