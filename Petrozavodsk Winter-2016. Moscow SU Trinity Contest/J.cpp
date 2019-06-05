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

int n, m;
vector<pair<int, char>> adj[500005];
char s1[1 << 20], s2[1 << 20];
int a1[1 << 20], f1[1 << 20], a2[1 << 20], f2[1 << 20];

[[noreturn]] void done(int u, int v) {
    printf("%d %d\n", u, v);
    exit(0);
}

void dfs(int u, int p) {
    int ma1 = 0, mf1 = u, ma2 = 0, mf2 = u;
    for (auto pr : adj[u]) {
        int v; char ch; tie(v, ch) = pr;
        if (v == p) continue;
        _debug("%d %c", v, ch);
        dfs(v, u);
        int ca1 = a1[v] + (s1[a1[v]] == ch);
        int ca2 = a2[v] + (s2[a2[v]] == ch);
        if (ca1 + ma2 >= m) done(f1[v], mf2);
        if (ma1 + ca2 >= m) done(mf1, f2[v]);
        if (ca1 > ma1) ma1 = ca1, mf1 = f1[v];
        if (ca2 > ma2) ma2 = ca2, mf2 = f2[v];
    }
    a1[u] = ma1; f1[u] = mf1;
    a2[u] = ma2; f2[u] = mf2;
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, n - 1) {
        int u, v; char ch[2];
        scanf("%d%d%s", &u, &v, ch);
        adj[u].emplace_back(v, ch[0]);
        adj[v].emplace_back(u, ch[0]);
    }
    scanf("%s", s1); strcpy(s2, s1); reverse(s2, s2 + m);
    dfs(1, 0);
    puts("-1 -1");
    return 0;
}
