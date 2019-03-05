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
int a[1 << 20], b[1 << 20];

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d", a + i);
    sort(a, a + n);
    iota(b, b + n, 1);
    rep (i, n) {
        if (a[i] > b[i]) {
            puts("impossible");
            return 0;
        }
    }
    double ans = 1.0;
    rep (i, n) ans = min(ans, 1.0 * a[i] / b[i]);
    printf("%.7f\n", ans);
    return 0;
}
