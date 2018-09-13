#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define Rep(i, n) for (int i = 1; i <=n; i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

typedef long long LL;

LL dp[1 << 16][16];
int n;
LL d[16][16];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cin >> d[i][j];
            d[j][i] = d[i][j];
        }
    }
    _debug("DONE");
    // TODO: initialize dp value
    rep (i, 1 << 16) rep (j, 16) dp[i][j] = LLONG_MAX / 2;
    _debug("DONE2");
    rep (i, n) dp[1 << i][i] = 0;
    for (unsigned mask = 1; mask < (1u << n); mask++) {
        if (__builtin_popcount(mask) == 1) continue;
        for (unsigned cur = (mask - 1) & mask; cur; cur = (cur - 1) & mask) {
            unsigned another = mask ^ cur;
            int sz1 = __builtin_popcount(cur), sz2 = __builtin_popcount(another);
            for (unsigned m1 = cur; m1; m1 &= m1 - 1) {
                for (unsigned m2 = another; m2; m2 &= m2 - 1) {
                    int p1 = __builtin_ctz(m1), p2 = __builtin_ctz(m2);
                    dp[mask][p1] = min(dp[mask][p1],
                            dp[cur][p1] + dp[another][p2] + (n - sz2) * sz2 * d[p1][p2]);
                }
            }
        }
    }
    LL ans = LLONG_MAX;
    rep (i, n) ans = min(ans, dp[(1 << n) - 1][i]);
    cout << ans << endl;
    return 0;
}
