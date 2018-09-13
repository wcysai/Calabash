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

namespace lca {
  const int MAXN = 300005;
  vector<int> adj[MAXN];
  int sz[MAXN], top[MAXN], fa[MAXN], son[MAXN], depth[MAXN], id[MAXN];

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs1(int x, int dep, int par){
      depth[x] = dep;
      sz[x] = 1;
      fa[x] = par;
      int maxn = 0, s = 0;
      for (int c: adj[x]){
          if (c == par) continue;
          dfs1(c, dep + 1, x);
          sz[x] += sz[c];
          if (sz[c] > maxn){
              maxn = sz[c];
              s = c;
          }
      }
      son[x] = s;
  }

  int cid = 0;
  void dfs2(int x, int t){
      top[x] = t;
      id[x] = ++cid;
      if (son[x]) dfs2(son[x], t);
      for (int c: adj[x]){
          if (c == fa[x]) continue;
          if (c == son[x]) continue;
          else dfs2(c, c);
      }
  }

  void decomp(int root){
      dfs1(root, 1, 0);
      dfs2(root, root);
  }

  int query(int u, int v){
    int ans = 0;
//    _debug("u=%d, v=%d, pu=%d, pv=%d", u, v, top[u], top[v]);
    while (top[u] != top[v]){
      if (depth[top[u]] < depth[top[v]]) swap(u, v);
      ans += id[u] - id[top[u]];
      // id[top[u]] to id[u]
      u = fa[top[u]];
      ans++;
    }
//    _debug("u=%d, v=%d, pu=%d, pv=%d", u, v, top[u], top[v]);
    if (depth[u] > depth[v]) swap(u, v);
    // id[u] to id[v]
    ans += id[v] - id[u];
    return ans;
  }
}

int fa[300005];

void init(int n) {
  Rep (i, n) fa[i] = i;
}

int find(int x) {
  if (fa[x] == x) return x;
  return fa[x] = find(fa[x]);
}

bool unite(int u, int v) {
  u = find(u); v = find(v);
  fa[u] = v;
  return u != v;
}

int n, m;

inline int id(int x, int y) {
  x--; y--;
  return x * m + y;
}

int u, v, w;

int main() {
  scanf("%d%d", &n, &m);
  vector<tuple<int, int, int>> edges;
  init(n * m);
  Rep (i, n) {
    Rep (j, m) {
      int w1, w2; scanf("%*s %d %*s %d", &w1, &w2);
      if (i < n) edges.emplace_back(id(i, j), id(i+1, j), w1);
      if (j < m) edges.emplace_back(id(i, j), id(i, j+1), w2);
    }
  }
  sort(range(edges), [] (tuple<int, int, int>& e1, tuple<int, int, int>& e2) {
        return get<2>(e1) > get<2>(e2);
      });
  int cnt = n * m - 1;
  for (auto& e : edges) {
    int u, v, w; tie(u, v, w) = e;
    if (unite(u, v)) {
      _debug("+ %d %d", u, v);
      lca::add_edge(u, v);
      cnt --;
      if (cnt == 0) break;
    }
  }
  lca::decomp(0);
  int q; scanf("%d", &q);
  while (q--) {
    int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    int id1 = id(x1, y1), id2 = id(x2, y2);
    _debug("%d %d", id1, id2);
    printf("%d\n", lca::query(id1, id2));
  }
  return 0;
}
