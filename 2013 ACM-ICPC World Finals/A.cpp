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

const int MAXV = 64;

struct graph {
    vector<int> adj[MAXV];
    stack<int, vector<int>> s;
    int V;
    int pre[MAXV], lnk[MAXV], scc[MAXV];
    int time, sccn;

    void add_edge(int u, int v) {
        _debug("%d %d", u, v);
        adj[u].push_back(v);
    }

    void dfs(int u) {
        pre[u] = lnk[u] = ++time;
        s.push(u);
        rep (i, adj[u].size()) {
            int v = adj[u][i];
            if (!pre[v]) {
                dfs(v);
                lnk[u] = min(lnk[u], lnk[v]);
            } else if (!scc[v]) {
                lnk[u] = min(lnk[u], pre[v]);
            }

        }
        if (lnk[u] == pre[u]) {
            sccn++;
            int x;
            do {
                x = s.top(); s.pop();
                scc[x] = sccn;
            } while (x != u);
        }
    }

    void find_scc() {
        time = sccn = 0;
        memset(scc, 0, sizeof scc);
        memset(pre, 0, sizeof pre);
        Rep (i, V) {
            if (!pre[i]) dfs(i);
        }
    }

    bool get_ans() {
        return sccn < V;
    }

} g;

int get_id(bool sign, int num) {
    if (sign) num += 26;
    return num + 1;
}

bool conn[64][64] = {false};

void read_mole() {
    char str[32]; scanf("%s", str);
    bool zero[4] = {0};
    bool sign[4] = {0};
    int num[4] = {0};
    rep (i, 4) {
        if (str[i<<1] == '0') zero[i] = true;
        sign[i] = (str[i<<1|1] == '-');
        num[i] = str[i<<1] - 'A';
    }
    rep (i, 4) {
        if (zero[i]) continue;
        rep (j, 4) {
            if (i == j) continue;
            if (zero[j]) continue;
            int u = get_id(!sign[i], num[i]), v = get_id(sign[j], num[j]);
            _debug("%d %d", u, v);
            conn[u][v] = true;
        }
    }
}

int main() {
    int n; scanf("%d", &n);
    g.V = 52;
    rep (i, n) read_mole();
    Rep (i, 52) {
        Rep (j, 52) {
            if (!conn[i][j]) continue;
            if (i == j) {
                _debug("!");
                puts("unbounded");
                return 0;
            }
            g.add_edge(i, j);
        }
    }
    g.find_scc();
    if (g.get_ans()) puts("unbounded");
    else puts("bounded");
    return 0;
}
