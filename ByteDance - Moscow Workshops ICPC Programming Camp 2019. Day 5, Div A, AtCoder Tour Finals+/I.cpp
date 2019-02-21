#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 200005;

struct twoSAT {
    int n;
    vector<int> G[MAXN * 2];

    bool mark[MAXN * 2];
    int S[MAXN*2],c;

    void init(int n){
        this->n = n;
        for (int i=0;i<n*2;i++) G[i].clear();
        memset(mark,0,n * 2 + 3);
    }

    int dfs(int x){
        if (mark[x^1]) return false;
        if (mark[x])return true;
        mark[x] = 1;
        S[c++] = x;
        for (int i=0;i<G[x].size();i++){
            if (!dfs(G[x][i]))return false;
        }
        return true;
    }

    void add_clause(int x,bool xval,int y,bool yval){
//        _debug("%d:%d, %d:%d\n", x, xval, y, yval);
        x = x * 2 + xval;
        y = y * 2 + yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }

    bool solve(){
        for (int i=0;i<n*2;i+=2){
            if (!mark[i] && !mark[i+1]){
                c = 0;
                if (!dfs(i)){
                    while (c>0) mark[S[--c]] = false;
                    if (!dfs(i+1))return false;
                }
            }
        }
        return true;
    }
} sat;

int n, m;
bool ok[200005];
vector<int> adj[200005];
pair<int, int> cond[200005];
vector<pair<int, int>> conds;

void getconds(int u) {
    if (adj[u].size() == 1) {
        conds.push_back(cond[u]);
    } else {
        assert(adj[u].size() > 1);
        rep (i, 2) getconds(adj[u][i]);
    }
}

bool solvetr(int rt) {
    conds.clear();  getconds(rt);
    vector<int> vars;
    auto disc = [&] (int x) { 
        return lower_bound(range(vars), x) - vars.begin(); 
    };
    for (auto p : conds) { 
        vars.push_back(abs(p.first));
        vars.push_back(abs(p.second));
    }
    sort(range(vars));
    vars.erase(unique(range(vars)), vars.end());
    sat.init(vars.size());
    for (auto p : conds)
        sat.add_clause( disc(abs(p.first)), p.first > 0,
                        disc(abs(p.second)), p.second > 0 );
    return sat.solve();
}

struct hldecomp {
    int sz[MAXN], top[MAXN], fa[MAXN], 
        son[MAXN], depth[MAXN], id[MAXN];
    
    void debug() {
        printf("id\tfa\tson\n");
        for (int i = 1; i < m + m; i++) { 
            printf("%d\t%d\t%d\n", i, fa[i], son[i]);
        }
    }

    void dfs1(int x, int dep, int par) {
        depth[x] = dep; sz[x] = 1; fa[x] = par;
        int maxn = 0, s = 0;
        for (int c : adj[x]) {
            if (c == par) continue;
            dfs1(c, dep + 1, x);
            sz[x] += sz[c];
            if (sz[c] > maxn) maxn = sz[s = c];
        }
        son[x] = s;
    }

    int cid = 0;
    void dfs2(int x, int t) {
        top[x] = t; id[x] = ++cid;
        if (son[x]) dfs2(son[x], t);
        for (int c : adj[x]) {
            if (c == fa[x]) continue;
            if (c == son[x]) continue; else dfs2(c, c);
        }
    }

    void decomp(int root) {
        dfs1(root, 1, 0); dfs2(root, root);
    }

    void solve(int cur) {
        int u = cur;
        vector<int> sons;
        do { sons.push_back(u); } while (u = son[u]);
//        printf("%d: ", cur);
//        for (int x : sons) printf("%d ", x); puts("");
        for (int s : sons) {
            for (int c : adj[s]) {
                if (c == fa[s] || c == son[s]) continue;
                solve(c);
            }
        }
        int l = 0, r = sons.size();
        while (l < r) {
            int mid = (r + l) / 2;
            int res = solvetr(sons[mid]);
//            printf("try %d = %d\n", sons[mid], res);
            if (res) r = mid;  else l = mid + 1;
        }
        for (int i = l; i < sons.size(); i++) ok[sons[i]] = true;
    }
} dcmp;

int main() {
    scanf("%d%d", &n, &m);
    Rep (i, m) 
       scanf("%d%d", &cond[i].first, &cond[i].second);
    for (int i = m + 1; i < m + m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[i].push_back(u); adj[u].push_back(i);
        adj[i].push_back(v); adj[v].push_back(i);
    }
    int root = m + m - 1;
    dcmp.decomp(root);
    dcmp.solve(root);
    for (int i = m + 1; i < m + m; i++) 
        puts(ok[i] ? "Possible" : "Impossible");
    return 0;
}
