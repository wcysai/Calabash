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

constexpr LL mod = 1000000007;
int n;
vector<int> adj[100005];
int depth[100005], sz[100005];
tuple<int, int, int> edges[100005];

void dfs(int u, int p, int dep) {
  depth[u] = dep;
  sz[u] = 1;
  for (int v : adj[u]) {
    if (v == p) continue;
    dfs(v, u, dep + 1);
    sz[u] += sz[v];
  }
}

int main() {
  while (scanf("%d", &n) == 1) {
    Rep (i, n) adj[i].clear();
    for (int i = 1; i < n; i++) {
      int u, v, w; scanf("%d%d%d", &u, &v, &w);
      adj[u].push_back(v);
      adj[v].push_back(u);
      edges[i] = make_tuple(u, v, w);
    }
    dfs(1, 0, 0);
    LL tot = 0, fact = 2;
    for (int i = 1; i < n; i++) fact = fact * i % mod;
    for (int i = 1; i < n; i++) {
      int u, v, w; tie(u, v, w) = edges[i];
      if (depth[u] < depth[v]) swap(u, v);
      tot += 1ll * sz[u] * (n - sz[u]) % mod * w % mod;
      tot %= mod;
    }
    cout << tot * fact % mod << endl;
  }
  return 0;
}
