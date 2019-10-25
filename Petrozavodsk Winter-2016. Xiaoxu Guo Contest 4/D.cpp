#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n, k;
vector<int> adj[512];
char g[512][512];
int fa[512];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

bool unite(int u, int v) {
    u = find(u); v = find(v);
    fa[u] = v;
    return u != v;
}

vector<int> ans;
void dfs(int u, int p, int c) {
    if (c) ans.push_back(u);
    for (int v : adj[u]) if (v != p) dfs(v, u, !c);
    if (!c) ans.push_back(u);
}

int main() {
    scanf("%d%d", &n, &k);
    iota(fa, fa + n, 0);
    rep (i, n) scanf("%s", g[i]);
    rep (i, n) rep (j, n) if (g[i][j] == '1' and unite(i, j)) {
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    dfs(0, -1, 1);
    for (int x : ans) printf("%d ", x + 1);
    puts("");
    return 0;
}
