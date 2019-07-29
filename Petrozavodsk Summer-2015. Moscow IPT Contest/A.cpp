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

int n, nx, ny;
vector<int> xs, ys;
vector<pair<int, int>> pts;

typedef bitset<51200> bset;

constexpr int BLOCKSZ = 1024;
struct solver {
    vector<pair<int, int>> ps;
    bset bs[64][64];
    
    void construct(const vector<pair<int, int>>& pts) {
        ps = pts;
        sort(range(ps));
        for (int i = 0; i < 52; i++) {
            for (int j = i + 1; j < 52; j++) {
                bs[i][j] = bs[i][j-1];
                for (int cur = (j-1) << 10; cur < j << 10; cur++) {
                    if (cur >= ps.size()) break;
                    bs[i][j].set(ps[cur].second);
                }
            }
        }
    }
    
    bset buf;
    void prepare(int l, int r) {
        int lid = (l + BLOCKSZ - 1) / BLOCKSZ, rid = r / BLOCKSZ;
        if (lid >= rid) {
            buf.reset();
            for (int i = l; i < r; i++) {
                buf.set(ps[i].second);
            }
        } else {
            buf = bs[lid][rid];
            for (int i = l; i < lid * BLOCKSZ; i++) 
                buf.set(ps[i].second);
            for (int i = rid * BLOCKSZ; i < r; i++) 
                buf.set(ps[i].second);
        }
    }

    int query(int lx, int rx, int ly, int ry) {
        lx = lower_bound(range(ps), make_pair(lx, INT_MIN)) - ps.begin();
        rx = lower_bound(range(ps), make_pair(rx, INT_MIN)) - ps.begin();
        prepare(lx, rx);
        bset mask; mask.set();
        mask >>= mask.size() - (ry - ly);
        mask <<= ly;
        return (buf & mask).count();
    }
} svx, svy;

pair<int, int> query_wrapper(int x1, int x2, int y1, int y2) {
    x2++; y2++;
    x1 = lower_bound(range(xs), x1) - xs.begin();
    x2 = lower_bound(range(xs), x2) - xs.begin();
    y1 = lower_bound(range(ys), y1) - ys.begin();
    y2 = lower_bound(range(ys), y2) - ys.begin();
    return { svy.query(y1, y2, x1, x2), svx.query(x1, x2, y1, y2) };
}

int main() {
    scanf("%d", &n);
    rep (_, n) {
        int x, y;
        scanf("%d%d", &x, &y);
        pts.emplace_back(x, y);
        xs.emplace_back(x);
        ys.emplace_back(y);
    }
    sort(range(xs)); xs.erase(unique(range(xs)), xs.end()); nx = xs.size();
    sort(range(ys)); ys.erase(unique(range(ys)), ys.end()); ny = ys.size();
    for (auto& p : pts) {
        int x, y; tie(x, y) = p;
        x = lower_bound(range(xs), x) - xs.begin();
        y = lower_bound(range(ys), y) - ys.begin();
        p = make_pair(x, y);
    }
    svx.construct(pts);
    for (auto& p : pts) swap(p.first, p.second);
    svy.construct(pts);
    int q; scanf("%d", &q);
    while (q--) {
        int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int ansx, ansy;
        tie(ansx, ansy) = query_wrapper(x1, x2, y1, y2);
        printf("%d %d\n", ansx, ansy);
        fflush(stdout);
    }
    return 0;
}
