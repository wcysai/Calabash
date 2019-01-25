#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)

int n, m, d;
int w[1 << 16];
int sum[1 << 16];
int dp[1 << 16][2];

int check(int tot) {
    dp[0][0] = 0;
    dp[0][1] = 20005;
    for (int i = 2; i <= n; i += 2) {
        dp[i][0] = dp[i][1] = 20005;
        int low = max(i - d - d, 0);
        for (int j = i - 1, k = i - 2; k >= low; j--, k -= 2) {
            if (sum[i] - sum[j] > tot) break;
            if (sum[j] - sum[k] <= tot) {
                dp[i][0] = min(dp[i][0], dp[k][1] + 1);
                dp[i][1] = min(dp[i][1], dp[k][0] + 1);
            }
        }
    }
//    fprintf(stderr, "check %d = %d\n", tot, dp[n][m&1]);
    return dp[n][m&1];
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &d); m--;
        Rep (i, n) scanf("%d", w + i);
        partial_sum(w, w + n + 1, sum);
        if (m * d < n or (n & 1)) {
            puts("BAD");
            continue;
        }
        int l = 1, r = 100000000;
        while (r > l) {
            int mid = (l + r) / 2;
            if (check(mid) <= m) r = mid;
            else l = mid + 1;
        }
        printf("%d\n", r);
    }
    return 0;
} 
