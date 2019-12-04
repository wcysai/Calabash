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

const int mod = 1'000'000'007;

inline int add(int x, int y) {
    x += y; if (x >= mod) x -= mod;
    return x;
}

inline int Add(int& x, int y) { return x = add(x, y); }

inline int sub(int x, int y) {
    x -= y; if (x < 0) x += mod;
    return x;
}

inline int Sub(int& x, int y) { return x = sub(x, y); }

inline int mul(int x, int y) { return 1ll * x * y % mod; }

inline int mul(int x) { return mul(x, x); }

struct bit_purq {
    int N;
    vector<int> tr;

    void init(int n) { tr.assign(N = n + 5, 0); }

    int sum(int n) {
        int ans = 0;
        while (n) { Add(ans, tr[n]); n &= n - 1; }
        return ans;
    }

    int sum(int l, int r) { return sub(sum(r), sum(l-1)); }

    void add(int n, int x) {
        while (n < N) { Add(tr[n], x); n += n & -n; }
    }
};

struct bit_rupq {
    int N;
    vector<int> tr;

    void init(int n) { tr.assign(N = n + 5, 0); }

    int query(int n) {
        if (n == 0) return 0;
        int ans = 0;
        while (n < N) { Add(ans, tr[n]); n += n & -n; }
        return ans;
    }

    void add(int n, int x) {
        while (n) { Add(tr[n], x); n &= n - 1; }
    }

    void add(int l, int r, int x) {
        add(r, x); add(l - 1, sub(0, x));
    }
};

const int MAXN = 100005;
int n, totw, wt[MAXN];
vector<int> adj[MAXN];
int sz[MAXN], top[MAXN], fa[MAXN], son[MAXN], depth[MAXN], id[MAXN], idx;

void dfs1(int x, int dep, int par) {
    depth[x] = dep;
    sz[x] = 1;
    fa[x] = par;
    int maxn = 0, s = 0;
    for (int c : adj[x]) if (c != par) {
        dfs1(c, dep + 1, x);
        sz[x] += sz[c];
        if (sz[c] > maxn) {
            maxn = sz[c];
            s = c;
        }
    }
    son[x] = s;
}

void dfs2(int x, int t) {
    top[x] = t;
    id[x] = ++idx;
    if (son[x]) dfs2(son[x], t);
    for (int c : adj[x]) {
        if (c == fa[x]) continue;
        if (c == son[x]) continue;
        dfs2(c, c);
    }
}

void decomp(int root) {
    idx = 0;
    dfs1(root, 1, 0);
    dfs2(root, root);
}

bit_rupq sw;        // query(l), add([l, r], x)
bit_purq lcs2;      // sum([l, r]), add(l, x)

void update(int u, int dx) {
    _debug("%d: %d", u, dx);
    while (u) {
        if (fa[top[u]]) lcs2.add(id[fa[top[u]]], sub(0, mul(sw.query(id[top[u]]))));
        sw.add(id[top[u]], id[u], dx);
        if (fa[top[u]]) lcs2.add(id[fa[top[u]]], mul(sw.query(id[top[u]])));
        u = fa[top[u]];
    }
}

int query_point(int u) {
    int ans = mul(totw);
    Sub(ans, lcs2.sum(id[u], id[u]));
    Sub(ans, mul(sw.query(id[son[u]])));
    Sub(ans, mul(totw - sw.query(id[u])));
    _debug("%d: totw=%d, lcs2=%d, sws=%d, sw=%d", u, totw, lcs2.sum(id[u], id[u]),
        sw.query(id[son[u]]), sw.query(id[u]));
    _debug("%d: %d", u, ans);
    return ans;
}

int query_interval(int u, int v) {
    int ans = sub(mul(sw.query(id[u])), mul(sw.query(id[son[v]])));
    Sub(ans, lcs2.sum(id[u], id[v]));
    _debug("%d %d: %d", u, v, ans);
    return ans;
}

int query(int u, int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        Add(ans, query_interval(top[u], u));
        u = fa[top[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) Add(ans, query_interval(son[u], v));
    Add(ans, query_point(u));
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int m; scanf("%d%d", &n, &m);
        sw.init(n); lcs2.init(n);
        Rep (i, n) adj[i].clear();
        Rep (i, n) scanf("%d", wt + i);
        totw = accumulate(wt + 1, wt + n + 1, 0ll) % mod;
        for (int i = 1; i < n; i++) {
            int u, v; scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        decomp(1);
        Rep (i, n) update(i, wt[i]);
        while (m--) {
            int op, x, y; scanf("%d%d%d", &op, &x, &y);
            if (op == 1) {
                int delta = sub(y, wt[x]);
                update(x, delta);
                Add(totw, delta);
                wt[x] = y;
            } else if (op == 2) {
                printf("%d\n", query(x, y));
            } else assert(0);
        }
    }
    return 0;
}
