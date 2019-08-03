// #pragma GCC optimize(3)
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
vector<int> adj[100005];
int d[2][21][100005], w[100005];
vector<int> pq[100005];
bool done[100005];
int sz[2];
LL tot;

void sssp(int src, int d[]) {
    vector<int> q; q.push_back(src);
    int ptr = 0;

    fill(d, d + n + 1, -1);
    d[src] = 0;

    while (ptr < q.size()) {
        int u = q[ptr++];
        for (int v : adj[u]) if (d[v] == -1) {
            d[v] = d[u] + 1;
            q.push_back(v);
        }
    }
}

LL work(int u, int v) {
    Rep (i, n) w[i] = d[0][u][i] + d[1][v][i];

    fill(done, done + n + 1, 0);
    for (int i = 0; i <= m; i++) pq[i].clear();
    Rep (i, n) pq[w[i]].push_back(i);
    for (int i = 0; i <= m; i++) {
        while (pq[i].size()) {
            int u = pq[i].back(); pq[i].pop_back();
            if (done[u]) continue;
            for (int v : adj[u]) if (w[v] > w[u] + 1) {
                w[v] = w[u] + 1;
                pq[w[v]].push_back(v);
            }
            done[u] = true;
        }
    }
    return accumulate(w + 1, w + n + 1, 0ll);
}

int main() {
    int T; scanf("%d", &T);
    Rep (t, T) {
        scanf("%d%d", &n, &m);
        Rep (i, n) adj[i].clear();
        tot = 0;
        rep (i, m) {
            int u, v; scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        rep (i, 2) {
            scanf("%d", sz + i);
            rep (j, sz[i]) {
                int src; scanf("%d", &src);
                sssp(src, d[i][j]);
            }
        }
        LL num = 0;
        rep (u, sz[0]) rep (v, sz[1]) num += work(u, v);
        LL denom = 1ll * sz[0] * sz[1] * n, g = __gcd(num, denom);
        num /= g; denom /= g;
        printf("Case #%d: ", t);
        if (denom == 1) printf("%lld\n", num);
        else printf("%lld/%lld\n", num, denom);
    }
    return 0;
}
