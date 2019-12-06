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
 
const int MAXN = 4005;
 
struct twoSAT {
    int n;
    vector<int> G[MAXN * 2];
    
    bool mark[MAXN * 2];
    int S[MAXN * 2], c;
 
    void init(int n) {
        this->n = n;
        rep (i, n * 2) G[i].clear();
        memset(mark, 0, sizeof mark);
    }
    
    bool dfs(int x) {
        if (mark[x ^ 1]) return false;
        if (mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for (int u : G[x]) if (!dfs(u)) return false;
        return true;
    }
    
    void add_clause(int x, bool xval, int y, bool yval) {
        x = x * 2 + xval;
        y = y * 2 + yval;
        G[x].push_back(y);
    }
 
    void add_clause(int x, int y) { G[x].push_back(y); }
 
    bool solve() {
        for (int i = 0; i < n * 2; i += 2) {
            if (!mark[i] and !mark[i+1]) {
                c = 0;
                if (!dfs(i)) {
                    while (c > 0) mark[S[--c]] = false;
                    if (!dfs(i + 1)) return false;
                }
            }
        }
        return true;
    }
} sat;
 
int n;
int u[MAXN], v[MAXN];
bool reach[MAXN][MAXN];
vector<int> adj[MAXN];
 
void dfs(int u, int s) {
    if (reach[s][u]) return;
    reach[s][u] = true;
    for (int v : adj[u]) dfs(v, s);
}
 
bool check(int x) {
    sat.init(x);
    rep (i, x + x) rep (j, i) if (i != j) {
        if (!reach[v[i]][u[j]] and !reach[v[j]][u[i]]) { 
            sat.add_clause(i, j ^ 1);
            sat.add_clause(j, i ^ 1);
        }
    }
    bool ret = sat.solve();
    return ret;
}
 
int main() {
    scanf("%d", &n);
    rep (i, n + n) {
        scanf("%d%d", u + i, v + i);
        adj[u[i]].push_back(v[i]);
    }
    Rep (i, n) dfs(i, i);
    int l = 1, r = n + 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (check(m)) l = m + 1; else r = m;
    }
    printf("%d\n", l - 1);
    return 0;
}