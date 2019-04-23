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

struct array_wrapper {
    int dp[100005][256]; 
    array_wrapper() { memset(dp, 0x7f7f7f7f, sizeof dp); }
    int& operator()(int i, int j) {
        return dp[i][j - i + 128];
    }
} dp;

int n, k;
int a[100005], b[100005];

int main() {
    scanf("%d%d", &n, &k);
    Rep (i, n) scanf("%d", a + i);
    Rep (i, n) scanf("%d", b + i);
    rep (i, 110) dp(0, i) = dp(i, 0) = i;
    Rep (i, n) for (int j = i - 100; j <= i + 100; j++) {
        if (j <= 0 or j > n) continue;
        dp(i, j) = min(dp(i-1, j), dp(i, j-1));
        if (abs(a[i] - b[j]) > k) dp(i, j) = min(dp(i, j), dp(i-1, j-1));
        dp(i, j) ++;
    }
    cout << dp(n, n) << endl;
    return 0;
}
