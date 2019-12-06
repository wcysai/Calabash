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
int val[500005];
vector<int> adj[500005];
 
bool check(int u) {
    if (val[u]) return false;
    for (int v : adj[u]) 
        if (val[v] != 1) return false;
    return true;
}
 
int main() {
    scanf("%d%d", &n, &m);
    Rep (i, n) scanf("%d", val + i);
    rep (_, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Rep (i, n) if (check(i)) return printf("%d\n", i), 0;
    return 0;
}