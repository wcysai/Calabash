#pragma GCC optimize(3)
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

int n;
int a[5120];
int dp[5120][5120];

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d", a + i);
    sort(a, a + n);
    rep (i, n) {
        rep (j, i) {
            int prev = a[j] - (a[i] - a[j]);
            int pos = lower_bound(a, a + j, prev) - a;
            if (a[pos] != prev) dp[i][j] = 1;
            else dp[i][j] = dp[j][pos] + 1;
        }
    }
    int ans = 0;
    rep (i, n) rep (j, i) ans = max(ans, dp[i][j]);
    cout << ans + 1 << endl;
    return 0;
}
