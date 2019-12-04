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

const LL mod = 1'000'000'007;
int n;
char op[128];
LL dp[128][128], way[128][128];
LL C[128][128];

int main() {
    int T; scanf("%d", &T);
    rep (i, 128) rep (j, i + 1) {
        if (j == 0 or j == i) C[i][j] = 1;
        else C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
    }
    while (T--) {
        memset(dp, 0, sizeof dp); memset(way, 0, sizeof way);
        scanf("%d", &n);
        rep (i, n) scanf("%lld", &dp[i][i+1]);
        rep (i, n) way[i][i+1] = 1;
        scanf("%s", op + 1);
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len <= n; l++) {
                int r = l + len;
                dp[l][r] = 0;
                for (int k = l + 1; k < r; k++) {
                    LL coeff = C[r-l-2][k-l-1];
                    if (op[k] == '+') {
                        dp[l][r] +=
                            (way[k][r] * dp[l][k] + way[l][k] * dp[k][r]) % mod
                            * coeff % mod;
                    } else if (op[k] == '-') {
                        dp[l][r] +=
                            (way[k][r] * dp[l][k] - way[l][k] * dp[k][r]) % mod
                            * coeff % mod + mod;
                    } else if (op[k] == '*') {
                        dp[l][r] += dp[l][k] * dp[k][r] % mod * coeff % mod;
                    }
                    way[l][r] += way[l][k] * way[k][r] % mod * coeff % mod;
                }
                dp[l][r] %= mod; way[l][r] %= mod;
            }
        }
        cout << dp[0][n] << endl;
    }
    return 0;
}
