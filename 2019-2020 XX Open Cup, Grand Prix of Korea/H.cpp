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
int a[256000], b[256000];
int x[256000], y[256000];

LL work() {
    int dp[3] = {0, 0, 0};
    LL ans = 0;
    rep (i, n) {
        dp[x[i]]++;
        dp[y[i]]--;
        rep (j, 3) ans += max(dp[j], 0);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d", a + i), a[i]--;
    rep (i, n) scanf("%d", b + i), b[i]--;
    if (n % 2 == 0) {
        rep (i, n) x[i] = (a[i] >= (n / 2));
        rep (i, n) y[i] = (b[i] < (n / 2));
        cout << work() << endl;
    } else {
        rep (i, n) x[i] = int(a[i] > (n / 2)) * 2;
        rep (i, n) y[i] = int(b[i] < (n / 2)) * 2;
        LL ans = 0;
        rep (i, n) if (a[i] == n / 2) x[i] = 1;
        rep (i, n) if (b[i] == n / 2) y[i] = 1;
        ans = work();
        rep (i, n) if (a[i] == n / 2) x[i] = 0;
        rep (i, n) if (b[i] == n / 2) y[i] = 0;
        ans = min(ans, work());
        rep (i, n) if (a[i] == n / 2) x[i] = 2;
        rep (i, n) if (b[i] == n / 2) y[i] = 2;
        ans = min(ans, work());
        cout << ans << endl;
    }
    return 0;
}
