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

int n, m, d;
set<int> adj[200005];

int fa[200005];
int find(int x) { return fa[x] < 0 ? x : fa[x] = find(fa[x]); }
void unite(int u, int v) { 
    u = find(u); v = find(v);
    if (u == v) return;
    fa[v] += fa[u];
    fa[u] = v;
    return ;
}

set<int> vis;

void dfs(int u) {
    if (vis.count(u)) return;
    vis.insert(u);
    for (int v : adj[u]) dfs(v);
}

int main() {
    scanf("%d%d%d", &n, &m, &d);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].insert(v);
        adj[v].insert(u);
    }
    vector<int> q;
    Rep (i, n) if (adj[i].size() < d) q.push_back(i);
    while (q.size()) {
        int u = q.back(); q.pop_back();
        if (adj[u].empty()) continue;
        for (int v : adj[u]) {
            adj[v].erase(u);
            if (adj[v].size() < d) q.push_back(v);
        }
        adj[u].clear();
    }
    fill(fa + 1, fa + n + 1, -1);
    Rep (u, n) for (int v : adj[u]) unite(u, v);
    Rep (i, n) if (adj[i].size() == 0) fa[i] = INT_MAX;
    int s = min_element(fa + 1, fa + n + 1) - fa;
    if (fa[s] > 0) puts("NIE"); else {
        dfs(s);
        printf("%d\n", int(vis.size()));
        for (int x : vis) printf("%d ", x); 
        puts("");
    }
    return 0;
}
