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
const LL mod = 998244353;
LL p2[512000];

int n, m, ncyc;
vector<int> adj[300005];
int c[300005], dep[300005];
LL ans = 1;

void dfs(int u, int p, int d) {
    c[u] = 1; dep[u] = d;
    for (int v : adj[u]) if (v != p) {
        if (c[v] == 0) {
            dfs(v, u, d + 1);
        } else if (c[v] == 1) {
            int nd = dep[u] - dep[v] + 1;
            ans = ans * (p2[nd] - 1) % mod;
            ncyc += nd;
        }
    }
    c[u] = 2;
}

int main() {
    p2[0] = 1;
    Rep (i, 500005) p2[i] = p2[i-1] * 2 % mod;
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Rep (i, n) if (c[i] == 0) dfs(i, 0, 0);
    ans = ans * p2[m - ncyc] % mod;
    cout << ans << endl;
    return 0;
}
