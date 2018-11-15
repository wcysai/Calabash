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

int n, m, nz;
vector<LL> a;

int check(LL cur) {
    int cnt = 0;
    rep (i, n) {
        if (a[i] <= cur) {
            cur -= a[i];
            cnt++;
        }
    }
    return cnt;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        nz = 0; a.clear();
        rep (i, n) {
            LL x; scanf("%lld", &x);
            if (x) a.push_back(x); else nz++;
        }
        n -= nz; m -= nz;
        if (m < 0) {
            puts("Impossible");
            continue;
        }
        if (n == m) {
            puts("Richman");
            continue;
        }
        LL ans = accumulate(a.begin(), a.begin() + m, 0ll);
        ans += *min_element(a.begin() + m, a.begin() + n) - 1;
        if (ans < 0 or check(ans) != m) puts("Impossible");
        else printf("%lld\n", ans);
    }
    return 0;
}