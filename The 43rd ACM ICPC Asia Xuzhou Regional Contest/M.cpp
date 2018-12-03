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

inline int sgn(LL x) {
    if (x == 0) return 0;
    return x > 0 ? 1 : -1;
}

typedef struct pt {
    LL x, y;

    pt operator + (pt a) { return {x + a.x, y + a.y}; }
    pt operator - (pt a) { return {x - a.x, y - a.y}; }
    LL operator * (pt a) { return x * a.y - y * a.x; }
    LL operator , (pt a) { return x * a.x + y * a.y; }
    void read() { scanf("%lld%lld", &x, &y); }
} vec;

int n;
pt poly[5000];

int m;
pt point[1024];

pair<int, int> rmc[4096];

void solve() {
    int ans = INT_MAX;
    vector<int> sol;
    for (int i = n; i < n + n; i++) {
        int cur = i;
        vector<int> sch;
        while (cur < i + n) {
            sch.push_back(rmc[cur].second);
            cur = rmc[cur].first;
            if (cur == 0) {
                puts("-1");
                return;
            }
        }
        if (sch.size() < ans) {
            ans = sch.size();
            sol = sch;
        }
    }
    printf("%d\n", ans);
    rep (i, ans) printf("%d%c", sol[i], i == ans - 1 ? '\n' : ' ');
}

int side(pt p1, pt p2, pt pnt) {
    return sgn((p1 - p2) * (pnt - p2));
}

bool is_key_point(pt pnt, int i) {
    return sgn((poly[i+1] - pnt) * (poly[i] - pnt)) ==
           sgn((poly[i-1] - pnt) * (poly[i] - pnt));
}

pair<int, int> get_illum(pt pnt) {
    vector<int> lsusp;
    for (int i = 1; i <= n; i++)
        if (is_key_point(pnt, i)) lsusp.push_back(i);
    assert(lsusp.size() == 2);

    int p1 = lsusp[0], p2 = lsusp[1], p3 = p1 + n;
    if (p2 == p1 + 1) {
        if (side(poly[p1], poly[p2], poly[p2 + 1]) == side(poly[p1], poly[p2], pnt)) {
            return {p2, p3};
        } else {
            return {p1, p2};
        }
    } else {
        if (side(poly[p1], poly[p2], poly[p1 + 1]) == side(poly[p1], poly[p2], pnt)) {
            return {p1, p2};
        } else {
            return {p2, p3};
        }
    }

}

void work() {
    scanf("%d%d", &n, &m);

    Rep (i, n) {
        poly[i].read();
        poly[i+n] = poly[i+n+n] = poly[i];
    }
    poly[0] = poly[n];

    rep (i, m) point[i].read();

    fill(range(rmc), make_pair(0, 0));
    rep (i, m) {
        int l, r; tie(l, r) = get_illum(point[i]);
        l--; r--;
        _debug("%d: [%d, %d)", i, l, r);
        while (l >= n) {
            l -= n;
            r -= n;
        }
        _debug("%d: [%d, %d)", i, l, r);
        for (int p = l; p < r; p++) rmc[p] = max(rmc[p], make_pair(r, i + 1));
        l += n; r += n;
        for (int p = l; p < r; p++) rmc[p] = max(rmc[p], make_pair(r, i + 1));
        l += n; r += n;
        for (int p = l; p < r; p++) rmc[p] = max(rmc[p], make_pair(r, i + 1));
    }
    solve();
}

int main() {
    int t; scanf("%d", &t);
    while (t--) work();
    return 0;
}
