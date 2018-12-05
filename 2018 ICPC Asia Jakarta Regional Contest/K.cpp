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

int fa[100005];

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

bool unite(int u, int v) {
    u = find(u); v = find(v);
    fa[u] = v;
    return u != v;
}

int n, m, vi;
int id[200005];
bool vis[2000005];
vector<int> adj[200005];

void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

vector<tuple<int, int, int>> ans;

bool dfs(int u, int p) {
    vis[u] = true;
    vector<int> cid;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (dfs(v, u)) cid.push_back(v);   
    }
    while (cid.size() > 1) {
        int x = cid.back(); cid.pop_back();
        int y = cid.back(); cid.pop_back();
        ans.emplace_back(id[x], id[u], id[y]);
    }
    if (cid.size()) {
        if (p) ans.emplace_back(id[cid[0]], id[u], id[p]);
        return false;
    } else {
        return true;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    vi = n;
    Rep (i, n) fa[i] = id[i] = i;
    
    rep (_, m) {
        int u, v; scanf("%d%d", &u, &v);
        if (unite(u, v)) {
            add_edge(u, v);
        } else {
            id[++vi] = v;
            add_edge(u, vi);
        }
    }
    /*
    Rep (i, vi) {
        printf("[%d: real %d] ", i, id[i]);
        for (int c : adj[i]) {
            printf("%d ", c);
        }
        puts("");
    }
*/
    Rep (i, vi) 
        if (!vis[i]) dfs(i, 0);
    
    printf("%d\n", int(ans.size()));
    for (auto p : ans) {
        int u, v, w; tie(u, v, w) = p;
        printf("%d %d %d\n", u, v, w);
    }
    return 0;
}
