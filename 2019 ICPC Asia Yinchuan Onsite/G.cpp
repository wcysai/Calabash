#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <= int(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 4 * 100005;
struct segtree {
    int l[MAXN], m[MAXN], r[MAXN];
    int val[MAXN], tag[MAXN];

#define lson (o<<1)
#define rson (o<<1|1)

    void pull(int o) { val[o] = max(val[lson], val[rson]); }

    void push_add(int o, int x) {
        val[o] += x;
        tag[o] += x;
    }

    void push(int o) {
        if (l[o] == r[o]) return;
        if (tag[o]) {
            push_add(lson, tag[o]);
            push_add(rson, tag[o]);
            tag[o] = 0;
        }
    }

    void build(int o, int ll, int rr) {
        int mm = (ll + rr) / 2;
        l[o] = ll; r[o] = rr;  m[o] = mm;
        if (ll < mm) {
            build(lson, ll, mm);
            build(rson, mm, rr);
        }
    }

    void add(int o, int ll, int rr, int x) {
        if (ll <= l[o] and r[o] <= rr) {
            push_add(o, x);
        } else {
            push(o);
            if (m[o] > ll) add(lson, ll, rr ,x);
            if (m[o] < rr) add(rson, ll, rr, x);
            pull(o);
        }
    }

    int query(int o, int ll, int rr) {
        if (ll <= l[o] and r[o] <= rr) {
            return val[o];
        } else {
            push(o);
            if (rr <= m[o]) return query(lson, ll, rr);
            if (ll >= m[o]) return query(rson, ll, rr);
            return max(query(lson, ll, rr), query(rson, ll, rr));
        }
    }
} tr[4]; // 0:2, 1:3, 2:5, 3:7

int n, q;

int main() {
    scanf("%d%d", &n, &q);
    rep (i, 4) tr[i].build(1, 0, n);
    while (q--) {
        char op[12];
        int l, r, x; scanf("%s%d%d", op, &l, &r); l--;
        if (op[1] == 'U') { // mult
            scanf("%d", &x);
            if (x == 2) {
                tr[0].add(1, l, r, 1);
            } else if (x == 3) {
                tr[1].add(1, l, r, 1);
            } else if (x == 4) {
                tr[0].add(1, l, r, 2);
            } else if (x == 5) {
                tr[2].add(1, l, r, 1);
            } else if (x == 6) {
                tr[0].add(1, l, r, 1);
                tr[1].add(1, l, r, 1);
            } else if (x == 7) {
                tr[3].add(1, l, r, 1);
            } else if (x == 8) {
                tr[0].add(1, l, r, 3);
            } else if (x == 9) {
                tr[1].add(1, l, r, 2);
            } else if (x == 10) {
                tr[0].add(1, l, r, 1);
                tr[2].add(1, l, r, 1);
            } else assert(0);
        } else {    // query
            int ans = 0;
            rep (i, 4) ans = max(ans, tr[i].query(1, l, r));
            printf("ANSWER %d\n", ans);
        }
    }
    return 0;
}
