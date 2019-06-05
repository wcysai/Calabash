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
multiset<int> adj[300005];
vector<pair<int, int>> edges;
vector<int> ans;
int fa[1 << 18];

int find(int x) {
    return fa[x] == x ? x :  fa[x] = find(fa[x]);
}

bool unite(int u, int v) {
    u = find(u); v = find(v);
    fa[u] = v;
    return u != v;
}

void test(int x) {
    iota(fa, fa + n + 1, 0);
    for (auto p : edges) {
        if (p.first == x or p.second == x) continue;
        if (!unite(p.first, p.second)) return;
    }
    ans.push_back(x);
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].insert(v);
        adj[v].insert(u);
        edges.emplace_back(u, v);
    }
    int maxd = 0;
    Rep (i, n) {
        maxd = max(maxd, (int)adj[i].size());
        if (adj[i].size() & 1) {
            puts("0");
            return 0;
        }
    }
    if (maxd == 2) {
        printf("%d\n", n);
        Rep (i, n) printf("%d ", i);
        return 0;
    }
    Rep (i, n) if (adj[i].size() == maxd) test(i);
    cout << ans.size() << endl;
    for (int x : ans) cout << x << ' ';
    return 0;
}
