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

typedef complex<double> pt;

int n;
pt orig;
pt pts[1024];

pt read() {
    int x, y; scanf("%d%d", &x, &y);
    return pt(double(x), double(y));
}

bool degenerate(pt A, pt B) {
    return imag(A * conj(B)) == 0;
}

const double pi = acos(-1);

double fmod2pi(double x) {
    while (x < 0) x += 2 * pi;
    while (x > 2 * pi) x -= 2 * pi;
    return x;
}

double calc(pt A, pt B) {
    if (degenerate(A, B)) return 0.0;
    double a = abs(B);
    double alpha = arg((B - A) / -A), 
           beta = -arg((B - A) / B);
    beta = pi - beta;
    alpha = fmod2pi(alpha); beta = fmod2pi(beta); 
    double ans = a * sin(beta);
    ans *= log(abs(tan(beta / 2) / tan(alpha / 2)));
    return ans;
}

int main() {
    scanf("%d", &n); orig = read();
    rep (i, n) pts[i] = read() - orig;
    double ans = 0.0;
    for (int i = 0; i < n; i++) 
        ans += calc(pts[i], pts[(i+1)%n]);
    printf("%.12f\n", fabs(ans / acos(-1)));
    return 0;
}
