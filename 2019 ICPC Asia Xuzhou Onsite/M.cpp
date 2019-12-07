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

const int MAXN = 200005;
int n;
vector<int> adj[MAXN];
int sz[MAXN], fa[MAXN], son[MAXN], cent[MAXN], c2[MAXN];

void dfs1(int u, int p) {
    fa[u] = p; sz[u] = 1;
    int maxw = -1, s = 0;
    for (int v : adj[u]) if (v != p) {
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > maxw) {
            maxw = sz[v];
            s = v;
        }
    }
    son[u] = s;
}

bool is_cent_of(int u, int r) {
    int tot_sz = sz[r];
    return sz[son[u]] * 2 <= tot_sz and (tot_sz - sz[u]) * 2 <= tot_sz;
}

void dfs2(int u, int p) {
    if (son[u] == 0) {
        cent[u] = u;
        return;
    }
    for (int v : adj[u]) if (v != p) dfs2(v, u);
    cent[u] = cent[son[u]];
    while (!is_cent_of(cent[u], u)) cent[u] = fa[cent[u]];
    if (cent[u] != u and is_cent_of(fa[cent[u]], u)) c2[u] = fa[cent[u]];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1, 0); 
    dfs2(1, 0);
    Rep (i, n) {
        if (cent[i] and c2[i] and cent[i] > c2[i]) swap(cent[i], c2[i]);
        printf("%d", cent[i]);
        if (c2[i]) printf(" %d", c2[i]);
        puts("");
    }
    return 0;
}