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
typedef double dbl;

class Line {
    dbl k, b;

public:
    Line(dbl k, dbl b) : k(k), b(b) {}
    Line(dbl k, dbl x, dbl y) : k(k), b(-k*x+y) {}
    Line(dbl x1, dbl y1, dbl x2, dbl y2) : k((y2-y1)/(x2-x1)), b(-k*x1+y1) {}

    dbl operator () (dbl x) const {
        return k * x + b;
    }
};

template <typename T>
dbl findzero(T fn, double l, double r) {
    if (fn(r) <= 0.0) throw 0;
    rep (_, 100) {
        double mid = (l + r) / 2;
        if (fn(mid) < 0) l = mid; else r = mid;
    }
    return (l + r) / 2;
}

int check(dbl l, dbl r, dbl delta) {
    int cnt = 0;
    try {
        dbl x = l, y = log(x) + delta;
        while (true) {
            cnt++;
            dbl x0 = findzero([delta, x0 = x, y0 = y] (dbl x) {
                return (log(x) - delta - y0) / (x - x0) - 1.0 / x;
            }, x, r);
            x = findzero([delta, line = Line(1.0 / x0, x0, log(x0) - delta)] (dbl x) {
                return line(x) - log(x) - delta;
            }, x0, r);
            y = log(x) + delta;
        }
    } catch (...) {
        return cnt;
    }
}

dbl solve(int n, dbl a, dbl b) {
    dbl l = 0.0, r = 1e5;
    rep (_, 100) {
        dbl mid = (l + r) / 2;
        if (check(a, b, mid) > n) l = mid;
        else r = mid;
    }
    return (l + r) / 2;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; dbl a, b, c; cin >> n >> c >> a >> b;
        cout << setprecision(12) << c * solve(n, a, b) << endl;
    }
    return 0;
}
