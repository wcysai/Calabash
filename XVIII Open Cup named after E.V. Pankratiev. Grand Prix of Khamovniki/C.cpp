#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define Rep(i, n) for (int i = 1; i <=n; i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

typedef long long LL;
typedef unsigned long long ULL;

struct edge {
    int from, to;
    int cap, flow;
};

const int MAXN = 1005;
struct Dinic {
    int n, m, s, t;
    vector<edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];

    void clear() {
        edges.clear();
        for (int i = 0; i < MAXN; i++) G[i].clear();
    }

    void add_edge(int from, int to, int cap) {
        edges.push_back(edge{from, to, cap, 0});
        edges.push_back(edge{to, from, 0, 0});
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

    int dfs(int x, int a) {
        if (x == t || a == 0) return a;
        int flow = 0, f;
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

    int max_flow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, INT_MAX);
        }
        return flow;
    }
} dinic;

int n, m;
vector<int> adj[1024];
int ch[1024];
bool cover[1024];

int main() {
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Rep (u, n) {
        memset(cover, 0, sizeof cover);
        memset(ch, -1, sizeof ch);
        for (int v : adj[u]) {
            cover[v] = true;
        }
        dinic.clear();
        for (int v : adj[u]) {
            dinic.add_edge(u, v, 1);
            for (int w : adj[v]) {
                if (cover[w]) continue;
                dinic.add_edge(v, w, 1);
            }
        }
        int fcnt = 0;
        for (int v : adj[u]) {
            for (int w : adj[v]) {
                if (!cover[w]) {
                    fcnt++;
                    dinic.add_edge(w, 0, 1);
                    cover[w] = true;
                }
            }
        }
        int sz;
        // _debug("%d", u);
        Rep (i, n) if (i != u && !cover[i]) goto cont;
        sz = dinic.max_flow(u, 0);
        if (sz < fcnt) continue;
        else {
            puts("Yes");
            printf("%d %d\n", u, (int)adj[u].size());
            for (auto& e : dinic.edges) {
                // _debug("%d -> %d %d/%d", e.from, e.to, e.cap, e.flow);
                if (e.cap && e.flow && e.from != u && e.to != 0) {
                    ch[e.from] = e.to;
                }
            }
            /*
            for (int v : adj[u]) {
                bool flag = false;
                for (int eid : dinic.G[v]) {
                    flag ^= 1;
                    if (flag) continue;
                    assert(dinic.edges[eid].from == v);
                    if (dinic.edges[eid].flow) {
                        ch[v] = dinic.edges[eid].to;
                        break;
                    }
                }
            }
             */
            for(int v : adj[u]) {
                printf("%d %d\n", v, ch[v]);
            }
            return 0;
        }

        cont:;
    }
    puts("No");
    return 0;
}
