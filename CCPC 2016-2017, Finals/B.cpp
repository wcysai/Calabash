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
typedef long long LL;
typedef unsigned long long ull;

int l, n, m;
LL w[100006], d[100006];
LL t1[1000006], t2[1000006];

typedef pair<LL, int> p;

int main() {
  int T; scanf("%d", &T);
  Rep (t, T) {
    priority_queue<p, vector<p>, greater<p> > q1, q2;
    scanf("%d%d%d", &l, &n, &m);
    rep (i, n) {
      int a; scanf("%d", &a);
      w[i] = a;
      q1.push({w[i], i});
    }
    rep (i, m) {
      int a; scanf("%d", &a);
      d[i] = a;
      q2.push({d[i], i});
    }
    rep (i, l) {
      LL val; int id;
      tie(val, id) = q1.top(); q1.pop();
      _debug("i=%d, val=%lld, id=%lld, l-1-i=%d", i, val, id, l-1-i);
      t1[i] = val;
      q1.push({val+w[id], id});
    }
    rep (i, l) {
      LL val; int id;
      tie(val, id) = q2.top(); q2.pop();
      _debug("i=%d, val=%lld, id=%lld, l-1-i=%d", i, val, id, l-1-i);
      t2[l-1-i] = val;
      q2.push({val+d[id], id});
    }
    LL ans = 0;
    rep (i, l) {
      ans = max(ans, t1[i] + t2[i]);
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
  return 0;
}
