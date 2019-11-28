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

const LL mod = 1000000007;
int n, m;
int dp[5005][5005], sdp[5005][5005], sldp[5005][5005];

int madd(int x, int y) {
    x += y; if (x >= mod) x -= mod;
    return x;
}

int main() {
    scanf("%d%d", &m, &n);
    Rep (s, n) {
        Rep (k, min(s, m)) {
            if (s == k) dp[s][k] = 1;
            else dp[s][k] = (LL(k + 1) * sdp[s-k][k] - sldp[s-k][k]) % mod;
            if (dp[s][k] < 0) dp[s][k] += mod;
            sldp[s][k] = dp[s][k] * LL(k) % mod;
        }
        partial_sum(range(dp[s]), sdp[s], madd);
        partial_sum(range(sldp[s]), sldp[s], madd);
    }
    printf("%d\n", dp[n][m]);
    return 0;
}
