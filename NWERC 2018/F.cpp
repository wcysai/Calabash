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

const int MAXN = 4096;
typedef pair<LL, int> pii;

struct MDST {
    int V;
    LL heap[MAXN][MAXN];
//    priority_queue<pii, vector<pii>, greater<pii>> heap[MAXN];
    LL shift[MAXN];
    int fa[MAXN], vis[MAXN];

    void init(int n) {
        V = n;
        Rep (i, n) Rep (j, n) heap[i][j] = LLONG_MAX / 2;
    }

    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    void unite(int x, int y) {
        x = find(x); y = find(y); fa[y] = x; if (x == y) return ;
        Rep (i, V) heap[x][i] = min(heap[x][i], heap[y][i] - shift[y] + shift[x]);
    }

    void add_edge(int u, int v, LL w) { heap[v][u] = min(heap[v][u], w); }

    LL run(int n, int rt) {
        V = n;
        LL ans = 0;
        iota(fa, fa + n + 1, 0);
        Rep (i, n) if (find(i) != find(rt)) {
            int u = find(i);
            stack<int, vector<int>> s;
            while (find(u) != find(rt)) {
                if (vis[u]) while (s.top() != u) {
                    vis[s.top()] = 0; unite(u, s.top()); s.pop();
                } else { vis[u] = 1; s.push(u); }

                Rep (i, V) if (find(i) == u) heap[u][i] = LLONG_MAX / 2;
                
                auto ptr = min_element(heap[u] + 1, heap[u] + V + 1);
                if (*ptr == LLONG_MAX / 2) return LLONG_MIN;
                ans += *ptr - shift[u];
                shift[u] = *ptr;

                u = ptr - heap[u];
            }
            while (s.size()) { vis[s.top()] = 0; unite(rt, s.top()); s.pop(); }
        }
        return ans;
    }
} mdst;

int n;

#define ID(x) ((x) + 1)

int main() {
    scanf("%d", &n);
    mdst.init(n + 1);
    Rep (i, n) {
        int x, s; scanf("%d%d", &x, &s);
        mdst.add_edge(ID(x), ID(i), s);   
        for (int j = 0; j <= n; j++) {
            int val; scanf("%d", &val);
            mdst.add_edge(ID(j), ID(i), val);
        }
    }
    cout << mdst.run(n + 1, ID(0)) << endl;
    return 0;
}
