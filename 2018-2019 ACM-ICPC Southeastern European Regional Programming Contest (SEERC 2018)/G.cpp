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

enum { WHITE = 1, BLACK = 2, MIX = 3 };

int n;
LL tot;

struct segtree {
    int value[1 << 22];
    int l[1 << 22], m[1 << 22], r[1 << 22];
    int cnt[22][4];

#define lson (o<<1)
#define rson (o<<1|1)

    void pull(int o, int dep) {
        cnt[dep][value[o]]--;
        value[o] = value[lson] | value[rson];
        cnt[dep][value[o]]++;
    }

    void build(int o, int ll, int rr, int dep) {
        int mm = (ll + rr) / 2;
        l[o] = ll; r[o] = rr; m[o] = mm;
        value[o] = WHITE;
        if (dep == 0) return;
        else {
            build(lson, ll, mm, dep - 1);
            build(rson, mm, rr, dep - 1);
            cnt[dep][WHITE]++;
        }
    }

    void modify(int o, int x, int dep) {
        if (dep == 0) {
            value[o] = 3 - value[o];
            return;
        } else {
            if (x < m[o]) modify(lson, x, dep - 1);
            else modify(rson, x, dep - 1);
            pull(o, dep);
        }
    }
} srow, scol;

LL query() {
    LL ans = 0;
    Rep (i, n) ans += 1ll * (srow.cnt[i][1] + srow.cnt[i][2]) * (scol.cnt[i][1] + scol.cnt[i][2]);
    return tot - ans * 4;
}

int main() {
    int q; scanf("%d%d", &n, &q);
    for (int i = 0; i <= n; i++) tot += 1ll * (1 << i) * (1 << i);
    srow.build(1, 1, (1 << n) + 1, n);
    scol.build(1, 1, (1 << n) + 1, n);
    while (q--) {
        int t, x; scanf("%d%d", &t, &x);
        if (t) srow.modify(1, x, n);
        else scol.modify(1, x, n);
        printf("%" PRId64 "\n", query());
    }
    return 0;
}
