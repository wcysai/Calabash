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
int n, c, q;
map<int, pair<int, int>> color;
int ccnt[MAXN], cnt[MAXN];

inline void leave(int c) { cnt[ccnt[c]]--; }
inline void enter(int c) { cnt[ccnt[c]]++; }

void erase_node(decltype(color)::iterator it) {
    int c = it->second.second;
    cnt[ccnt[c]]--; 
    ccnt[c] -= it->second.first - it->first;
    cnt[ccnt[c]]++;
    color.erase(it);
}

void insert_node(int l, int r, int c) {
    cnt[ccnt[c]]--;
    ccnt[c] += r - l;
    cnt[ccnt[c]]++;
    color[l] = make_pair(r, c);
}

void split(int x) {
    if (color.count(x) || x >= n) return;
    auto it = prev(color.upper_bound(x));
    int r = it->second.first;
    it->second.first = x;
    color[x] = make_pair(r, it->second.second);
}

void change(int l, int r, int c) {
    if (l == r) return;
    split(l); split(r);
    auto it1 = color.lower_bound(l), it2 = color.lower_bound(r);
    while (it1 != it2) erase_node(it1++);
    insert_node(l, r, c);
}

vector<int> adj[MAXN];
int sz[MAXN], top[MAXN], fa[MAXN], son[MAXN], depth[MAXN], id[MAXN];

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

int cid = 0;
void dfs2(int x, int t) {
    top[x] = t;
    id[x] = cid++;
    if (son[x]) dfs2(son[x], t);
    for (int c: adj[x]){
        if (c == fa[x]) continue;
        if (c == son[x]) continue;
        else dfs2(c, c);
    }
}

void decomp(int root) {
    dfs1(root, 1, 0);
    dfs2(root, root);
}

void query(int u, int c) {
    while (top[u] != 1) {
        change(id[top[u]], id[u] + 1, c);
        u = fa[top[u]];
    }
    change(1, id[u] + 1, c);
}

int main() {
    scanf("%d%d%d", &n, &c, &q);
    cnt[0] = c + 1;
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v); adj[v].push_back(u);
    }
    decomp(1); 
//    Rep (i, n) printf("%d, id=%d, top=%d\n", i, id[i], top[i]);
    insert_node(1, n, 0);
    while (q--) {
        int u, c, m; scanf("%d%d%d", &u, &c, &m);
        query(u, c);
    //    rep (i, ::c + 1) printf("cc[%d]=%d\n", i, ccnt[i]);
     //   rep (i, n + 1) printf("c[%d]=%d\n", i, cnt[i]);
        printf("%d\n", cnt[m] - (ccnt[0] == m));
    }
    return 0;
}
