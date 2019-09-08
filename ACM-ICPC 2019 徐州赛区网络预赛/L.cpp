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

int dist(int x, int y) {
    x = abs(x); y = abs(y);
    if (x > y) swap(x, y);
    if (x > 1) return x + y;
    if (x == 1 and y == 1) return 6;
    static const int per[4] = {0, 3, 4, 5};
    return y / 4 * 4 + per[y % 4] + x;
}

int n;
int x[20], y[20];
int d[20][20];
int dp[1 << 16][16];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        rep (i, n) scanf("%d%d", x + i, y + i);
        rep (i, n) rep (j, n) d[i][j] = dist(x[i] - x[j], y[i] - y[j]);
        memset(dp, 0x7f7f7f7f, sizeof dp);
        rep (i, n) dp[1<<i][i] = dist(x[i], y[i]);
        for (unsigned mask = 1; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) == 0) continue;
            rep (v, n) if (mask & (1 << v)) {
                rep (u, n) if (u != v and mask & (1 << u)) {
                    dp[mask][v] = min(dp[mask][v],
                        dp[mask ^ (1 << v)][u] + d[u][v]);
                }
            }
        }
        int ans = INT_MAX;
        rep (i, n) ans = min(ans, dp[(1<<n)-1][i]);
        cout << ans << endl;
    }
    return 0;
}
