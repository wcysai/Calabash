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

int m, n, k;
LL c[256], v[256];

vector<int> dep[205];
//   id                id  cnt
pair<int, vector<pair<int, int>>> formula[205];

bool flag = false;

void update(int i) {
  LL tot = 0;
  int id = formula[i].first;
  for (auto& item : formula[i].second) {
    tot += c[item.first] * item.second;
  }
  if (tot < c[id]) {
    _debug("update %d!", formula[i].first);
    c[formula[i].first] = tot;
    flag = true;
  }
}

LL dp[10005];

int main() {
  int T; scanf("%d", &T);
  Rep (t, T) {
    scanf("%d%d%d", &m, &n, &k);
    Rep (i, n) {
      int tp; scanf("%d", &tp);
      int co = INT_MAX, va = 0;
      if (tp == 0) {
        scanf("%d", &va);
      } else {
        scanf("%d%d", &co, &va);
      }
      c[i] = co;
      v[i] = va;
    }
    _debug("!");
    rep (i, k) {
      int x, y;
      scanf("%d%d", &x, &y);
      formula[i].first = x;
      formula[i].second.resize(y);
      rep (j, y) {
        int u, v;
        scanf("%d%d", &u, &v);
        formula[i].second[j] = {u, v};
      }
    }
    _debug("!");
    do { // bellman-ford
      flag =  false;
      rep (i, k) update(i);
    } while (flag);
    memset(dp, 0, sizeof dp);
    Rep (i, n) {
      for (int w = c[i]; w <= m; w++) {
        dp[w] = max(dp[w], dp[w - c[i]] + v[i]);
      }
    }
    printf("Case #%d: %d\n", t, int(dp[m]));
  }
  return 0;
}
