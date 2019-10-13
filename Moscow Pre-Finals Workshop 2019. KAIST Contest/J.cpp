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

const int MAXN = 200005;

struct Kuhn {
    int n1, n2;
    vector<int> adj[MAXN];
    int mx[MAXN], my[MAXN];
    int dx[MAXN], dy[MAXN];
    bool vis[MAXN];

    bool vx[MAXN], vy[MAXN];

    bool find(int u) {
        for (int v : adj[u]) {
            if (!vis[v] && dy[v] == dx[u] + 1) {
                vis[v] = true;
                if (!my[v] or find(my[v])) {
                    mx[u] = v;
                    my[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    int matching() {
        queue<int> q;
        memset(mx, 0, sizeof(mx));
        memset(my, 0, sizeof(my));
        int ans = 0;
        while (true) {
            bool flag = false;
            while (q.size()) q.pop();
            memset(dx, 0, sizeof(dx));
            memset(dy, 0, sizeof(dy));
            Rep (i, n1) if (!mx[i]) q.push(i);
            while (q.size()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) if (!dy[v]) {
                    dy[v] = dx[u] + 1;
                    if (my[v]) {
                        dx[my[v]] = dy[v] + 1;
                        q.push(my[v]);
                    } else flag = true;
                }
            }
            if (!flag) break;
            memset(vis, 0, sizeof(vis));
            Rep (i, n1) if (!mx[i] && find(i)) ans++;
        }
        return ans;
    }
} km;

int n, m;
int u[200005], v[200005], cap[200005];
vector<pair<int, int>> adj[200005];
bool vis[200005];

int dfs(int u) {
    vis[u] = true;
    int tot = bool(u > 100002);
    for (auto p : adj[u]) {
        int v, id; tie(v, id) = p;
        if (vis[v]) continue;
        int sz = dfs(v); tot += sz;
        if (id > 0) cap[id] += sz; else cap[-id] -= sz;
    }
    return tot;
}

int main() {
    scanf("%d%d", &n, &m);
    km.n1 = n; km.n2 = n - 1;
    Rep (i, m) {
        scanf("%d%d", v + i, u + i);
        km.adj[u[i]].push_back(v[i]);
    }
    if (km.matching() != n - 1) return puts("-1"), 0;
    int unsat;
    Rep (i, n) if (!km.mx[i]) unsat = i;
    Rep (i, m) {
        if (km.mx[u[i]] == v[i]) {
            cap[i] = n - 1;
            adj[v[i] + 100002].emplace_back(u[i], -i);
        } else {
            adj[u[i]].emplace_back(v[i] + 100002, i);
        }
    }
    if (dfs(unsat) != n - 1) return puts("-1"), 0;
    Rep (i, m) printf("%d\n", cap[i]);
    return 0;
}
