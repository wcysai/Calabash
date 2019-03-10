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

const int MAXN = 100005;
int n, k, s, m, q;
int epoch = 0;
int ans[MAXN];

vector<pair<int, int>> next_unite;

struct UFS {
    vector<pair<int, int>> queries[MAXN];
    int fa[MAXN];

    void init(int n) { Rep (i, n) fa[i] = i; }

    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    void unite(int x, int y) {
        x = find(x); y = find(y); if (x == y) return;
        if (max(x, y) <= k) 
            for (int i = 1; i <= s; i++) 
                next_unite.emplace_back(x + i * k, y + i * k);
        if (queries[x].size() > queries[y].size()) swap(x, y);
        // queries[x].size() <= queries[y].size())
        for (auto q : queries[x]) {
            int to, id; tie(to, id) = q;
            to = find(to);
            if (to == x) continue;
            else if (to == y) ans[id] = epoch; 
            else queries[y].push_back(q);
        }
        if (x < y) { swap(x, y); swap(queries[x], queries[y]); }  // x > y, merge x to y
        fa[x] = y;
    }
} ufs;

int main() {
    scanf("%d%d%d%d", &n, &k, &s, &m);
    ufs.init(n);
    rep (_, m) {
        int u, v; scanf("%d%d", &u, &v);
        next_unite.emplace_back(u, v);
    }
    scanf("%d", &q);
    Rep (i, q) {
        int s, t; scanf("%d%d", &s, &t);
        ufs.queries[s].emplace_back(t, i);
        ufs.queries[t].emplace_back(s, i);
        ans[i] = -1;
    }
    while (next_unite.size()) {
        vector<pair<int, int>> to_unite(move(next_unite));
        for (auto p : to_unite) ufs.unite(p.first, p.second);
        epoch++;
    }
    Rep (i, q) printf("%d\n", ans[i]);
    return 0;
}
