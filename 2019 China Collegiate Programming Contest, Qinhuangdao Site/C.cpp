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

const int p = 998244353;

int nmod(int x) {
    if (x < 0) x += p;
    return x;
}

int pmod(int x) {
    if (x >= p) x -= p;
    return x;
}

struct psum2d {
    int val[5120][5120], psum[5120][5120];

    int operator() (int xl, int xr, int yl, int yr) {
        LL ret = 0ll + psum[xr][yr] - psum[xl][yr] -
            psum[xr][yl] + psum[xl][yl];
        while (ret < 0) ret += p;
        while (ret >= p) ret -= p;
        return ret;
    }

    void update(int i, int j, int v) {
        val[i][j] = v;
        LL sum = 0ll + psum[i][j+1] + psum[i+1][j] - psum[i][j] + v;
        while (sum < 0) sum += p;
        while (sum >= p) sum -= p;
        psum[i+1][j+1] = sum;
    }
} eq, gt;

struct sequence {
    int size;
    int val[5120], pre[5120];
    int last[128];
        // len   pos
    int dp[5120][5120], psum[5120][5120];

    void init(int n) {
        size = n;
        Rep (i, n) {
            scanf("%d", val + i);
            pre[i] = last[val[i]];
            _debug("pre[%d]=%d", i, pre[i]);
            last[val[i]] = i;
        }
        Rep (i, n) psum[0][i] = 1;
        Rep (len, n) Rep (i, n) {
            dp[len][i] = nmod(psum[len-1][i] - psum[len-1][pre[i]]);
            psum[len][i+1] = pmod(psum[len][i] + dp[len][i]);
        }
        Rep (i, size) _debug("dp[%d][n]=%d", i, psum[i][size+1]);
    }

    int operator[] (int x) { return val[x]; }
} a, b;

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    a.init(n); b.init(m);
    eq.update(0, 0, 1);
    Rep (i, n) eq.update(i, 0, 0);
    Rep (i, m) eq.update(0, i, 0);
    Rep (i, n) Rep (j, m) {
        if (a[i] == b[j]) eq.update(i, j, eq(a.pre[i], i, b.pre[j], j));
        else eq.update(i, j, 0);
        int vg = gt(a.pre[i], i, b.pre[j], j);
        if (a[i] > b[j])
            vg = pmod(vg + eq(a.pre[i], i, b.pre[j], j));
        gt.update(i, j, vg);
    }
    LL ans = gt.psum[n+1][m+1];
    Rep (i, n) Rep (j, i - 1) ans += 1ll * a.psum[i][n+1] * b.psum[j][m+1] % p;
    cout << ans % p << endl;
    return 0;
}
