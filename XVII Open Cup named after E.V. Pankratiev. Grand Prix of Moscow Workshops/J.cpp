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

int n, m;
double theta, phi;
const double pi = acos(-1);

LL lcm(LL x, LL y) { return x / __gcd(x, y) * y; }
inline double H(LL n) { return 0.5 / tan(pi / n); }
inline double R(LL n) { return 0.5 / sin(pi / n); }

double dot(cplx a, cplx b) {
    return a.real() * b.real() + a.imag() * b.imag();
}

double check(double th, bool raise = false) {
    int k = fmod(th + pi * 2 + (raise ? phi / 2 : 0), pi * 2) / phi;
    return dot(polar(1.0, th), polar(1.0, k * phi - (raise ? 0 : phi / 2))); 
}

double solve() {
    if (n >= 2e6) return H(n) / H(m);
    double ans1 = 0.0, ans2 = 0.0, ans3 = 0.0;
    rep (i, n) ans1 = max(ans1, check(i * theta + theta / 2, true));
    rep (i, n) ans2 = max(ans2, check(i * theta, true));
    rep (i, n) ans3 = max(ans3, check(i * theta, false));
    cout << ans1 << ' ' << ans2 << ' ' << ans3 << endl;
    return min({ans1, ans2, ans3}) * R(n) / H(m);
}

int main() {
    cin >> n >> m;
    LL w = lcm(n, m);
    double ans = 1.0/(1.0 / R(n) * R(w) / H(w) * H(m));
    printf("%.12f\n", ans);
/*
    theta = 2 * pi / n;
    phi = 2 * pi / m;
    printf("%.12f\n", solve());
    */
    return 0;
}
