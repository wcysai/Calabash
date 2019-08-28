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

const LL mod = 1'000'000'009;
int n, k;

//   len(pref)  maxdep  curdep
LL dp[305][305][305];

int main() {
    cin >> n >> k;
    dp[0][0][0] = 1;
    for (int i = 0; i <= n; i++) for (int md = 0; md <= k; md++) for (int d = 0; d <= k; d++) {
        LL now = (dp[i][md][d] %= mod);
        dp[i+1][md][d] += now; // 0
        if (d) dp[i+1][md][d-1] += now; // )
        dp[i+1][max(md, d+1)][d+1] += now; // (
    }
    cout << dp[n][k][0] << endl;
    return 0;
}
