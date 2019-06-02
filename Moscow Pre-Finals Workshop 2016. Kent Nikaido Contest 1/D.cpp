#pragma GCC optimize(3)
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

const LL mod = 1000000007;

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

int n, m;
int deg[500005];
int u[500005], v[500005];
int fa[500005];
vector<pair<int, int>> adj[500005];
LL ans;

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

bool unite(int u, int v) {
    u = find(u); v = find(v);
    fa[u] = v;
    return u != v;
}

bool dfs(int u, int fa, int fe) {
    bool tot = deg[u] & 1;
    for (auto& ev : adj[u]) {
        int v, eid; tie(v, eid) = ev;
        if (v == fa) continue;
        tot ^= dfs(v, u, eid);
    }
    if (tot) ans += powmod(2, fe);
    return tot;
}

int main() {
    scanf("%d%d", &n, &m);
    ans = powmod(2, m) - 1;
    rep (i, m) {
        scanf("%d%d", u + i, v + i);
        deg[u[i]]++;
        deg[v[i]]++;
    }
    iota(fa, fa + n + 1, 0);
    rep (i, m) if (unite(u[i], v[i])) {
        adj[u[i]].emplace_back(v[i], i);   
        adj[v[i]].emplace_back(u[i], i);   
    }
    dfs(1, 0, 0);
    cout << (ans * 2 % mod) << endl; 
    return 0;

}
