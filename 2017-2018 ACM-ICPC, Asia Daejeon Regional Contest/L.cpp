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

LL INF = LLONG_MAX >> 5;
LL c[3][52*52*52];
LL cost[52*52*52][52];
LL h[52];

int p;
int n, m;
//  from  cost
vector<pair<int, int>> adj[52];

int main() {
  cin >> p;
  for (int ii=0; ii<p; ii++) {
    cin >> n >> m;
    memset(h, 0, sizeof h);
    memset(cost, 0, sizeof cost);
    for (auto& v : adj) v.clear();
    Rep (i, n) cin >> h[i];
    rep (i, m) {
      int u, v, w;
      cin >> u >> v >> w;
      adj[v].push_back({u, w});
    }
    Rep (i, n) cost[0][i] = INF;
    cost[0][1] = 0;
    for (int d = 1; d <= 50*50*50; d++) {
      Rep (i, n) {
        cost[d][i] = min(cost[d-1][i] + h[i], INF);
        for (auto& p : adj[i]) {
          int u, w; tie(u, w) = p;
          cost[d][i] = min(cost[d][i], cost[d-1][u] + w);
        }
        if (d < 5) {
          _debug("cost[%d][%d]=%lld", d, i, cost[d][i]);
        }
      }
    }
    int a; cin >> a;
    for (int d=0; d<=50*50*50; d++)
      c[ii][d] = cost[d][a];
  }
  LL ans = LLONG_MAX;
  for (int d=0; d<=50*50*50; d++) {
    if (d < 5) {
      _debug("d=%d, c0=%lld, c1=%lld, c2=%lld", d, c[0][d], 
          c[1][d], c[2][d]);
    }   
    ans = min(ans, c[0][d] + c[1][d] + c[2][d]);
  }
  cout << ans << endl;
  return 0;
}
