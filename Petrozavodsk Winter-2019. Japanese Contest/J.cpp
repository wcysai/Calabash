#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> rkt;

const int MAXN = 100005, MAXM = 20;
int ans[MAXN], lca[MAXN], clr[MAXN];
int id[MAXN], iend[MAXN], fa[MAXN], dep[MAXN], jp[MAXN][MAXM];
rkt tr[MAXN];
set<int> sv[MAXN];

int cntrange(int c, int v) {
    return tr[c].order_of_key(iend[v]) - tr[c].order_of_key(id[v]);
}

int n;
vector<int> adj[MAXN];

int climb(int v, int c) {
    int ans = 0;
    if (cntrange(c, v)) return 0;
    for (int l = MAXM - 1; l >= 0; l--) {
        if (jp[v][l] == 0) continue;
        if (cntrange(c, jp[v][l]) == 0) {
            ans += (1 << l);
            v = jp[v][l];
        }
    }
    return ans + 1;
}

int getlca(int c) {
    int v = *(sv[c].begin());
    if (cntrange(c, v) == tr[c].size()) return v;
    for (int l = MAXM - 1; l >= 0; l--) { 
        if (jp[v][l] == 0) continue;
        if (cntrange(c, jp[v][l]) < tr[c].size()) {
            v = jp[v][l];
        }
    }
//    _debug("%d", v);
    return fa[v];
}

void enter(int v, int c) {
    clr[v] = c; 
    if (tr[c].empty()) {
        ans[c] = 0; lca[c] = v;
        tr[c].insert(id[v]); sv[c].insert(v);
    } else {
        ans[c] += climb(v, c);
        tr[c].insert(id[v]); sv[c].insert(v);
        int nlca = getlca(c);
        ans[c] += dep[lca[c]] - dep[nlca];
        lca[c] = nlca;
    }
//    _debug("%d %d %d", v, lca[c], ans[c]);
}

void leave(int v, int c) {
    if (tr[c].size() == 1) {
        tr[c].erase(id[v]); sv[c].erase(v);
    } else {
        tr[c].erase(id[v]); sv[c].erase(v);
        ans[c] -= climb(v, c);
        int nlca = getlca(c);
        ans[c] -= dep[nlca] - dep[lca[c]];
        lca[c] = nlca; 
    }
//    _debug("%d %d %d", v, lca[c], ans[c]);
}

int dfs_no = 0;
void dfs(int u, int father, int depth) {
    fa[u] = father; dep[u] = depth; id[u] = dfs_no++;
    for (int v : adj[u]) if (v != father) dfs(v, u, depth + 1);
    iend[u] = dfs_no;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v); adj[v].push_back(u);
    }
    dfs(1, 0, 1);
    Rep (i, n) jp[i][0] = fa[i];
    for (int l = 1; l < MAXM; l++) Rep (i, n) jp[i][l] = jp[jp[i][l-1]][l-1];
    Rep (i, n) {
        int c; scanf("%d", &c);
        enter(i, c);
    }
    int q; scanf("%d", &q);
    while (q--) {
        char op[4]; scanf("%s", op);
        if (op[0] == 'Q') {
            int c; scanf("%d\n", &c);
            printf("%d\n", tr[c].empty() ? -1 : ans[c]);
        } else {
            int u, c; scanf("%d%d", &u, &c);
            leave(u, clr[u]); enter(u, c);
        }
    }
    return 0;
}
