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

struct edge {
    int u, v, w;
};

namespace ChuLiu {
    const int MAXN = 64;

    int in[MAXN];
    int pre[MAXN], vis[MAXN], id[MAXN];

    int getans(int n, int rt, vector<edge> &edges) {
        int ans = 0;
        int cnt = 0;
        while (true) {
            Rep (i, n) in[i] = INT_MAX, id[i] = vis[i] = 0;
            for (auto e : edges) {
                if (e.u != e.v and e.w < in[e.v]) {
                    pre[e.v] = e.u;
                    in[e.v] = e.w;
                }
            }
            in[rt] = 0;
            Rep (i, n) {
                if (in[i] == INT_MAX) return -1;
                ans += in[i];
                int u;
                for (u = i; u != rt && vis[u] != i && !id[u]; u = pre[u])
                    vis[u] = i;
                if (u != rt && !id[u]) {
                    id[u] = ++cnt;
                    for (int v = pre[u]; v != u; v = pre[v])
                        id[v] = cnt;
                }
            }
            if (!cnt) return ans;
            Rep (i, n) if (!id[i]) id[i] = ++cnt;
            for (auto &e : edges) {
                LL laz = in[e.v];
                e.u = id[e.u];
                e.v = id[e.v];
                if (e.u != e.v) e.w -= laz;
            }
            n = cnt;
            rt = id[rt];
            cnt = 0;
        }
    }
}

int n;
int a[64], b[64];
int g[64][64], gg[64][64];

int get_ans_by_prefix(vector<int> prefix) {
    int ord[64] = {0};
    memset(gg, -1, sizeof gg);
    rep (i, prefix.size()) ord[prefix[i]] = i + 1;
    vector<edge> edges;
    Rep (i, n) Rep (j, n) {
        if (i == j) {
            edges.push_back({n + 1, i, g[i][i]});
            gg[n+1][i] = g[i][i];
            continue;
        }
        if (ord[i] and ord[j] and ord[i] > ord[j]) continue;
        if (!ord[i] and ord[j]) continue;
        edges.push_back({i, j, g[i][j]});
        gg[i][j] = g[i][j];
    }
    /*
    Rep (i, n + 1) {
        Rep (j, n + 1) fprintf(stderr, "%d ", gg[i][j]);
        fputc('\n', stderr);
    }
     */
    _debug("sz=%d", (int)edges.size());
    return ChuLiu::getans(n + 1, n + 1, edges);
}

int main() {
    scanf("%d", &n);
    Rep (i, n) scanf("%d", a + i);
    Rep (i, n) scanf("%d", b + i);
    Rep (i, n) Rep (j, n) g[i][j] = b[i] ^ a[j];
    /*
    Rep (i, n) {
        Rep (j, n) printf("%d ", g[i][j]);
        puts("");
    }
     */
    const int val = get_ans_by_prefix({});
    printf("%d\n", val);
    vector<int> pref;
    set<int> rem;
    Rep (i, n) rem.insert(i);
    Rep (pn, n) {
        _debug("pn=%d", pn);
        pref.push_back(0);
        for (int x : rem) {
            pref.back() = x;
            if (get_ans_by_prefix(pref) == val) {
                _debug("append %d", x);
                // rem.erase(x);
                break;
            }
        }
        rem.erase(pref.back());
    }
    for (int x : pref) printf("%d ", x);
    return 0;
}
/*
 3
 1 2 3
 3 2 1
 */

/*
4
1432 23849 123 3412
123 13214 234 1411
 */
