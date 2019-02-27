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

#define MAXN 512
vector<int> adj[MAXN];

#define kill wrfuygie

int n;
int dist[512][512];
int weight[512];
bool kill[512];
vector<int> conn;

void update(int u, int v) {
    Rep (w, n) if (dist[u][w] <= dist[v][w]) kill[w] = true;
}

int findroot() {
    int minv = INT_MAX, ans = 0;
    Rep (u, n) {
        int cur = 0;
        if (kill[u]) continue;
        for (int v : adj[u]) {
            int cnt = 0;
            Rep (w, n) {
                if (kill[w]) continue;
                if (dist[v][w] < dist[u][w]) cnt++;
            }
            cur = max(cur, cnt);
        }
        if (cur < minv) {
            minv = cur;
            ans = u;
        }
    }
    _debug("%d, %d", minv, ans);
    return ans;
}

int ask(int x) {
    printf("%d\n", x);
    fflush(stdout);
    char buf[32];
    scanf("%s", buf);
    if (buf[0] == 'F') return 0;
    scanf("%d", &x);
    return x;
}

void work() {
    memset(kill, 0, sizeof kill);
    while (1) {
        int rt = findroot();
        kill[rt] = true;
        int v = ask(rt);
        if (v == 0) return; 
        update(rt, v);
    }
}

int main() {
    int m; scanf("%d%d", &n, &m);
    memset(dist, 0x3f, sizeof dist);
    Rep (i, n) dist[i][i] = 0;
    while (m--) {
        int u, v, sz; scanf("%d", &sz);
        rep (i, sz) {
            scanf("%d", &v);
            if (i) {
                dist[u][v] = dist[v][u] = 1;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            u = v;
        }
    }
    Rep (k, n) Rep (i, n) Rep (j, n) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    rep (_, n) work();
    return 0;
}
