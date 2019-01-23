#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

struct edge {
    int from, to, id;
    LL cap, flow;
};

const int MAXN = 128;
struct Dinic {
    int n, m, s, t;
    vector<edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];
    
    void init(int nv) {
        n = nv; m = 0;
        edges.clear();
        for (auto& v : G) v.clear();
        memset(vis, 0, sizeof vis);
        memset(d, 0, sizeof d);
        memset(cur, 0, sizeof cur);
    }

    void add_edge(int from, int to, int id, LL cap) { 
        edges.push_back(edge{from, to, id, cap, 0});
        edges.push_back(edge{to, from, id, 0, 0});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        d[s] = 0;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int i = 0; i < G[x].size(); i++) {
                edge& e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    LL dfs(int x, LL a) {
        if (x == t || a == 0) return a;
        LL flow = 0, f;
        for (int& i = cur[x]; i < G[x].size(); i++) {
            edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = dfs(e.to, min(a, e.cap-e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    LL max_flow(int s, int t) {
        this->s = s; this->t = t;
        LL flow = 0;
        while (bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, LLONG_MAX);
        }
        return flow;
    }

    vector<int> min_cut() { // call this after maxflow
        vector<int> ans;
        for (int i = 0; i < edges.size(); i++) {
            edge& e = edges[i];
            if(vis[e.from] && !vis[e.to] && e.cap > 0)
                ans.push_back(e.id);
        }
        return ans;
    }
} dinic;

int n, m;
int u[512], v[512];
LL w[512];

bool check(LL k) {
    LL ans = 0;
    dinic.init(n + 1);
    Rep (i, m) {
        if (w[i] <= k) ans += w[i] - k;
        else {
            dinic.add_edge(u[i], v[i], i, w[i] - k);
            dinic.add_edge(v[i], u[i], i, w[i] - k);
        }
    }
    ans += dinic.max_flow(1, n);
    return ans > 0;
}

int main() {
    freopen("network.in", "r", stdin);
    freopen("network.out", "w", stdout);
    cin >> n >> m;
    Rep (i, m) cin >> u[i] >> v[i] >> w[i], w[i] *= 2;
    LL l = -1, r = 20000005, mid;
    while (r > l) {
        mid = (l + r) / 2;
        if (check(mid)) l = mid + 1; else r = mid;
    }
    mid = r - 1;
    check(mid);
    vector<int> ans = dinic.min_cut();
    Rep (i, m) if (w[i] <= mid) ans.push_back(i);
    cout << ans.size() << endl;
    sort(range(ans));
    for  (int v : ans) cout << v << ' ';
    return 0;
}


