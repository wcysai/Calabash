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

int n;
vector<int> adj[1024];
int sz[1024];

void dfs(int u, int p) {
    if (adj[u].size() == 1 and p) {
        sz[u] = 1;
        return;
    } else {
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

typedef complex<double> cplx;
cplx pos[1024];

void draw(int u, int p, cplx pt, double al, double ar) {
    pos[u] = pt;
    double slice = (ar - al) / sz[u], pos = al, npos;
    for (int v : adj[u]) {
        if (v == p) continue;
        npos = pos + sz[v] * slice;
        draw(v, u, pt + polar(1.0, (pos + npos) / 2.0), pos, npos);
        pos = npos;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    draw(1, 0, 0, 0, acos(-1));
    Rep (i, n) printf("%.14f %.14f\n", pos[i].real(), pos[i].imag());
    return 0;
}
