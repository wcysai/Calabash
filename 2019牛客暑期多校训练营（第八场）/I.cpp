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

const int MAXN = 300005;
vector<int> adj[MAXN];
int sz[MAXN], top[MAXN], fa[MAXN], son[MAXN], depth[MAXN], id[MAXN];

void dfs1(int x, int dep, int par){
    depth[x] = dep;
    sz[x] = 1;
    fa[x] = par;
    int maxn = 0, s = 0;
    for (int c: adj[x]){
        if (c == par) continue;
        dfs1(c, dep + 1, x);
        sz[x] += sz[c];
        if (sz[c] > maxn){
            maxn = sz[c];
            s = c;
        }
    }
    son[x] = s;
}

int cid = 0;
void dfs2(int x, int t){
    top[x] = t;
    id[x] = ++cid;
    if (son[x]) dfs2(son[x], t);
    for (int c: adj[x]){
        if (c == fa[x]) continue;
        if (c == son[x]) continue;
        else dfs2(c, c);
    }
}

void decomp(int root){
    dfs1(root, 1, 0);
    dfs2(root, root);
}

struct bit_rupq{ // range update, point query
    int N;
    vector<LL> tr;

    void init(int n) { tr.resize(N = n + 5); }

    LL query(int n){
        LL ans = 0;
        while (n < N) { ans += tr[n]; n += n & -n; }
        return ans;
    }

    void add(int n, LL x){
        if (n == 0) return;
        while (n) { tr[n] += x; n &= n - 1; }
    }

    void add(int l, int r, LL x) {
        add(l - 1, -x); add(r, x);
    }
} base, incr;

LL query(int u, int t) {
    LL ans = 0;
    return incr.query(id[u]) * t + base.query(id[u]);
}

void modify(int u, int t, LL d) {
    while (u) {
        assert(id[top[u]] <= id[u]);
        base.add(id[top[u]], id[u], -d * t);
        incr.add(id[top[u]], id[u], d);
        u = fa[top[u]];
    }
}

vector<int> vin[300005], vout[300005];
        //  vertex qid
vector<pair<int, int>> qin[300005], qout[300005];
LL ans[300005];

int main() {
    int n, m, q; scanf("%d%d", &n, &m);
    base.init(m); incr.init(m);
    rep (i, m) {
        int u, v, l, r; scanf("%d%d%d%d", &u, &v, &l, &r);
        adj[u].push_back(v);
        adj[v].push_back(u);
        vin[l].push_back(v);
        vout[r].push_back(v);
    }
    scanf("%d", &q);
    rep (i, q) {
        int x, l, r; scanf("%d%d%d", &x, &l, &r);
        qin[l].emplace_back(x, i);
        qout[r].emplace_back(x, i);
        ans[i] = x == 1 ? r - l + 1 : 0;
    }
    decomp(1);
    Rep (i, n) {
        for (auto p : qin[i]) ans[p.second] -= query(p.first, i);
        for (int x : vin[i]) modify(x, i, 1);
        for (auto p : qout[i]) ans[p.second] += query(p.first, i + 1);
        for (int x : vout[i]) modify(x, i + 1, -1);
    }
    rep (i, q) printf("%lld\n", ans[i]);
}
