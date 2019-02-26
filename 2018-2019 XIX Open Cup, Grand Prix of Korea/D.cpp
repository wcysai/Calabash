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

const int MAXN = 300005;
int n, m;
int l[MAXN], r[MAXN];
int deg[MAXN], ans[MAXN], clr[MAXN];
vector<int> adj[MAXN];

void dfs(int u) {
    if (clr[u] == 1) { printf("-1\n"); exit(0); }
    if (clr[u] == 2) return;
    if (clr[u] == 0) {
        clr[u] = 1;
        for (int v : adj[u]) {
            dfs(v);
            r[u] = min(r[u], r[v]);
        }
        clr[u] = 2;
    }
}

bool cmp1(int lhs, int rhs) { return l[lhs] > l[rhs]; }
bool cmp2(int lhs, int rhs) { return r[lhs] > r[rhs]; }
priority_queue<int, vector<int>, bool (*)(int, int)> pq1(cmp1), pq2(cmp2);

int main() {
    scanf("%d%d", &n, &m);
    Rep (i, n) {
        scanf("%d%d", l + i, r + i);
        l[i]--; r[i]--;
    }
    rep (_, m) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v); deg[v]++;
    }
    Rep (i, n) if (!clr[i]) dfs(i);
    int ptr = 0;
    Rep (i, n) if (deg[i] == 0) pq1.push(i);
    do {
        while (pq1.size() and l[pq1.top()] <= ptr) pq2.push(pq1.top()), pq1.pop();
        if (pq2.empty() or r[pq2.top()] < ptr) { printf("-1\n"); return 0; }
        int u = pq2.top(); pq2.pop();
        ans[ptr++] = u;
        for (int v : adj[u]) if (--deg[v] == 0) pq1.push(v);
    } while (ptr < n);
    rep (i, n) printf("%d\n", ans[i]);
    return 0;
}
