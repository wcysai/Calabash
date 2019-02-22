#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 300005;

int n, m, k;
int clr[MAXN];
vector<int> adj[MAXN];
set<int> ac[MAXN];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    Rep (i, n) scanf("%d", clr + i);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Rep (u, n) 
        for (int v : adj[u]) ac[u].insert(clr[v]);
    bool flag = false;
//    Rep (i, n) printf("%d %d\n", i, int(ac[i].size()));
    Rep (i, n) 
        if (ac[i].size() + 1 < k) flag = true;
    printf("%d\n", flag);
    
    return 0;
}
