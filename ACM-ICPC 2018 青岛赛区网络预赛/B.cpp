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

const int MAXN = 100005;
vector<int> adj[MAXN];
int sz[MAXN], top[MAXN], fa[MAXN], son[MAXN], depth[MAXN], id[MAXN];
int isred[MAXN], upred[MAXN];
LL wt[MAXN], totl[MAXN];

void dfs1(int x, int dep, int par) {
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

int cid;
void dfs2(int x, int t) {
    top[x] = t;
    id[x] = ++cid;
    if (son[x]) dfs2(son[x], t);
    for (int c: adj[x]){
        if (c == fa[x]) continue;
        if (c == son[x]) continue;
        else dfs2(c, c);
    }
}

void dfs3(int u, int p, int r, LL len) {
    upred[u] = r;
    totl[u] = len;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (isred[v]) dfs3(v, u, v, 0);
        else dfs3(v, u, r, len + wt[v]);
    }
}

void decomp(int root){
    dfs1(root, 1, 0);
    dfs2(root, root);
}

int query_lca(int u, int v) {
    while (top[u] != top[v]){
        if (depth[top[u]] < depth[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    return u;
}

void cleanup(int n) {
    Rep (i, n) {
        adj[i].clear();
        isred[i] = 0;
    }
    cid = 0;
}

/*
int build_vtree(const vector<int> &a) {
    sort(a.begin(), a.end(), [] (int a, int b) { return id[a] < id[b]; });
    assert(a.size() > 0);
    int t = 0;
    vector<int> st;
    for(int v : a) {
        if (st.empty()) {
            st.push_back(x);
            continue;
        }
        int l = query_lca(b, st.back());
        while (st.size() > 1 && id[st.rbegin()[2]] >= id[l]) {
            int x = st.back(); st.pop_back();
            add_edge(x, st.back());
        }
        if(l != st.back()) {
            add_edge(l, st.back());
            st.back() = l;
        }
        st.push_back(a[i]);
    }
    while (st.size() > 2) {
        int x = st.back(); st.pop_back();
        add_edge(x, st.back());
    }
    return st[0];
}
*/

LL work(const vector<int>& vs) {
    if (vs.size() == 0) return 0;
    LL maxl = 0, ans = 0;
    int vb, vred;
    for (int v : vs) {
        if (totl[v] > maxl) {
            maxl = totl[v];
            vb = v;
        }
    }
    vred = upred[vb];

    map<int, LL> mp;
    map<int, int> mpv;

    for (int v : vs) {
        int vpos = query_lca(v, vb);
        if (upred[v] != vred /* || depth[vpos] <= depth[vred]*/) {
            ans = max(ans, totl[v]);
        } else {
            mp[depth[vpos]] = max(mp[depth[vpos]], totl[v]);
            mpv[depth[vpos]] = vpos;
        }
    }
    int cnt = mp.size();
    vector<LL> upmax, downmax;
    vector<int> deps;
    upmax.push_back(0);
    for (auto& p : mp) {
        upmax.push_back(p.second);
        downmax.push_back(p.second);
        deps.push_back(p.first);
    }
    for (int i = 1; i <= cnt; i++) {
        upmax[i] = max(upmax[i], upmax[i-1]);
    }
    for (int i = cnt - 1; i ; i--) {
        downmax[i-1] = max(downmax[i-1], downmax[i]);
    }
    LL best = LLONG_MAX;
    for (int i = 0; i < cnt; i++) {
        best = min(best, max(upmax[i], downmax[i] - totl[mpv[deps[i]]]));
    }
    assert(best != LLONG_MAX);
    return max(best, ans);
}

int n, m, q;
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &q);

        rep (i, m) {
            int v; scanf("%d", &v);
            isred[v] = 1;
        }
        vector<tuple<int, int, int>> edges;
        for (int i = 1; i < n; i++) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            edges.emplace_back(u, v, w);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        decomp(1);
        for (auto& p : edges) {
            int u, v, w; tie(u, v, w) = p;
            if (depth[u] < depth[v]) swap(u, v);
            wt[u] = w;
        }
        dfs3(1, 0, 1, 0);

        while (q--) {
            int k; scanf("%d", &k);
            vector<int> vid;
            rep (i, k) {
                int x; scanf("%d", &x);
                if (isred[x]) continue;
                vid.push_back(x);
            }
            printf("%lld\n", work(vid));
        }

        cleanup(n);
    }
    return 0;
}
