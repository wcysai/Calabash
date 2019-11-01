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
vector<int> adj[100005];

int dfs(int u, int p) {
    int cur = 0;
    for (int v : adj[u]) if (v != p) cur += dfs(v, u);
    return abs(cur - 1);
}

int main() {
    scanf("%d", &n);
    rep (i, n - 1) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (dfs(1, 0)) {
        puts("Alice");
    } else {
        puts("Bob");
    }
    return 0;
}
