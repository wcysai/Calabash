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

int n;
int a[1000005];

const LL mod = 1000000007;
LL inv[1000005], fact[1000005], ifact[1000005];


int par[1000005], sz[1000005];
LL cnt[1000005];

void tinit() { 
  rep (i, n) par[i] = i; 
  rep (i, n) cnt[i] = sz[i] = 1;
}

int parent(int x) {
  if (par[x] == x) return x;
  return par[x] = parent(par[x]);
}

void unite(int from, int to) {
  from = parent(from);
  par[from] = to;
}

LL combine(int m, int n) {
  return fact[m] * ifact[n] % mod * ifact[m-n] % mod;
}

LL powmod(LL b, LL e) {
  LL r = 1;
  while (e) {
    if (e & 1) r = r * b % mod;
    b = b * b % mod;
    e >>= 1;
  }
  return r;
}

void init() {
  const int maxn = 1000000;
  fact[0] = ifact[0] = 1;
  Rep (i, maxn) fact[i] = i * fact[i-1] % mod;
  ifact[maxn] = powmod(fact[maxn], mod - 2);
  for (int i = maxn; i; i--) ifact[i-1] = i * ifact[i] % mod;
  Rep (i, maxn) inv[i] = fact[i-1] * ifact[i] % mod;
}

int main() {
  init();
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    tinit();
    vector<pair<int, int>> p(n);
    rep (i, n) {
      int x; scanf("%d", &x);
      p[i] = {x, -i};
    }
    sort(range(p));
    rep (i, n) { a[-p[i].second] = i; }
    LL lastcnt = 0;
    rep (i, n) {
      int pos = -p[i].second;
      int lflag = 1, rflag = 1, lpos, rpos;
      lpos = pos - 1; rpos = pos + 1;
      if (lpos < 0) lflag = 0; 
      else {
        lpos = parent(lpos);
        if (a[lpos] > a[pos]) lflag = 0;
      }
      if (rpos >= n) rflag = 0;
      else {
        rpos = parent(rpos);
        if (a[rpos] > a[pos]) rflag = 0;
      }

//    _debug("lpos=%d, rpos=%d, lflag=%d, rflag=%d", 
//          lpos, rpos, lflag, rflag);

      if (lflag == 0 && rflag == 0) {
        lastcnt = cnt[pos];
      } else if (rflag == 0) {
        lastcnt = cnt[pos] = cnt[lpos];
        sz[pos] = sz[lpos] + 1;
        unite(lpos, pos);
      } else if (lflag == 0) {
        lastcnt = cnt[pos] = cnt[rpos];
        sz[pos] = sz[rpos] + 1;
        unite(rpos, pos);
      } else {
//        _debug("lcnt=%lld, rcnt=%lld", cnt[lpos], cnt[rpos]);
        lastcnt = cnt[pos] = cnt[lpos] * cnt[rpos] % mod * 
          combine(sz[lpos] + sz[rpos], sz[lpos]) % mod;
        sz[pos] = sz[lpos] + sz[rpos] + 1;
        unite(rpos, pos);
        unite(lpos, pos);
      } 
//     _debug("pos=%d, cnt=%lld", pos, lastcnt); 
    }
//    rep (i, n) cout << a[i] << ' '; cout << endl;
    printf("%d\n", int(lastcnt * ifact[n] % mod * n % mod * inv[2] % mod));
  }
  return 0;
}
