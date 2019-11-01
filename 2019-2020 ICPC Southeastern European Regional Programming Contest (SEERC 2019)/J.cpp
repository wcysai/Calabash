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
LL adj[1024][1024];

int main() {
    scanf("%d", &n);
    Rep (i, n * (n - 1) / 2) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        adj[u][v] = adj[v][u] = w;
    }
    LL ans = 0;
    Rep (i, n) {
        vector<LL> val;
        Rep (j, n) if (i != j) val.push_back(adj[i][j]);
        sort(range(val));
        for (int i = 0; i < val.size(); i += 2) ans += val[i+1];
    }
    cout << ans << endl;
    return 0;
}
