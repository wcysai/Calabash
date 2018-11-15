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

struct DAG {
    vector<int> adj[500005];
    int deg[500005];
    int dist[500005];
    vector<int> topo;

    void clear() {
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            adj[i].shrink_to_fit();
        }
        memset(deg, 0, sizeof deg);
        memset(dist, 0, sizeof dist);
        topo.clear();
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        deg[v]++;
    }

    void work() {
        vector<int> q; topo.push_back(0);
        for (int i = 1; i <= n; i++) if (deg[i] == 0) q.push_back(i);
        while (q.size()) {
            int u = q.back(); q.pop_back();
            topo.push_back(u);
            for (int v : adj[u]) {
                dist[v] = max(dist[v], dist[u] + 1);
                deg[v]--;
                if (deg[v] == 0) q.push_back(v);
            }
        }
    }

} dag;

int ds[500005], dt[500005];
int topord[500005];
pair<int, int> edges[1000005];
vector<int> topo;
vector<pair<int, int>> update[500005];
int ans[500005];

int main() {
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        edges[i] = {u, v};
    }
    
    {   // build pos dag
        dag.clear();
        rep (i, m) dag.addEdge(edges[i].first, edges[i].second);
        dag.work();
        memcpy(ds, dag.dist, sizeof ds);
    }
    
    topo = dag.topo;
    for (int i = 0; i <= n; i++) 
        topord[topo[i]] = i;
    
    {   // build neg dag
        dag.clear();
        rep (i, m) dag.addEdge(edges[i].second, edges[i].first);
        dag.work();
        memcpy(dt, dag.dist, sizeof dt);
    } 

    Rep (i, n) {
        int ou = 0, ov = topord[i];
        _debug("%d %d %d", ou, ov, dt[i]);
        update[ou].emplace_back(ov, dt[i]);
    }
    
    Rep (i, n) {
        int ou = topord[i], ov = n+1;
        _debug("%d %d %d", ou, ov, ds[i]);
        update[ou].emplace_back(ov, ds[i]);
    }
 
    rep (i, m) {
        int u, v; tie(u, v) = edges[i];
        int ou = topord[u], ov = topord[v];
        _debug("%d %d %d", ou, ov, ds[u] + dt[v] + 1);
        update[ou].emplace_back(ov, ds[u] + dt[v] + 1);
    }
         
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i <= n; i++) {
        while (pq.size() and pq.top().second <= i) pq.pop();
        // update
        if (pq.size()) ans[i] = pq.top().first; else ans[i] = INT_MAX;

        for (auto p : update[i]) 
            pq.emplace(p.second, p.first); 
    }

    int maxv = INT_MAX, id = 0;
    for (int u = 1; u <= n; u++) {
        _debug("ans[%d]=%d", topo[u], ans[u]);
        if (ans[u] < maxv) {
            maxv = ans[u];
            id = u;
        }
    }
    
    printf("%d %d\n", topo[id], maxv);
    return 0;
}
