#pragma GCC optimize(3)
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

int w, h, x[3], xx[3];
typedef complex<double> pt;
pt pts[3];
const double eps = 1e-7;

bool cmp(pt a, pt b) {
    if (a.real() == b.real()) return a.imag() < b.imag();
    return a.real() < b.real();
}

bool valid() {
    for (int i = 0; i < 3; i++) {
        if (pts[i].real() < -eps or pts[i].real() > w + eps) return false;
        if (pts[i].imag() < -eps or pts[i].imag() > h + eps) return false;
    }
    return true;
}

bool valid2() {
    if (fabs(abs(pts[0] - pts[1]) - xx[0]) > eps) return false;
    if (fabs(abs(pts[0] - pts[2]) - xx[1]) > eps) return false;
    if (fabs(abs(pts[1] - pts[2]) - xx[2]) > eps) return false;
    return true;
}

bool attempt() {
    double alpha = acos((x[0] * x[0] + x[2] * x[2] - x[1] * x[1]) / (2.0 * x[0] * x[2]));
    double theta = 0;
    if (x[2] > w) theta = acos(1.0 * w / x[2]);
    pts[0] = 0;
    pts[1] = polar(double(x[2]), theta);
    pts[2] = polar(double(x[0]), theta + alpha);
    return valid();
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &w, &h);
        rep (i, 3) scanf("%d", x + i);
        memcpy(xx, x, sizeof xx);
        sort(range(x));
        bool done = false;
        do {
            if (attempt()) {
                while (!valid2()) next_permutation(range(pts), cmp);
                assert(valid() and valid2());
                for (int i = 0; i < 3; i++)
                    printf("%.12f %.12f ", pts[i].real(), pts[i].imag());
                puts("");
                done = true;
                break;
            }
        } while (next_permutation(range(x)));
        assert(done);
    }
    return 0;
}
}
