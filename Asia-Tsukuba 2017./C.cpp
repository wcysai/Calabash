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
LL t;
LL h[100005];
LL psum[100005], pmax[100005];

int main() {
    scanf("%d%lld", &n, &t);
    rep (i, n) scanf("%lld", h + i);
    partial_sum(h, h + n, psum);
    partial_sum(h, h + n, pmax, [] (LL a, LL b) -> LL { return max(a, b); });
    rep (i, n) {
        LL done = 1;
        LL cur = t - psum[i];
        if (cur >= 0) {
            done += cur / pmax[i] + 1;
        }
        printf("%lld\n", done);
    }
    return 0;
}
