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
typedef long double db;

int n, k;

db compute(LL i) {
    db ans = 0;
    if ((1 << i) > k) return 0;
    Rep (I, (1 << i) - 1) {
        ans += logl(k - I) - logl((1 << n) - I);
    }
    return expl(ans);
}

int main() {
    cin >> n >> k;
    k = (1<<n) + 1 - k;
    _debug("%d", k);
    db ans = 0.0;
    rep (i, n) ans += compute(i);
    printf("%.15Lf\n", ans);
    return 0;
}
