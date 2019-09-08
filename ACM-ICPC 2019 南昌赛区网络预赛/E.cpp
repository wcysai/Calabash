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

LL n, m;

inline LL countfill(LL l, LL r) {
    return (r + m - 1) / m - (l + m - 1) / m;
}

LL solve(LL k, LL l, LL r) {
    _debug("%lld [%lld, %lld)", k, l, r);
    if (k % m == 0) return k / m;
    LL etot = r - l - countfill(l, r);
    LL ebefore = k - l - countfill(l, k);
    return solve(r + ebefore, r, r + etot);
}

LL Solve(LL k) {
    LL ans = solve(k, 0, n);
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &n, &m); m++;
        int q; scanf("%d", &q);
        while (q--) {
            LL k; scanf("%lld", &k);
            printf("%lld\n", Solve(k - 1) + 1);
        }
    }
    return 0;
}
