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

struct pt {
    int x, y;
    pt (int x = 0, int y = 0) : x(x), y(y) {}
    pt operator - (pt a) { return {x - a.x, y - a.y}; }
    int operator * (pt a) { return x * a.y - y * a.x; }
};

vector<pt> make_hull(vector<pt> pts) {
    sort(range(pts), [] (pt a, pt b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    int k = 0;
    vector<pt> ret(pts.size() * 2);
    rep (i, pts.size()) {
        while (k > 1 and (ret[k-1] - ret[k-2]) * (pts[i] - ret[k-1]) < 0) k--;
        ret[k++] = pts[i];
    }
    for (int i = pts.size() - 2, t = k; i >= 0; i--) {
        while (k > t and (ret[k-1] - ret[k-2]) * (pts[i] - ret[k-1]) < 0) k--;
        ret[k++] = pts[i];
    }
    ret.resize(k - 1);
    return ret;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n; vector<pt> pts;
        scanf("%d", &n);
        rep (i, n) {
            int x, y; scanf("%d%d", &x, &y);
            pts.emplace_back(x, y);
        }
        int nhull = make_hull(pts).size();
        _debug("hull size: %d, total size: %d", nhull, n);
        puts((n - nhull) & 1 ? "OwO" : "T^T");
    }
    return 0;
}
