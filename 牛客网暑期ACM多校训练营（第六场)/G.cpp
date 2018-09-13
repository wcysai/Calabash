// #pragma GCC optimize("sanitize=undefined")
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
vector<int> adj[100005];
int depth[100005];
LL ud[100005], totd[100005];
LL sz[100005], usz[100005], wt[100005];
 
void dfs(int u, int p, int dep) {
  sz[u] = 1;
  depth[u] = dep;
  for (int v : adj[u]) {
    if (v == p) continue;
    dfs(v, u, dep+1);
    sz[u] += sz[v];
//    ud[u] += ud[v] + sz[v] * wt[v];
  }
  usz[u] = n - sz[u];
}
 
void dfs1(int u, int p) {
  ud[u] = 0;
  for (int v : adj[u]) {
    if (v == p) continue;
    dfs1(v, u);
    ud[u] += ud[v] + sz[v] * wt[v];
  }
//  _debug("ud[%d] = %lld", u, ud[u]);
}
 
void dfs2(int u, int p, LL upd) {
//  _debug("upd[%d]=%lld, wt=%lld, usz=%d", u, upd, wt[u], usz[u]);
  totd[u] = ud[u] + upd;
  LL td = upd;
  for (int v : adj[u]) {
    if (v == p) continue;
    td += ud[v] + sz[v] * wt[v];
  }
  for (int v :  adj[u]) {
    if (v == p) continue;
    LL ctd = td - ud[v] - sz[v] * wt[v];
    dfs2(v, u, ctd + wt[v] * usz[v]);
  }
}
 
int main() {
  int T; scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    /*
    memset(depth, 0, sizeof depth);
    memset(ud, 0, sizeof ud);
    memset(totd, 0, sizeof totd);
    memset(usz, 0, sizeof usz);
    memset(wt, 0, sizeof wt);
    */
    scanf("%d", &n);
    Rep (i, n) adj[i].clear();
    {
      vector<tuple<int, int, int>> tup;
      for (int i = 1; i < n; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back(v);
        adj[v].push_back(u);
        tup.push_back(make_tuple(u, v, w));
      }
      dfs(1, 0, 0);
      for (auto& tu : tup) {
        int u, v, w; tie(u, v, w) = tu;
        if (depth[u] < depth[v]) wt[v] = w;
        else wt[u] = w;
      }
    }
    dfs1(1, 0);
    dfs2(1, 0, 0);
    __int128 ans = 0;
//    Rep (i, n) _debug("totd[%d]=%d", i, int(totd[i]));
     
     
    sort(totd+1, totd+n+1);
    Rep (i, n) ans += totd[i] * (n-i);
const __int128 LIMIT = 1000000000000000000;
    if (ans >= LIMIT) {
      printf("Case #%d: %lld%018lld\n", t, LL(ans / LIMIT), LL(ans % LIMIT));
    } else {
      printf("Case #%d: %lld\n", t, LL(ans));
    }
  }
  return 0;
}
