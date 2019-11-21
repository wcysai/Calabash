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

int readint() {
    double x; scanf("%lf", &x);
    return lround(x * 100);
}

int main() {
    int t[4]; rep (i, 4) t[i] = readint();
    int target = readint() * 3;
    sort(range(t));
    if (t[0] + t[1] + t[2] > target) {
        puts("impossible");
    } else if (t[1] + t[2] + t[3] <= target) {
        puts("infinite");
    } else {
        printf("%.2f\n", (target - t[1] - t[2]) / 100.);
    }
    return 0;
}

