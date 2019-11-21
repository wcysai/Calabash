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

int n, k;
double p[512], q[512], r[512];

int main() {
    scanf("%d%d", &n, &k);
    rep (i, n) scanf("%lf", p + i);
    reverse(p, p + n);
    q[0] = 1. * k / n;
    for (int i = 1; n - i != k - 1; i++) q[i] = q[i-1] * (1. - 1. * (k - 1) / (n - i));
    rep (i, n) rep (j, n) r[i] += p[(i+j)%n] * q[j];
    reverse(r, r + n);
    rep (i, n) printf("%.9f ", r[i]);
    return 0;
}
