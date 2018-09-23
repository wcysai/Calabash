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
vector<int> adj[2505];
int sz[2505], depth[2505], wt[2505];

const LL mod = 1000000007;
LL ans = 0;

LL fact[2505], ifact[2505];
LL factor[2505];

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

LL comb(LL u, LL v) {
    return fact[u] * (ifact[v] * ifact[u - v] % mod) % mod;
}

void init() {
    fact[0] = ifact[0] = 1;
    Rep (i, m) fact[i] = fact[i-1] * i % mod;
    Rep (i, m) ifact[i] = ifact[i-1] * powmod(i, mod - 2) % mod;

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j + i <= m; j++) {
            factor[j] += comb(m, i) * comb(m, i+j) % mod;
            factor[j] %= mod;
        }
        _debug("%d, %lld", i, factor[i]);
    }
}

LL compute(LL l, LL r) {
    LL tot = m * powmod(n, m + m) % mod, fac = powmod(l * r % mod, m);
    LL invl = powmod(l, mod - 2), invr = powmod(r, mod - 2);
    //_debug("%lld", tot);
    LL cur1 = 1, cur2 = 1;
    for (int i = 0; i <= m; i++) {
        tot += mod - (cur1 + cur2) % mod * i % mod * fac % mod * factor[i] % mod;
        tot %= mod;
        cur1 = cur1 * l % mod * invr % mod;
        cur2 = cur2 * r % mod * invl % mod;
    }
    _debug("%d v. %d: %lld", (int)l, (int)r, tot);
    return tot;
}

void dfs2(int u, int p) {
    if (p != 0) {
        _debug("%d sz=%d, wt=%d", u, sz[u], wt[u]);
        ans += compute(sz[u], n - sz[u]) * wt[u];
        ans %= mod;
    }
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs2(v, u);
    }
}

void dfs(int u, int p, int d) {
    depth[u] = d;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
        sz[u] += sz[v];
    }
}

int main() {
    cin >> n >> m;
    init();
    vector<tuple<int, int, int>> edges;
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.emplace_back(u, v, w);
    }
    dfs(1, 0, 0);
    for (auto& p : edges) {
        int u, v, w; tie(u, v, w) = p;
        if (depth[u] < depth[v]) swap(u, v);
        wt[u] = w;
    }
    dfs2(1, 0);
    cout << ans << endl;
    return 0;
}


/*
5 2
4 5 9805
3 4 2001
2 3 6438
1 3 3790
 */
