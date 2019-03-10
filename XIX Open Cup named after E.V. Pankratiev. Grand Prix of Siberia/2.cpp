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

#define double long double
double v, d, w;

double check(double ax) {
    double t = (-v+sqrt(v * v + 2 * ax * d)) / ax;
    double ay = 2 * w / t / t;
    return hypot(ax, ay);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%Lf%Lf%Lf", &v, &d, &w); w /= 2.0;
        double aa = v * v / (2 * d);
        double l = -aa, r = 0.0;
        rep (_, 150) {
            double m1 = (2 * l + r) / 3, m2 = (l + 2 * r) / 3;
            if (check(m1) > check(m2)) l = m1; else r = m2;
        }
        printf("%.18Lf\n", min(aa, check((l + r) / 2.0)));
    }
    return 0;
}
