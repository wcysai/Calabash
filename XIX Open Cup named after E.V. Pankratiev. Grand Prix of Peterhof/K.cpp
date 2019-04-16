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

int n, rt;
int fa[512];
char clr[512];
vector<int> ch[512];
//      id   #b  BLACK
bool dp[512][512][2];

void dfs(int u) {
    if (u == 0) return;
    int c1 = ch[u][0], c2 = ch[u][1];
    dfs(c1); dfs(c2);
    for (int nb = 1; nb < 512; nb++) {
        if (dp[c1][nb][1] and dp[c2][nb][1])
            dp[u][nb][0] = true;
        if ((dp[c1][nb-1][0] or dp[c1][nb-1][1]) and
            (dp[c2][nb-1][0] or dp[c2][nb-1][1]))
            dp[u][nb][1] = true;
    }
}

void getans(int u, int c, int cur) {
    assert(dp[u][cur][c]);
    if (u == 0) return;
    clr[u] = (c == 1 ? 'B' : 'R');
    if (c == 0) {
        for (int v : ch[u])
            getans(v, 1, cur);
    } else {
        for (int v : ch[u]) {
            if (dp[v][cur - 1][0]) {
                getans(v, 0, cur - 1);
            } else {
                getans(v, 1, cur - 1);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    Rep (i, n) {
        scanf("%d", fa + i);
        ch[fa[i]].push_back(i);
    }
    rt = ch[0][0];
    Rep (i, n) while (ch[i].size() < 2) ch[i].push_back(0);
    dp[0][1][1] = true;
    dfs(rt);
    for (int i = 0; i < 512; i++) 
        if (dp[rt][i][1]) {
            getans(rt, 1, i);
            printf("%s", clr + 1);
            return 0;
        }
    puts("Impossible");
    return 0;
}
