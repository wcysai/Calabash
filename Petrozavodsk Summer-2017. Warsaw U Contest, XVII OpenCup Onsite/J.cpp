#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(fmt, ...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

struct edge {
    int from, to;
    LL cap, flow;
};

const int MAXN = 1005;

struct Dinic {
    int n, m, s, t;
    vector<edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];

    void add_edge(int from, int to, LL cap) {
        _debug("%d->%d:%lld", from, to, cap);
        edges.push_back(edge{from, to, cap, 0});
        edges.push_back(edge{to, from, 0, 0});
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool bfs() {
        memset(vis, 0, sizeof vis);
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        d[s] = 0;
        while (q.size()) {
            int x = q.front(); q.pop();
            for (int i = 0; i < G[x].size(); i++) {
                edge & e = edges[G[x][i]];
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
        if (x == t or a == 0) return a;
        LL flow = 0, f;
        for (int &i = cur[x]; i < G[x].size(); i++) {
            edge& e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] and (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    LL max_flow(int s, int t) {
        this->s = s; this->t = t;
        LL flow = 0;
        while (bfs()) {
            memset(cur, 0, sizeof cur);
            flow += dfs(s, LLONG_MAX);
        }
        return flow;
    }
} dinic;

int n, m;

int en;
vector<int> evp;
vector<tuple<int, int, int>> task;

#define SRC 1
#define DEST 2
#define TASK(x) (3 + (x))
#define SLICE(x) (205 + (x))

int main() {
    scanf("%d%d", &n, &m);
    LL tot = 0;
    rep (i, n) {
        int s, e, c; scanf("%d%d%d", &s, &e, &c);
        task.emplace_back(s, e, c);
        tot += c;
        evp.push_back(s); evp.push_back(e);
    }
    sort(range(evp));
    evp.erase(unique(range(evp)), evp.end());
    en = evp.size();
    rep (_, task.size()) {
        int s, t, c; tie(s, t, c) = task[_];
        dinic.add_edge(SRC, TASK(_), c);
        for (int i = 0; i < en - 1; i++)
            if (evp[i] >= s and evp[i + 1] <= t)
                dinic.add_edge(TASK(_), SLICE(i), evp[i + 1] - evp[i]);
    }
    rep (i, en - 1)
        dinic.add_edge(SLICE(i), DEST, (evp[i + 1] - evp[i]) * m);
    LL fv = dinic.max_flow(SRC, DEST);
    _debug("flow=%lld", fv);
    puts((fv == tot) ? "YES" : "NO");
    return 0;
}
