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

int n, m, a, b;
vector<pair<int, int>> edges;
bool aa[100005], ab[100005];
vector<int> adj[100005];
vector<int> saa[100005], sab[100005];

bool check(int u, int v) {
    if (min(saa[u].size(), sab[v].size()) > 2) return true;
    if (saa[u].size() < sab[v].size()) {
        for (int x : saa[u]) if (x != v)
            for (int y : sab[v]) if (y != u)
                if (x != y) return true;
    } else {
        for (int y : sab[v]) if (y != u)
            for (int x : saa[u]) if (x != v)
                if (x != y) return true;
    }
    return false;
}

bool check(int num) {
    Rep (i, n) {
        adj[i].clear();
        saa[i].clear();
        sab[i].clear();
    }
    memset(aa, 0, sizeof aa);
    memset(ab, 0, sizeof ab);
    rep (i, num) {
        int u, v; tie(u, v) = edges[i];
        if ((u == a and v == b) or (u == b and v == a)) continue;
        if (u == a) aa[v] = true;
        if (v == a) aa[u] = true;
        if (u == b) ab[v] = true;
        if (v == b) ab[u] = true;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Rep (i, n) {
        if (i == a or i == b) continue;
        for (int u : adj[i]) if (u != a and u != b) {
            if (aa[u]) saa[i].push_back(u);
            if (ab[u]) sab[i].push_back(u);
        }
    }
    rep (i, num) {
        int u, v; tie(u, v) = edges[i];
        if (u == a or u == b or v == a or v == b) continue;
        if (check(u, v)) return true;
        if (check(v, u)) return true;
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        edges.emplace_back(u, v);
    }
    scanf("%d%d", &a, &b);
    if (!check(m)) {
        cout << -1 << endl;
        return 0;
    }
    int l = 0, r = m;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << endl;
    return 0;
}
