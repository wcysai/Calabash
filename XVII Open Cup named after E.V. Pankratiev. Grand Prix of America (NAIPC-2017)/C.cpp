#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 0; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

const int mod = 1000000007;

int n;
int x[320];
bool conn[320][320];
int dp[320][320][2];

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d", x + i);
    rep (i, n) rep (j, n) if (__gcd(x[i], x[j]) != 1) conn[i][j] = 1;
    rep (i, n) dp[i][i][0] = dp[i][i][1] = 1;
    for (int i = 1; i < n; i++) dp[i-1][i][0] = dp[i-1][i][1] = conn[i-1][i];
    for (int len = 2; len < n; len++) {
        for (int l = 0; l + len < n; l++) {
            int r = l + len;
            for (int mid = l + 1; mid < r; mid++) {
                dp[l][r][0] = (dp[l][r][0] + 1ll * dp[l][mid][0] * dp[mid][r][1]) % mod;
            }
            if (conn[l][r]) {
                for (int mid = l + 1; mid <= r; mid++) {
                    int res = 1ll * dp[l][mid - 1][0] * dp[mid][r][0] % mod;
                    dp[l][r][1] += res;
                    dp[l][r][1] %= mod;
                    dp[l][r][0] += res;
                    dp[l][r][0] %= mod;
                }
            }
        }
    }
    printf("%d\n", dp[0][n-1][0]);
    return 0;
}

/*2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2*/
