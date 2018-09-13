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
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

inline int lowbit(int x) { return x&-x; }

struct bit_purq {
  int N;
  vector<LL> tr;

  void init(int n) { tr.assign(N = n + 5, 0); }
  
  LL query(int n) {
    LL ans = 0;
    while (n < N) {
      ans += tr[n];
      n += lowbit(n);
    }
    return ans; 
  } 

  void add(int n, LL x) {
    while (n) {
      tr[n] += x;
      n -= lowbit(n);
    }
  }
} bit;

int n, x, y;
int cnt[100005];

int main() {
  while (scanf("%d%d%d", &n, &x, &y) != EOF) {
    vector<pair<int, int>> vp(n);
    rep (i, n) {
      scanf("%d", &(vp[i].first));
      vp[i].second = i;
    }
    sort(range(vp));
    bit.init(n);
    LL ans = 0;
    rep (i, n) {
      _debug("%d @ %d", vp[i].first, vp[i].second);
      int pos = vp[i].second + 1;
      ans += bit.query(pos);
      bit.add(pos, 1);
    }
    cout << ans * min(x, y) << endl;
  }
  return 0;
}
