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
const int MAXN = 200005;

vector<int> adj[MAXN];
int c[MAXN];
LL cnt[4];

void bipartite(int u, int cc = 1) {
    if (c[u]) {
        if (c[u] != cc) throw 0;
        return;
    }
    c[u] = cc; cnt[cc] ++;
    for (int v : adj[u]) bipartite(v, 3 - cc);
}

struct graph {
    int pre[MAXN], iscut[MAXN], bccno[MAXN], dfs_clock, bcc_cnt;
    vector<int> adj[MAXN], bcc[MAXN];
    set<pair<int, int>> bcce[MAXN];
    stack<pair<int, int>> s;

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int u, int fa) {
        int lowu = pre[u] = ++ dfs_clock;
        int child = 0;
        for (int v : adj[u]) {
            if (!pre[v]) {
                s.push({u, v});
                child++;
                int lowv = dfs(v, u);
                lowu = min(lowu, lowv);
                if (lowv >= pre[u]) {
                    iscut[u] = 1;
                    bcc[bcc_cnt].clear();
                    bcce[bcc_cnt].clear();
                    while (1) {
                        int xu, xv;
                        tie(xu, xv) = s.top(); s.pop();
                        bcce[bcc_cnt].insert({min(xu, xv), max(xu, xv)});
                        if (bccno[xu] != bcc_cnt) {
                            bcc[bcc_cnt].push_back(xu);
                            bccno[xu] = bcc_cnt;
                        }
                        if (bccno[xv] != bcc_cnt) {
                            bcc[bcc_cnt].push_back(xv);
                            bccno[xv] = bcc_cnt;
                        }
                        if (xu == u and xv == v)  break;
                    }
                    bcc_cnt++;
                }
            } else if (pre[v] < pre[u] and v != fa) {
                s.push({u, v});
                lowu = min(lowu, pre[v]);
            }
        }
        if (fa < 0 and child == 1) iscut[u] = 0;
        return lowu;
    }

    void find_bcc(int n) {
        memset(pre, 0, sizeof pre);
        memset(iscut, 0, sizeof iscut);
        memset(bccno, -1, sizeof bccno);
        dfs_clock = bcc_cnt = 0;
        Rep (i, n) if (!pre[i]) dfs(i, -1);
    }
    
    vector<pair<int, int>> work() {
        vector<pair<int, int>> ret;
        rep (i, bcc_cnt) {
            for (auto p : bcce[i]) {
                int u, v; tie(u, v) = p;
                ::adj[u].push_back(v);
                ::adj[v].push_back(u);
            }
            bool flag = true;
            try {
                bipartite(bcce[i].begin()->first);

            } catch(int x) {
                flag = false;
            }
            if (flag) for (auto p : bcce[i]) ret.push_back(p);

            for (auto p : bcce[i]) {
                int u, v; tie(u, v) = p;
                ::adj[u].clear(); c[u] = c[v] = 0;
               ::adj[v].clear();
            }
        }
        return ret;
    }
} bcc;

int main() {
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        bcc.add_edge(u, v);
    }
    bcc.find_bcc(n);
    for (auto p : bcc.work()) {
        int u, v; tie(u, v) = p;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    LL ans1 = 0, ans2 = 0;
    Rep (i, n) {
        if (c[i]) continue;
        memset(cnt, 0, sizeof cnt);
        bipartite(i);
        ans1 += cnt[1] * (cnt[1] - 1) / 2 + cnt[2] * (cnt[2] - 1) / 2;
        ans2 += cnt[1] * cnt[2];
    }
    cout << ans1 << ' ' << ans2 << endl;
    return 0;
}
