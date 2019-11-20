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

int n, m;
int fa[1 << 20];
char g[1024][1024];

int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }

int ans;

void unite(int u, int v) {
    u = find(u); v = find(v);
    fa[u] = v;
    if (u == v) ans++;
}

int pt(int x, int y) { return x << 10 | y; }

int main() {
    scanf("%d%d", &n, &m);
    iota(range(fa), 0);
    rep (i, n) scanf("%s", g[i]);
    rep (i, n) rep (j, m) if (g[i][j] == '/') unite(pt(i+1, j), pt(i, j+1));
    else if (g[i][j] == '\\') unite(pt(i, j), pt(i+1, j+1));
    cout << ans << endl;
    return 0;
}
