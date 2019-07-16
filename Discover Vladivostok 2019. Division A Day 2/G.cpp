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

typedef unsigned short us;

const int NUM = 800;
int n;
int x[51200], y[51200];

vector<tuple<int, int, int>> edges;
void add_edge(int u, int v) {
    int dx = x[u] - x[v], dy = y[u] - y[v];
    edges.emplace_back(dx*dx + dy*dy, u, v);
}

int fa[51200];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool unite(int u, int v) {
    u = find(u); v = find(v);
    fa[u] = v;
    return u != v;
}

int main() {
    scanf("%d", &n);
    Rep (i, n) scanf("%d%d", x+i, y+i);
    vector<pair<int, int>> v;
    set<pair<int, int>> s;
    Rep (i, n) v.emplace_back(y[i], i);
    sort(range(v));
    int thresh = 30000000 / n;
    for (int i = 0; i < n; i++) {
        int ii = v[i].second;
        for (int j = max(i - NUM, 0); j < i; j++) {
            int jj = v[j].second;
            if (abs(x[ii] - x[jj]) <= thresh) 
                add_edge(ii, jj);
        }
    }
    iota(fa, fa + n + 1, 0);
    sort(range(edges));
    vector<pair<int, int>> ed;
    long double ans = 0;
    for (auto e : edges) {
        int w, u, v; tie(w, u, v) = e;
        if (unite(u, v)) {
            ans += sqrt((long double)w);
            ed.emplace_back(u, v);
        }
    }
    assert(ed.size() == n - 1);
    printf("%.20Lf\n", ans);
    for (auto e : ed) {
        int u, v; tie(u, v) = e;
        printf("%d %d\n", u, v);
    }
    return 0;
}
