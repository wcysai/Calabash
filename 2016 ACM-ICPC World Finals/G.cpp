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

const int MAXN = 2048;
int n;
int x1[MAXN], x2[MAXN], y[MAXN];

struct frac {
    LL x, y;
    
    LL operator < (const frac &a) const { return x * a.y < a.x * y; }
};

LL work(int cx, int cy) {
    vector<pair<frac, int>> op;
    rep (i, n) {
        if (y[i] == cy) continue;
        if (y[i] > cy) {
            op.emplace_back(frac{x1[i] - cx, y[i] - cy}, -x2[i] + x1[i]);
            op.emplace_back(frac{x2[i] - cx, y[i] - cy}, -x1[i] + x2[i]);
        } else {
            op.emplace_back(frac{cx - x2[i], cy - y[i]}, -x2[i] + x1[i]);
            op.emplace_back(frac{cx - x1[i], cy - y[i]}, -x1[i] + x2[i]);
        }
    }
    sort(range(op));
    LL cur = 0, ans = 0;
    for (const auto &p : op) {
        cur -= p.second;
        ans = max(ans, cur);
    }
    _debug("%d %d %lld", cx, cy, ans);
    return ans;
}

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d%d%d", x1 + i, x2 + i, y + i);
    rep (i, n) if (x1[i] > x2[i]) swap(x1[i], x2[i]);
    LL ans = 0;
    rep (i, n) ans = max(ans, x2[i] - x1[i] + max(work(x1[i], y[i]), work(x2[i], y[i])));
    cout << ans << endl;
    return 0;
}
