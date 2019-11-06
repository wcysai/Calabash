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

double R, l, w;
typedef complex<double> pt;
typedef pair<pt, pt> seg;

double operator , (pt a, pt b) {
    return real(a) * real(b) + imag(a) * imag(b);
}

double operator * (pt a, pt b) {
    return real(a) * imag(b) - imag(a) * real(b);
}

double distance(pt p, seg S) {
    pt s, t; tie(s, t) = S;
    if ((p - s, t - s) <= 0) return abs(p - s);
    if ((p - t, s - t) <= 0) return abs(p - t);
    return abs((s - p) * (t - p)) / abs(s - t);
}

pt A[3], B[4];

int main() {
    scanf("%lf%lf%lf", &R, &l, &w);
    int T; scanf("%d", &T);
    while (T--) {
        double a, b; scanf("%lf%lf", &a, &b);
        B[0] = pt(0.0, w);
        B[1] = -conj(polar(l, b)) + pt(l, 0.0);
        B[2] = pt(l, 0.0);
        B[3] = pt(l + l, 0.0);
        A[0] = -conj(polar(l, a)) + pt(l, w);
        A[1] = pt(l, w);
        A[2] = pt(l + l, w);
#ifdef __LOCAL_DEBUG__
        rep (i, 3) cerr << A[i] << ' '; cerr << endl;
        rep (i, 3) cerr << B[i] << ' '; cerr << endl;
#endif  
        double ans = min(w, R * 2.0);
        rep (i, 2) rep (j, 4) ans = min(ans, distance(B[j], make_pair(A[i], A[i+1])));
        for (int i = 1; i < 3; i++) rep (j, 3) 
            ans = min(ans, distance(A[j], make_pair(B[i], B[i+1])));
        printf("%.12f\n", ans / 2.0);
    }
    return 0;
}
