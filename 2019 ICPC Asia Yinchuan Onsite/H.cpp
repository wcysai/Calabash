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

const int MAXN = 100005, INF = INT_MAX / 2;
int n, s;
vector<pair<int, int>> adj[MAXN], dadj[MAXN];
int sccid[MAXN];
bool vis[MAXN];
int d[MAXN];

int ncc;
vector<vector<int>> cc;
vector<int> cadj[MAXN];
int indeg[MAXN];

vector<int> cur;
void dfs(int u) {
    if (vis[u]) return ;
    sccid[u] = cc.size();
    vis[u] = true; cur.push_back(u);
    for (const auto& p : adj[u]) dfs(p.first);
}

void dijkstra(int id) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    for (int u : cc[id]) if (d[u] < INF) pq.emplace(d[u], u);
    while (pq.size()) {
        int u = pq.top().second; pq.pop();
        for (auto p : adj[u]) {
            int v, w; tie(v, w) = p;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pq.emplace(d[v], v);
            }
        }
    }
}

int main() {
    int m1, m2; scanf("%d%d%d%d", &n, &m1, &m2, &s);
    fill(d + 1, d + n + 1, INF); d[s] = 0;
    rep (_, m1) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    rep (_, m2) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        dadj[u].emplace_back(v, w);
    }
    Rep (i, n) if (!vis[i]) {
        cur.clear();
        dfs(i);
        cc.push_back(move(cur));
    }
    ncc = cc.size();
    Rep (u, n) for (auto& p : dadj[u]){
        int v = p.first;
        cadj[sccid[u]].push_back(sccid[v]);
        indeg[sccid[v]]++;
    }
    vector<int> q;
    rep (i, ncc) if (indeg[i] == 0) q.push_back(i);
    while (q.size()) {
        int id = q.back(); q.pop_back();
        dijkstra(id);
        for (int v : cadj[id]) if (--indeg[v] == 0) q.push_back(v);
        for (int u : cc[id]) if (d[u] < INF) for (auto p : dadj[u])
            d[p.first] = min(d[p.first], d[u] + p.second);
    }
    Rep (i, n) if (d[i] == INF) puts("NO PATH"); else printf("%d\n", d[i]);
    return 0;
}
