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

inline int lowbit(int x) { return x & -x; }

const int MAXN = 10005;
int n, m;
pair<int, int> pos[MAXN];
vector<int> adj[MAXN];
vector<int> ord;
int clr[MAXN];
bool vis[MAXN];

void probe(int u, int cmask) {
    if (vis[u]) return; vis[u] = true;
    for (int v : adj[u]) if (clr[v] & cmask) probe(v, cmask);
}

void recolor(int u, int cmask) {
    vis[u] = true; clr[u] = cmask ^ clr[u];
    for (int v : adj[u]) if (!vis[v] and (clr[v] & cmask)) recolor(v, cmask);
}

int main() {
    scanf("%d%d", &n, &m);
    Rep (i, n) { scanf("%d%d", &pos[i].first, &pos[i].second); ord.push_back(i); }
    rep (_, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    sort(range(ord), [] (int l, int r) { return pos[l] < pos[r]; });
    for (int u : ord) {
        int mask = 0;
        for (int v : adj[u]) mask |= clr[v];
        if (mask == 0xf) {
            vector<int> cs;
            for (int v : adj[u]) if (clr[v]) cs.push_back(v);
            sort(range(cs), [u] (int x, int y) {
                return atan2(pos[x].second - pos[u].second, pos[x].first - pos[u].first)
                    <  atan2(pos[y].second - pos[u].second, pos[y].first - pos[u].first);
            });
            assert(cs.size() == 4);
            memset(vis, 0, sizeof vis); probe(cs[0], clr[cs[0]] | clr[cs[2]]);
            if (!vis[cs[2]]) {
                memset(vis, 0, sizeof vis);
                recolor(cs[0], clr[cs[0]] | clr[cs[2]]);
                mask = 0; for (int v : adj[u]) mask |= clr[v];
            } else {
                memset(vis, 0, sizeof vis);
                recolor(cs[1], clr[cs[1]] | clr[cs[3]]);
                mask = 0; for (int v : adj[u]) mask |= clr[v];
            }
        }
        assert(mask < 0xf);
        clr[u] = lowbit(0xf ^ mask);
    }
    Rep (i, n) printf("%d\n", 1 + __builtin_ctz(clr[i]));
    return 0;
}
