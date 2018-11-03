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

typedef complex<double> cplx;

const double PI = acos(-1);

double mod2pi(double x) {
    while (x < 0) x += 2 * PI;
    while (x >= 2 * PI) x -= 2 * PI;
    return x;
}

double work() {
    int n;
    double R;
    scanf("%d%lf", &n, &R);
    vector<double> pos;
    vector<cplx> pts;
    double rho;
    rep (i, n) {
        double x, y, r, d;
        scanf("%lf%lf%lf", &x, &y, &r);
        d = hypot(x, y);
        if (d >= r + R or d <= R - r) continue;
        rho = atan2(y, x);
        double delta = acos((R * R + d * d - r * r) / (2 * R * d));
        pos.push_back(rho - delta);
        pos.push_back(rho + delta);
    }
    if (pos.size() == 0) return 2 * R;
    for (double& theta : pos) {
        theta = mod2pi(theta - rho);
        pts.push_back(polar(R, theta));
    }
    sort(range(pos));
    for (double theta : pos) {
        theta = mod2pi(theta + PI);
        if ((lower_bound(range(pos), theta) - pos.begin()) & 1) return 2 * R;
    }
    double ans = 0.0;
    for (int i = 0; i < pts.size(); i++)
        for (int j = i + 1; j < pts.size(); j++)
            ans = max(ans, abs(pts[i] - pts[j]));
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    Rep (t, T) {
        printf("Case #%d: %.12f\n", t, work());
    }
    return 0;
}
