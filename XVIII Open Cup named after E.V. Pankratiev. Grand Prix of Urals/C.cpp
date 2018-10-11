#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debug(...) ((void) 0)
#endif

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

const int BLOCKSZ = 800;
int n, k, q;

int bigcnt = 0;
int big[200005];
int deg[200005];
int color[200005];
bool cur[200005];

// bool bigconn[400][262144];
int bignei[400];

vector<pair<int, int>> badj[200005];
vector<pair<int, int>> sadj[200005];
int sadjsz[200005];
int sscnt, bscnt, bbcnt;

inline void add_edge(int u, int v, int w) {
    if (big[v]) badj[u].push_back({v, w});
    else {
        sadj[u].push_back({v, w});
        sadjsz[u] += w;
    }
}

int main() {
    scanf("%d%d%d", &n, &k, &q);
    rep (i, n) scanf("%d", color + i);
    map<pair<int, int>, int> edges;
    for (int i = 1; i < n; i++) {
        if (color[i] == color[i-1]) continue;
        int u = color[i], v = color[i-1];
        if (u > v) swap(u, v);
        edges[{u, v}]++;
    }

    for (auto& e : edges) {
        int u, v; tie(u, v) = e.first;
        deg[u]++; deg[v]++;
    }

    Rep (i, k) {
        _debug("deg[%d]=%d", i, deg[i]);
        if (deg[i] > BLOCKSZ) big[i] = ++bigcnt;
    }

    for (auto p : edges) {
        int u, v, w;
        tie(u, v) = p.first; w = p.second;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    rep (i, q) {
        int u; scanf("%d", &u);
        if (big[u] == 0) { // small
            for (auto p : sadj[u]) {
                int v, w; tie(v, w) = p;
                if (cur[u] == cur[v]) sscnt += w; else sscnt -= w;
            }
            for (auto p : badj[u]) {
                int v, w; tie(v, w) = p;
                if (cur[u] == cur[v]) bscnt += w; else bscnt -= w;
                if (!cur[u]) bignei[big[v]] += w; else bignei[big[v]] -= w;
            }
        } else {    // big
            if (cur[u]) {
                bscnt += bignei[big[u]];
                bscnt -= sadjsz[u] - bignei[big[u]];
            } else {
                bscnt -= bignei[big[u]];
                bscnt += sadjsz[u] - bignei[big[u]];
            }
            for (auto p : badj[u]) {
                int v, w; tie(v, w) = p;
                if (cur[u] == cur[v]) sscnt += w;
                else sscnt -= w;
            }
        }
        cur[u] = !cur[u];
        printf("%d\n", (bscnt + sscnt + bbcnt + 1 + cur[color[0]]) / 2);
    }
    return 0;
}

/*
3 2 5
1 2 1
1
2
1
2
2
 */
