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
vector<pair<int, int>> adj[2048];
bool ok[2048][2048], may_use[2048];
LL dist[2048][2048];

vector<pair<int, LL>> hull;

void add(int k, LL b) {
    while (true) {
        if (hull.empty()) {
            hull.emplace_back(k, b);
            return;
        }
        if (b > hull.back().second) return;
        if (hull.size() == 1) {
            hull.emplace_back(k, b);
            return;
        }
        int k1, k2; LL b1, b2;
        tie(k1, b1) = hull.back(); tie(k2, b2) = hull.rbegin()[1];
        LL v1 = k1 * (b - b2) + b1 * (k2 - k), v2 = k2 * b - k * b2;
        if (v1 < v2) {
            hull.pop_back();
        } else {
            hull.emplace_back(k, b);
            return;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    Rep (i, n) rep (j, n + 1) dist[i][j] = LLONG_MAX;
    dist[1][0] = 0;
    rep (_, m) {
        int u, v, l; scanf("%d%d%d", &u, &v, &l);
        adj[u].emplace_back(v, l);
        adj[v].emplace_back(u, l);
    }
    rep (d, n) {
        Rep (u, n) {
            if (dist[u][d] == LLONG_MAX) continue;
            for (auto p : adj[u]) {
                int v, w; tie(v, w) = p;
                dist[v][d+1] = min(dist[v][d+1], dist[u][d] + w);
            }
        }
    }
    Rep (d, n) if (dist[n][d] < LLONG_MAX) add(d, dist[n][d]);
    for (auto p : hull) ok[n][p.first] = true;
    for (int d = n - 1; d >= 0; d--) {
        Rep (u, n) {
            if (dist[u][d] == LLONG_MAX) continue;
            for (auto p : adj[u]) {
                int v, w; tie(v, w) = p;
                if (ok[v][d+1] and dist[v][d+1] == dist[u][d] + w)
                    ok[u][d] = true;
            }
        }
    }
    Rep (i, n) if (accumulate(range(ok[i]), 0)) may_use[i] = true;
    int cnt = n - accumulate(range(may_use), 0); printf("%d\n", cnt);
    Rep (i, n) if (!may_use[i]) printf("%d ", i);
    puts("");
    return 0;
}
