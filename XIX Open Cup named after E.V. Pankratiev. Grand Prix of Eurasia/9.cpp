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

int n;

pair<int, int> operator + (pair<int, int> l, pair<int, int> r) {
    return {l.first + r.first, (l.second + r.second) % n};
}

const int MAXN = 15000000;
LL R, S;

struct segtree {
    int lptr[MAXN], rptr[MAXN];
    int val1[MAXN], val2[MAXN];

    int alloc() {
        static int ptr = 1;
        return ptr++;
    }

    int left(int o) {
        if (lptr[o]) return lptr[o];
        else return lptr[o] = alloc();
    }

    int right(int o) {
        if (rptr[o]) return rptr[o];
        else return rptr[o] = alloc();

    }

    pair<int, int> query(int o, LL pos, LL l, LL r) {
        LL m = (l + r) / 2;
        pair<int, int> ans = {val1[o], val2[o]};
        if (l == m) return ans;
        if (pos < m and lptr[o]) ans = ans + query(lptr[o], pos, l, m);
        if (pos >= m and rptr[o]) ans = ans + query(rptr[o], pos, m, r);
        return ans;
    }

    void add(int o, LL l, LL r, LL ll, LL rr, int id) {
        if (ll <= l && r <= rr) {
            val1[o]++;
            val2[o] = (val2[o] + id) % n;
        } else {
            LL m = (l + r) / 2;
            if (m > ll) add(left(o), l, m, ll, rr, id);
            if (m < rr) add(right(o), m, r, ll, rr, id);
        }
    }
} seg;

LL scale(double x) {
     return llround(x * 1000000.0);
}

void do_range(LL c, LL r) {
    static int cnt = 0;
    c = (c + S) % R;
    LL ll = max(0ll, c - r), rr = min(R, c + r + 1);
    _debug("c=%lld, r=%lld, S=%lld [%lld, %lld]", c, r, S, ll, rr);
    seg.add(0, 0, R, ll, rr, cnt++);
}

void do_point(LL x) {
    x = (x + S) % R;

    auto ans = seg.query(0, x, 0, R);
    _debug("%lld S = %lld, {%d, %d}", x, S, ans.first, ans.second);
    S = (S + ans.second * 1000000ll) % R;
    printf("%d\n", ans.first);
}

int main(){
    scanf("%d", &n);
    R = n * 1000000ll;
    rep (i, 2*n) {
        int op; double x, y;
        scanf("%d", &op);
        if (op == 0) { // interval;

            scanf("%lf%lf", &x, &y);
            _debug("[%.8f, %.8f]", x, y);
            do_range(scale(x), scale(y));
        } else { // point
            scanf("%lf", &x);
            _debug("%lf", x);
            do_point(scale(x));
        }
    }
    return 0;
}
