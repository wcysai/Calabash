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

const int per = 60;
int n, m;
int x[12], y[12], k[12], t[12];
int res[60][60];

int judge(int u, int v) {
    rep (i, n) if ((abs(u - x[i]) + abs(v - y[i])) % k[i] != t[i]) return false;
    return true;
}

LL subsum(int xl, int xr, int yl, int yr) {
    int ans = 0;
    for (int i = xl; i < xr; i++)
        for (int j = yl; j < yr; j++)
            ans += res[i][j];
    return ans;
}

LL subsolve(int xl, int xr, int yl, int yr) {
    memset(res, 0, sizeof res);
    int nx = xr - xl, ny = yr - yl;
    int cx = nx / per, cy = ny / per;
    int rx = nx % per, ry = ny % per;
    rep (i, per) rep (j, per) res[i][j] = judge(xl + i, yl + j);
    LL ans = subsum(0, per, 0, per) * cx * cy;
    ans += subsum(0, rx, 0, per) * cy;
    ans += subsum(0, per, 0, ry) * cx;
    ans += subsum(0, rx, 0, ry);
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m); m++;
        vector<int> xs = {0, m}, ys = {0, m};
        rep (i, n) {
            scanf("%d%d%d%d", x + i, y + i, k + i, t + i);
            xs.emplace_back(x[i]);
            ys.emplace_back(y[i]);
        }
        sort(range(xs)); xs.erase(unique(range(xs)), xs.end());
        sort(range(ys)); ys.erase(unique(range(ys)), ys.end());
        LL ans = 0;
        rep (i, xs.size() - 1) rep (j, ys.size() - 1)
            ans += subsolve(xs[i], xs[i+1], ys[j], ys[j+1]);
        printf("%lld\n", ans);
    }
    return 0;
}
