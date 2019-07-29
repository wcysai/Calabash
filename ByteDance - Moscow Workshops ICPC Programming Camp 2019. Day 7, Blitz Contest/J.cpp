#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n;
int x[100005], y[100005], dx, dy;

int main() {
    while (scanf("%d%d%d", &n, &dx, &dy), n) {
        rep (i, n) scanf("%d%d", x + i, y + i);
        int ans = INT_MAX;
        rep (i, n) ans = min(ans, max(abs(dx - x[i]), abs(dy - y[i])));
        printf("%d\n", ans);
    }
    return 0;
}
