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

#define next shue

int n;
int next[100005][2];
int clr[100005];
int fa[100005];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool unite(int u, int v) {
    u = find(u); v = find(v); fa[u] = v;
    return u != v;
}

int main() {
    int u, v;
    scanf("%d", &n); scanf("%d%d", &u, &v);
    iota(fa, fa + n, 0);
    rep (i, n) scanf("%d%d%d", next[i], next[i] + 1, clr + i);
    queue<tuple<int, int, int>> q; q.emplace(u, v, 0);
    while (q.size()) {
        int u, v, d; tie(u, v, d) = q.front(); q.pop();
        if (clr[u] != clr[v]) {
            printf("%d\n", d);
            return 0;
        }
        if (unite(u, v)) {
            q.emplace(next[u][0], next[v][0], d + 1);
            q.emplace(next[u][1], next[v][1], d + 1);
        }
    }
    puts("indistinguishable");
    return 0;
}
