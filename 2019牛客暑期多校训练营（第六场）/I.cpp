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

const LL mod = 998244353;
LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

const int MAXN = 100005;
struct graph {
    int n;
    int pre[MAXN], iscut[MAXN], bccno[MAXN], dfs_clock, bcc_cnt;
    vector<int> adj[MAXN], bcc[MAXN];
    set<pair<int, int>> bcce[MAXN];

    stack<pair<int, int>> s;

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int u, int fa) {
        int lowu = pre[u] = ++dfs_clock;
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
                        bcce[bcc_cnt].insert(minmax(xu, xv));
                        if (bccno[xu] != bcc_cnt) {
                            bcc[bcc_cnt].push_back(xu);
                            bccno[xu] = bcc_cnt;
                        }
                        if (bccno[xv] != bcc_cnt) {
                            bcc[bcc_cnt].push_back(xv);
                            bccno[xv] = bcc_cnt;
                        }
                        if (xu == u && xv == v) break;
                    }
                    bcc_cnt++;
                }
            } else if (pre[v] < pre[u] && v != fa) {
                s.push({u, v});
                lowu = min(lowu, pre[v]);
            }
        }
        if (fa < 0 && child == 1) iscut[u] = 0;
        return lowu;
    }

    void init(int n) {
        this->n = n;
        memset(pre, 0, sizeof pre);
        memset(iscut, 0, sizeof iscut);
        memset(bccno, -1, sizeof bccno);
        dfs_clock = bcc_cnt = 0;
        rep (i, n) {
            adj[i].clear();
            bcc[i].clear();
            bcce[i].clear();
        }
    }

    void find_bcc() { rep (i, n) if (!pre[i]) dfs(i, -1); }
} g;

int n, nb;
map<int, LL> wt[100005];
vector<pair<int, int>> assoc[100005];
vector<int> block[100005];
vector<int> adj[100005];

LL dp(int bid, int off) {
    auto& blk = block[bid];
    int sz = blk.size();
    rotate(blk.begin(), blk.begin() + off, blk.end());
    vector<LL> p(sz);

    if (sz > 2) {
        vector<LL> lsucc(sz), rsucc(sz);
        lsucc[0] = rsucc[0] = 1;
        for (int i = 1; i < sz; i++)
            lsucc[i] = lsucc[i-1] * wt[blk[i-1]][blk[i]] % mod;
        for (int i = sz - 1; i; i--) {
            int j = (i + 1) % sz;
            rsucc[i] = rsucc[j] * wt[blk[i]][blk[j]] % mod;
        }
        for (int i = 1; i < sz; i++) {
            p[i] = 1 - (1 - lsucc[i]) * (1 - rsucc[i]) % mod;
            p[i] = (p[i] % mod + mod) % mod;
        }
    } else {
        p[1] = wt[blk[0]][blk[1]];
    }
    LL ret = 0;
    for (int i = 1; i < sz; i++) {
        ret += p[i];
        for (auto pp : assoc[blk[i]]) if (pp.first != bid)
            ret += p[i] * dp(pp.first, pp.second);
        ret %= mod;
    }
    return ret;
}

int main() {
    int T; scanf("%d", &T);
    Rep (t, T) {
        int m; scanf("%d%d", &n, &m);
        rep (i, n) adj[i].clear(), assoc[i].clear(), wt[i].clear();
        g.init(n);
        for (int i = 0; i < m; i++) {
            int u, v, a, b; scanf("%d%d%d%d", &u, &v, &a, &b);
            u--; v--;
            wt[u][v] = wt[v][u] = a * powmod(b, mod - 2) % mod;
            g.add_edge(u, v);
        }

        g.find_bcc();
        nb = g.bcc_cnt;
        rep (i, nb) block[i].clear();

        for (int i = 0; i < nb; i++) {
            for (auto p : g.bcce[i]) {
                adj[p.first].push_back(p.second);
                adj[p.second].push_back(p.first);
            }

            if (g.bcce[i].size() > 1) {
                int u = g.bcce[i].begin()->first, last = -1, init = u;
                block[i].push_back(u);
                do {
                    for (int v : adj[u]) if (v != last) {
                        last = u;
                        u = v;
                        block[i].push_back(u);
                        break;
                    }
                } while (u != init);
                block[i].pop_back();
            } else {
                block[i].push_back(g.bcce[i].begin()->first);
                block[i].push_back(g.bcce[i].begin()->second);
            }

            for (int j = 0; j < block[i].size(); j++)
                assoc[block[i][j]].emplace_back(i, j);

            for (auto p : g.bcce[i]) {
                adj[p.first].clear();
                adj[p.second].clear();
            }
        }
        LL ans = 1;
        for (auto as : assoc[0]) ans += dp(as.first, as.second);
        printf("Case #%d: %lld\n", t, ans % mod);
    }
    return 0;
}
