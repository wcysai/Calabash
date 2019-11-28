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
LL L, U;
LL a[100005];

pair<LL, LL> operator + (pair<LL, LL> a, pair<LL, LL> b) {
    if (b.first >= a.second) return make_pair(b.first, b.first);
    if (b.second <= a.first) return make_pair(b.second, b.second);
    return make_pair(max(a.first, b.first), min(a.second, b.second));
}

const int MAXN = 4 * 1000005;
struct segtree {
    int l[MAXN], m[MAXN], r[MAXN];
    pair<LL, LL> val[MAXN];

#define lson (o<<1)
#define rson (o<<1|1)

    void pull(int o) { val[o] = val[lson] + val[rson]; }

    void build(int o, int ll, int rr) {
        int mm = (ll + rr) / 2;
        l[o] = ll; r[o] = rr; m[o] = mm;
        if (ll == mm) {
            val[o] = make_pair(L - a[mm], U - a[mm]);
        } else {
            build(lson, ll, mm);
            build(rson, mm, rr);
            pull(o);
        }
    }

    pair<LL, LL> query(int o, int ll, int rr) {
        if (ll <= l[o] and r[o] <= rr) {
            return val[o];
        } else {
            if (rr <= m[o]) return query(lson, ll, rr);
            if (ll >= m[o]) return query(rson, ll, rr);
            return query(lson, ll, rr) + query(rson, ll, rr);
        }
    }
} seg;

int main() {
    scanf("%d", &n); scanf("%lld%lld\n", &L, &U);
    Rep (i, n) scanf("%lld", a + i);
    partial_sum(a + 1, a + n + 1, a + 1);
    seg.build(1, 1, n + 1);
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; LL num; scanf("%d%d%lld", &l, &r, &num);
        num -= a[l-1];
        LL left, right; tie(left, right) = seg.query(1, l, r + 1);
        if (num < left) num = left;
        if (num > right) num = right;
        num += a[r];
        printf("%lld\n", num);
    }
    return 0;
}
