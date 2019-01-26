#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)
typedef long long LL;
typedef __int128_t i128;

int m, n;
i128 a[1 << 20], s[1 << 20];
pair<i128, int> dp[1 << 20];

int check(i128 c) {
    pair<i128, int> best(0, 0);
    Rep (i, n) {
        dp[i] = max(dp[i-1], {best.first + s[i] + c, best.second - 1});
        best = max(best, {dp[i].first - s[i], dp[i].second});
    }
    return -dp[n].second;
}

int main() {
    freopen("holidays.in", "r", stdin);
    freopen("holidays.out", "w", stdout);
    scanf("%d%d", &n, &m);
    int cpos = 0;
    LL ans = 0;
    Rep (i, n) {
        int ss; scanf("%d", &ss);
        if (ss >= 0) {
            cpos ++;
            ans += ss;
        }
        a[i] = ss;
    }
    if (cpos < m) {
        printf("%lld\n", ans);
        return 0;
    }
    partial_sum(a, a + 1 + n, s);
    i128 l = -1000000000 * i128(n) - 5, r = -l;
    while (l < r) {
        i128 mid = l + (r - l) / 2;
        if (check(mid) <= m) l = mid + 1; else r = mid;
    }
    check(--l);
    printf("%lld\n", LL(dp[n].first - m * l));
    return 0;
}
