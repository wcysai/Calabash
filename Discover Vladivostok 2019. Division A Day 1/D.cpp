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

int n;
int x[1 << 20], y[1 << 20];

double calc(int x1, double y1, int x2, double y2) {
    if (x1 == x2) return 0.0;
    double rat = (y2 - y1) / (x2 - x1);
    if (x1 % 2) x1++, y1+=rat;
    if (x2 % 2) x2++, y2+=rat;
    double area = (y2 + y1) * (x2 - x1) / 2.0;
    area -= (x2 - x1) * rat / 2.0 ;
    area /= 2.0;
    
    return area;
}

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d%d", x + i, y + i), swap(x[i], y[i]);
    double ans = 0.0;
    rep (i, n) ans += calc(x[i], y[i], x[(i+1)%n], y[(i+1)%n]);
    printf("%.12f\n", fabs(ans));
    return 0;
}
