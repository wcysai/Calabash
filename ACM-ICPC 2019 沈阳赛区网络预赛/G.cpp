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

const double phi = (sqrt(5.) + 1.) / 2.;
double a;
char buf[1 << 20];

double f(double x) {
    if (x == DBL_MAX) return 2;
    return x / (x + 1) + 1;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s %lf", buf, &a);
        double ans;
        if (strlen(buf) > 4) {
            ans = phi;
        } else {
            int n; sscanf(buf, "%d", &n);
            ans = DBL_MAX;
            rep (i, n << 1) ans = f(ans);
        }
        ans *= a;
        printf("%.10f\n", ans);
    }
    return 0;
}
