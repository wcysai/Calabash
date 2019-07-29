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

bool pos, neg;
int a[3];

int main() {
    rep (i, 3) scanf("%d", a + i);
    rep (i, 3) {
        if (a[i] > 0) pos = true;
        if (a[i] < 0) neg = true;
        a[i] = abs(a[i]);
    }
    int x = __gcd(a[0], __gcd(a[1], a[2]));
    if (x == 0) {
        cout << 0 << endl;
        return 0;
    }
    double ans = 0.5 / x;
    if (pos and neg) ans *= 2;
    printf("%.12f\n", ans);
    return 0;
}
