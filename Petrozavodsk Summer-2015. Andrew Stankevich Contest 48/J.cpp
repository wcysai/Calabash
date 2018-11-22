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
#define PROBLEM "jackpot"
typedef long long LL;
typedef unsigned long long ULL;
template <class T1, class T2> T1 minz(T1& l, T2 r) { return l = min(l, (T1)r); }
template <class T1, class T2> T1 maxz(T1& l, T2 r) { return l = max(l, (T1)r); }

struct edge {
    int from, to, cap, flow, cost;
};

const int INF = INT_MAX / 2;
const int MAXN = 1024;

struct MCMF {
    int s, t, m;
    vector<edge> edges;
    vector<int> G[MAXN];
    bool inq[MAXN];
    int d[MAXN];
    int p[MAXN];
    int a[MAXN];
    
    void clear() {
        m = 0;
        edges.clear(); 
        for (auto & v : G) v.clear();
        memset(inq, 0, sizeof inq);
        memset(d, 0, sizeof d);
        memset(p, 0, sizeof p);
        memset(a, 0, sizeof a);
    }

    void add_edge(int from, int to, int cap, int cost) {
//        _debug("%d, %d, %d, %d", from, to, cap, cost);
        edges.push_back(edge{from, to, cap, 0, cost});
        edges.push_back(edge{to, from, 0, 0, -cost});
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool spfa() {
        queue<int> q;
        fill(range(d), INF); d[s] = 0;
        memset(inq, 0, sizeof(inq));
        q.push(s); inq[s] = true;
        p[s] = 0; a[s] = INT_MAX;
        while (q.size()) {
            int u = q.front(); q.pop(); inq[u] = false;
            rep (i, G[u].size()) {
                edge& e = edges[G[u][i]];
                if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if (!inq[e.to]) q.push(e.to), inq[e.to] = true;
                }
            }
        }
        return d[t] != INF;
    }


    void augment() {
        int u = t;
        while (u != s) {
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
            u = edges[p[u]].from;
        }
    }

    int min_cost(int s, int t, int& cost) {
        this->s = s; this->t = t;
        int flow = 0;
        cost = 0;
        while (spfa()) {
            augment();
            flow += a[t];
            cost += a[t] * d[t];
        }
        return flow;
    }
} mcmf;

int m, n;
char type[512];
int nw[512], nb[512], nd[512];
int w[512], b[512], c[512];
int cost[512][512];

#define SRC         1
#define DEST        2
#define TOKEN(x)    ((x) + 100)
#define CARD(x)     ((x) + 500)

int main() {
#ifndef __LOCAL_DEBUG__
    freopen(PROBLEM ".in", "r", stdin);
    freopen(PROBLEM ".out", "w", stdout);
#endif
    while (scanf("%d", &m), m) {
        mcmf.clear();
        memset(nw, 0, sizeof nw);
        memset(nb, 0, sizeof nb);
        memset(nd, 0, sizeof nd);
        scanf("%s", type);
        Rep (i, m) {
            if (type[i-1] == 'W') {
                nw[i] = 1; 
            } else if (type[i-1] == 'B') {
                nb[i] = 1; 
            } else {
                nd[i] = 1; 
            }
        }
        partial_sum(nw, nw + m + 1, nw);
        partial_sum(nb, nb + m + 1, nb);
        partial_sum(nd, nd + m + 1, nd);
        scanf("%d", &n);
        rep (i, n) scanf("%d%d%d", w + i, b + i, c + i);
        Rep (i, m) {
            rep (j, n) 
                cost[j][i] = max(max(w[j] - nw[i-1], 0) + max(b[j] - nb[i-1], 0) - nd[i-1], 0);
        }
        Rep (i, m) mcmf.add_edge(SRC, TOKEN(i), 1, 0);
        Rep (i, m) {
            rep (j, n) {
                mcmf.add_edge(TOKEN(i), CARD(j), 1, cost[j][i]);
            }
        }
        rep (i, n) mcmf.add_edge(CARD(i), DEST, c[i], 0);
        int cost = 0;
        int flow = mcmf.min_cost(SRC, DEST, cost);
        assert(flow == m);
        printf("%d\n", cost);
    }
    return 0;
}
