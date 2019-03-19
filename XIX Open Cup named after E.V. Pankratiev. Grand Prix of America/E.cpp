#pragma GCC optimize(3)
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

int r, c;
int g[24][24];

#define for_mask(i, mask) \
    for (int m = mask, i = __builtin_ctz(m); m; m &= m - 1, i = __builtin_ctz(m))

int dp[24][1500000];
int cmask[24][24];
bool cansel[24];

bool can_selc(int rowmask, int c) {
    int idl[24], sz = 0;
    for_mask(i, rowmask) idl[sz++] = g[i][c];
    bool inc = true, dec = true;
    for (int i = 1; i < sz; i++) {
        inc &= idl[i] > idl[i - 1];
        dec &= idl[i] < idl[i - 1];
    }
    return inc or dec;
}

int compute_weight(int c1, int c2) {
    int mask = 0;
    for (int i = r - 1; i >= 0; i--) {
        mask = mask << 1;
        if (g[i][c1] < g[i][c2]) mask |= 1;
    }
    return mask;
}

LL ans = 0;

int main() {
    scanf("%d%d", &r, &c);
    rep (i, r) rep (j, c) scanf("%d", &g[i][j]);
    rep (j, c) rep (i, j) cmask[i][j] = compute_weight(i, j);
    for (int mask = 1; mask < (1 << r); mask++) {
        rep (i, c) ans += (cansel[i] = can_selc(mask, i)); 
        rep (i, c) if (cansel[i]) for (int j = i + 1; j < c; j++) if (cansel[j]) {
            int smask = cmask[i][j] & mask;
            dp[j][smask] += dp[i][smask] + 1;
        }
        rep (i, c) if (cansel[i]) for (int j = i + 1; j < c; j++) if (cansel[j]) {
            int smask = cmask[i][j] & mask;
            ans += dp[j][smask];
            dp[j][smask] = 0;
        }
    }
    cout << ans << endl;
    return 0;
}
