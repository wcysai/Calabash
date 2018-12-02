#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(fmt, ...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;
#define PROBLEM "elegant"

LL p[3][5] = {
    {2, 3, 5, 7, 11}, 
    {13, 17, 19, 23, 29}, 
    {31, 37, 41, 43, 47}
};
LL pp[3][32];

void precalc() {
    for (unsigned mask = 0; mask < (1 << 5); mask++) {
        rep (i, 3) pp[i][mask] = 1;
        for (int d = 0; d < 5; d++) 
            if (mask & (1 << d)) 
                rep (i, 3)
                    pp[i][mask] *= p[i][d];
    }
}

int n;
LL ans[32][32];

int main() {
    #ifndef __LOCAL_DEBUG__
    freopen(PROBLEM ".in", "r", stdin);
    freopen(PROBLEM ".out", "w", stdout);
    #endif
    precalc();
    scanf("%d", &n);
    rep (i, n) rep (j, n) {
        ans[i][j] = pp[0][(i+j)%n] * pp[1][(i-j+n)%n];
    }
    if (n % 2 == 0) {
        int m = n / 2;
        rep (i, m) {
            rep (j, m) {
                ans[i][j] *= pp[2][(i-j+m)%m];
                ans[i+m][j] *= pp[2][(i-j+m)%m];
                ans[i+m][j+m] *= pp[2][(i-j+1+m)%m];
                ans[i][j+m] *= pp[2][(i-j+1+m)%m];
            }
        }
    }
    rep (i, n) {
        rep (j, n) {
            printf("%lld ", ans[i][j]);
        }
        puts("");
    }
    return 0;
}
