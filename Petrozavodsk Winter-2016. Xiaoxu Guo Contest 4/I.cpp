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

const int mod = 1000000007;
int update(int &x, int y) {
    x += y; if (x >= mod) x -= mod;
    return x;
}

int n;
int g[32][32];
int dp[1 << 24];

int ans = 0;
int sel;

void dfs(int i) {
    if (i == n) {
        update(ans, dp[~sel & ((1 << (n - 6)) - 1)]);
    } else if (sel & (1 << i)) {
        dfs(i + 1);
    } else {
        sel ^= 1 << i;
        rep (j, n) if (~sel & (1 << j)) if (g[i][j]) {
            sel ^= 1 << j;
            dfs(i + 1);
            sel ^= 1 << j;
        }
        sel ^= 1 << i;
    }
}

void work(int n) {
    dp[0] = 1;
    for (unsigned mask = 0; mask < (1 << n); mask++) if (!(__builtin_popcount(mask) & 1)) {
        int u = __builtin_ctz(mask);
        unsigned nmask = mask ^ (1 << u);
        for (int v = u + 1; v < n; v++) if (mask & (1 << v)) if (g[u][v])
            update(dp[mask], dp[nmask ^ (1 << v)]);
    }
}


int main() {
    int m;
    scanf("%d%d", &n, &m);
    rep (_, m) {
        int u, v; scanf("%d%d", &u, &v);
        u--; v--;
        g[u][v] = g[v][u] = 1;
    }
    if (n & 1) return puts("0"), 0;
    if (n <= 24) {
        work(n);
        cout << dp[(1<<n)-1] << endl;
    } else {
        work(n - 6);
        dfs(n - 6);
        cout << ans << endl;
    }
    return 0;
}
