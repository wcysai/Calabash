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

int n, t;
vector<int> adj[1024];

int sum;
vector<pair<int, int>> ssz;

int dfs(int u, int p) {
    int sz = 1;
    for (int v : adj[u]) if (v != p) sz += dfs(v, u);
    return sz;
}

int dfs2(int u, int p) {
    int sz = 1, rk = 0;
    for (int v : adj[u]) if (v != p) {
        int psz = dfs2(v, u);
        rk = max(rk, psz);
        sz += psz;
    }
    rk = max(rk, sum - sz);
    ssz.emplace_back(rk, u);
    return sz;
}

pair<int, int> get_centroid(int u, int p) {
    sum = dfs(u, p);
    ssz.clear(); dfs2(u, p);
    int av, a1, a2 = -1;
    tie(av, a1) = *min_element(range(ssz));
    for (auto& p : ssz) if (p.first == av and p.second != a1) a2 = p.second;
    return {a1, a2};
}

bool verify(int u, int p) {
    int v1, v2; tie(v1, v2) = get_centroid(u, p);
    if (v1 != u and v2 != u) return false;
    for (int v : adj[u]) if (v != p) if (!verify(v, u)) return false;
    return true;
}

int main() {
    scanf("%d%d", &t, &n);
    rep (_, t) {
        Rep (i, n) adj[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v; scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int r1, r2; tie(r1, r2) = get_centroid(1, 0);
        if (verify(r1, 0) or (r2 > 0 and verify(r2, 0))) 
            puts("Centroid");
        else
            puts("Random");
    }
    return 0;
}
