#pragma GCC optimize(3)
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

const int INF = INT_MAX / 2;
int n, m, k, sz;
int x[20], y[20];
int id[20][20];
int gain[20][20];

int dp[1 << 18];
int emask[20][20];

void update(int& x, int y) { x = max(x, y); }

unsigned genmask(int from, int to) {
    unsigned mask = 0;
    int x = ::x[from], y = ::y[from], xt = ::x[to], yt = ::y[to];
    while (x != xt) {
        if (x < xt) x++; else x--;
        if (id[x][y] >= 0) mask |= 1 << id[x][y];
    }
    while (y != yt) {
        if (y < yt) y++; else y--;
        if (id[x][y] >= 0) mask |= 1 << id[x][y];
    }
    mask &= ~(1 << from);
    mask &= ~(1 << to);
    return mask;
}

void prep() {
    memset(emask, 0, sizeof emask);
    rep (i, sz) rep (j, sz) emask[i][j] = genmask(i, j);
}

int work() {
    fill(range(dp), -INF); dp[0] = 0;
    for (int mask = 0; mask < (1 << sz); mask++) if (!(__builtin_popcount(mask) & 1)) {
        rep (i, sz) if (~mask & (1 << i)) rep (j, i) if (~mask & (1 << j)) {
            if ((mask & emask[i][j]) == emask[i][j] || (mask & emask[j][i]) == emask[j][i])
                update(dp[mask | (1 << i) | (1 << j)], dp[mask] + gain[i][j]);
        }
    }
    return dp[(1<<sz)-1];
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        sz = 0; memset(id, -1, sizeof id);
        string attr[20];
        rep (i, n) rep (j, m) {
            char buf[6]; scanf("%s", buf);
            if (buf[0] == '-') {
                id[i][j] = -1;
                continue;
            }
            attr[sz] = buf;
            x[sz] = i; y[sz] = j;
            id[i][j] = sz++;
        }
//        rep (i, n) { rep (j, m) printf("%d ", id[i][j]); puts(""); }
        assert(~sz & 1); assert(sz <= 18);
        int s[6];
        rep (i, k + 1) scanf("%d", s + i);
        rep (i, sz) rep (j, sz) {
            int g = 0;
            rep (p, k) g += bool(attr[i][p] == attr[j][p]);
            gain[i][j] = s[g];
        }
        prep();
        printf("%d\n", work());
    }
    return 0;
}
