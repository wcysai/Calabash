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
int fa[100005], son[100005], dep[100005], dep2[100005];

void decomp(int u, int p) {
  fa[u] = p;
  dep[u] = 1;
  for (int& v : adj[u]) {
    if (v == p) continue;
    decomp(v, u);
    if (dep[v] + 1 >= dep[u]) {
      dep2[u] = dep[u] - 1;
      dep[u] = dep[v] + 1;
      son[u] = v;
    } else {
      dep2[u] = max(dep2[u], dep[v]);
    }
  }
  if (dep[u] == 0) dep[u] = 1;
  _debug("u=%d, fa=%d, son=%d, dep=%d, dep2=%d", 
      u, fa[u], son[u], dep[u], dep2[u]);
}

LL ans = 0;

pair<vector<LL>, deque<LL>> dfs(int u) {
  vector<LL> f;
  deque<LL> g; 
  if (son[u] == 0) {
    f.push_back(1);
    g.push_back(0);
    return {f, g};
  }
  tie(f, g) = dfs(son[u]);
  ans += g[0];
  g.pop_front(); g.resize(dep[u]);
  vector<LL> sf(dep2[u]), sf2(dep2[u]), sf3(dep2[u]), sg(dep2[u]);
  LL totfg = 0;
  for (int i = 0; i < dep2[u]; i++) {
    sf.rbegin()[i] += f.rbegin()[i];
    sf2.rbegin()[i] += f.rbegin()[i] * f.rbegin()[i]; 
    sf3.rbegin()[i] += f.rbegin()[i] * f.rbegin()[i] * f.rbegin()[i];
    totfg -= f.rbegin()[i] * g[i];
    sg[i] += g[i];
  }
  for (int v : adj[u]) {
    if (v == fa[u] or v == son[u]) continue;
    vector<LL> ff;
    deque<LL> gg; tie(ff, gg) = dfs(v);
    ans += gg[0]; gg.pop_front(); gg.resize(ff.size());
    for (int i = 0; i < ff.size(); i++) {
      f.rbegin()[i] += ff.rbegin()[i];
      sf.rbegin()[i] += ff.rbegin()[i];
      sf2.rbegin()[i] += ff.rbegin()[i] * ff.rbegin()[i];
      sf3.rbegin()[i] += ff.rbegin()[i] * ff.rbegin()[i] * ff.rbegin()[i];
      totfg -= ff.rbegin()[i] * gg[i];
    }
    for (int i = 0; i < gg.size(); i++) {
      g[i] += gg[i];
      sg[i] += gg[i];
    }
  }
  _debug("u=%d, g[0]=%lld", u, g[0]);
  for (int i = 0; i < dep2[u]; i++) { // triplet in three subtrees
    totfg += sf.rbegin()[i] * sg[i];
    LL inc = (sf.rbegin()[i] * sf.rbegin()[i] * sf.rbegin()[i] + 
        2 * sf3.rbegin()[i] - 3 * sf2.rbegin()[i] * sf.rbegin()[i]) / 6;
    _debug("%d i=%d, inc=%lld", u, i, inc);
    ans += inc;
    g[i] += (sf.rbegin()[i] * sf.rbegin()[i] - sf2.rbegin()[i]) / 2;
  }
  _debug("totfg %d = %lld", u, totfg);
  ans += totfg;
  f.push_back(1); // current node;
  // cout << "g of " << u << " : " ;
  // for (auto x : g) cout << x << ' '; cout << endl;
  return {f, g};
}

int main() {
  scanf("%d", &n);
  rep (i, n - 1) {
    int u, v; scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  decomp(1, 0);
  dfs(1);
  cout << ans << endl;
  return 0;
}
