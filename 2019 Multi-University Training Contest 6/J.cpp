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

const int mod = 1000000007;

int n, m;
vector<int> adj[2048];
map<int, int> cnt[2048];
int w[2048];
LL ans;

void addmod(int& x, LL y) {
    x = (x + y) % mod;
}

void dfs(int u, int p) {
    map<int, int> cur;
    cnt[u][w[u]] = 1;
    for (int v : adj[u]) if (v != p) {
        dfs(v, u);
        cur = cnt[u];
        for (const auto& p : cnt[v]) {
            for (const auto& q : cnt[u]) {
                if (1ll * p.first * q.first > m) break;
                addmod(cur[p.first * q.first], 1ll * p.second * q.second);
            }
        }
        cnt[u] = move(cur);
    }
    for (const auto& p : cnt[u]) ans += p.second;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        Rep (i, n) adj[i].clear(), cnt[i].clear();
        Rep (i, n) scanf("%d", w + i);
        for (int i = 1; i < n; i++) {
            int u, v; scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        ans = 0;
        dfs(1, 0);
        printf("%lld\n", ans % mod);
    }
    return 0;
}
