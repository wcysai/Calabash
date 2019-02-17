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
typedef long long LL;
const int MAXN = 256;
typedef bitset<MAXN> bs;

struct point {
    int x, y;

    int operator * (point a)  { return x * a.y - y * a.x; }
    point operator - (point a) { return {x - a.x, y - a.y}; }
};

int n;
point pt[256];
bs dir[256][256];
LL ans = 0;

int solve(int i, int j, int k) {
    if ((pt[j] - pt[i]) * (pt[k] - pt[i]) < 0) swap(i, j);
    int d = (dir[i][j] & dir[j][k] & dir[k][i]).count();
    //_debug("i=%d, j=%d, k=%d, d=%d", i, j, k, d);
    //cout << dir[i][j] << ' ' << dir[j][k] << ' ' << dir[k][i] << endl;
    return d * (d - 1) / 2;
}

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d%d", &pt[i].x, &pt[i].y);
    rep (i, n) rep (j, n) rep (k, n) 
        if ((pt[j] - pt[i]) * (pt[k] - pt[i]) > 0) dir[i][j].set(k);
//    rep (i, n) rep (j, n) cout << dir[i][j] << endl;
    rep (i, n) rep (j, n) {
        LL c = dir[i][j].count(), d = n - 2 - c;
//        cout << c << ' ' << d << endl;
        ans += c * (c - 1) / 2 * d;
    }
    //cout << ans << endl;
    rep (i, n) rep (j, i) rep (k, j) ans += solve(i, j, k);
    cout << ans << endl;
    return 0;
}
