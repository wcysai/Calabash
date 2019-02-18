#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debuf(...) ((void) 0)
#endif
typedef long long LL;

int n;

struct pt {
    LL x, y;
    pt operator - (pt rhs) { return {x - rhs.x, y - rhs.y}; }
    LL operator * (pt rhs) { return x * rhs.y - y * rhs.x; }
    LL norm() { return x * x + y * y; }
    double arg() { return atan2(double(y), double(x)); }
};

pt pts[2048];
LL ans = LLONG_MAX;

inline void update(int i, int j, int k) {
    LL cur = (pts[i] - pts[j]) * (pts[k] - pts[j]);
    if (cur) ans = min(ans, abs(cur));
}

vector<tuple<LL, int, int>> cand;
int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%lld%lld", &pts[i].x, &pts[i].y);

    rep (i, n) rep (j, i) rep (k, j) update(i, j, k);
    printf("%.2f\n", ans / 2.0);
    return 0;

    rep (i, n) rep (j, i) 
        cand.emplace_back((pts[i] - pts[j]).norm(), i, j);
    sort(range(cand));
    int cnt = 0;
    for (auto& p : cand) {
        if (++cnt > 400000) break;
        int i, j; tie(ignore, i, j) = p;
        rep (k, n) update(i, j, k);
    }
    rep (i, n) {
        vector<pair<double, int>> cd;
        rep (j, n) 
            cd.emplace_back((pts[j] - pts[i]).arg(), j);
        sort(range(cd));
        rep (j, n)
            for (int d = 0; d < 10; d++)
                update(i, cd[j].second, cd[(j+d)%n].second); 
    }

    printf("%.2f\n", ans / 2.0);
    return 0;
}
