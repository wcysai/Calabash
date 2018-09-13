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

inline int lowbit(int x) { return x & -x ; }

struct bit_purq {
  int N;
  vector<LL> tr;

  void init(int n) {
    tr.resize(N = n + 5);
  }

  LL sum(int n) {
    if (n <= 0) return 0;
    LL ans = 0;
    while (n) {
      ans += tr[n];
      n -= lowbit(n);
    }
    return ans;
  }

  void add(int n, LL x) {
    while (n < N) {
      tr[n] += x;
      n += lowbit(n);
    }
  } 
};

struct bit_rurq {
  bit_purq d, di;

  void init(int n) { 
    d.init(n); di.init(n);
  }

  void add(int l, int r, LL x) {
//    _debug("%d %d += %lld", l, r, x);
    d.add(l, x); d.add(r+1, -x);
    di.add(l, x*l); di.add(r+1, -x*(r+1));
  }

  LL query(int l, int r) {
    return (r+1) * d.sum(r) - di.sum(r) - l * d.sum(l-1) + di.sum(l-1);
  }
} bit;

int n, q;
int main() {
  scanf("%d%d", &n, &q);
  bit.init(n);
  Rep (i, n) {
    int x; scanf("%d", &x);
    bit.add(i, n, x);
  }
  /*
  Rep (i, n) {
    _debug("a[%d]=%lld", i, bit.query(i, i));
  }
  */
  Rep (i, q) {
    int a, b, c; scanf("%d%d%d", &a, &b, &c);
    if (a == 1) {
//      _debug("query: %d %d", b, c);
      printf("%lld\n", bit.query(b, c) - (c-b+1) * bit.query(b - 1, b - 1));
    } else {
      LL y = bit.query(b, b) - bit.query(b-1, b-1);
      bit.add(b, n, c - y);
/*
  Rep (i, n) {
    _debug("a[%d]=%lld", i, bit.query(i, i));
  }
  */
    }
  }
  return 0;
}
