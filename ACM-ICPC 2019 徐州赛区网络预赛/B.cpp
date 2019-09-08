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

int n, q;
vector<int> xs;
int fa[1 << 21];
bool del[1 << 21];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void unite(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return;
    if (u < v) swap(u, v);
    fa[v] = u;
}

int main() {
    scanf("%d%d", &n, &q);
    vector<pair<int, int>> ops;
    rep (_, q) {
        int z, x; scanf("%d%d", &z, &x);
        ops.emplace_back(z, x);
        xs.push_back(x);
        xs.push_back(x + 1);
    }
    sort(range(xs)); xs.erase(unique(range(xs)), xs.end());
    iota(range(fa), 0);
    for (auto p : ops) {
        int z, x; tie(z, x) = p;
        x = lower_bound(range(xs), x) - xs.begin();
        if (z == 1) {
            if (del[x]) continue;
            del[x] = true;
            unite(x, x + 1);
        } else {
            int ans = xs[find(x)];
            if (ans > n) ans = -1;
            printf("%d\n", ans);
        }
    }
    return 0;
}
