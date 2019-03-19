#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL; 

int n, k;
double x[2560], y[2560];
double logi[2560], logfact[2560];
double pd[2560];

double logcomb(int x, int y) {
    return logfact[x] - logfact[y] - logfact[x - y];
}

double area(int i, int j) {
    return y[j] * x[i] - y[i] * x[j];
}

int main() {
    scanf("%d%d", &n, &k);
    Rep (i, n) logi[i] = log(i);
    partial_sum(logi, logi + n + 1, logfact);
    for (int i = 1; n - i >= k - 1; i++) 
        pd[i] = exp(logcomb(n - i, k - 1) - logcomb(n - 1, k - 1));
    for (int i = 1; n - i >= k - 1; i++) 
        pd[i] -= pd[i + 1];
    rep (i, n) scanf("%lf%lf", x + i, y + i);
    double ans = 0.0;
    for (int i = 0; i < n; i++) 
        for (int j = 1; n - j >= k - 1; j++) 
            ans += pd[j] * area(i, (j + i) % n);
    ans /= -2.0;
    printf("%.9f\n", ans * k / n);
    return 0;
}
