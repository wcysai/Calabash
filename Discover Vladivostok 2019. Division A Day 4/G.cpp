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
const LL per = 1'000'000, totper = per * per * 12;
LL x[200005];

LL solve() {
    sort(x, x + n);
    rep (i, n) x[i+n] = x[i] + totper;
    LL cur = 0, ans;
    for (int i = 0; i < n - 1; i++) cur += x[n-1] - x[i];
    ans = cur;
    for (int ptr = n; ptr < n + n; ptr++) {
        cur -= x[ptr] - x[ptr - n];
        cur += n * (x[ptr] - x[ptr-1]);
        ans = min(ans, cur);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    rep (i, n) {
        LL h, m, s; scanf("%lld%lld%lld", &h, &m, &s);
        x[i] = h * per * per + m * per + s;
    }
    LL x = solve();
    LL h = x / (per * per), m = x % (per * per) / per, s = x % per;
    printf("%lld %lld %lld\n", h, m, s);
    return 0;
}
