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

struct segtree {
    int l[1 << 22], m[1 << 22], r[1 << 22];
    struct data {
        int l, r;
        LL end, sum;

        void init(int pos, LL len) {
            l = pos; r = pos + 1;
            end = l + len;
            sum = len;
        }

        friend data operator | (data lhs, data rhs) {
            data ret;
            ret.l = lhs.l; ret.r = rhs.r;
            ret.sum = lhs.sum + rhs.sum;
            LL over = lhs.end - lhs.r;
            LL space = rhs.end - rhs.l - rhs.sum;
            if (over < 0) {
                ret.end = rhs.end;
            } else if (space >= over) {
                ret.end = rhs.end;   
            } else {
                ret.end = rhs.end + over - space;
            }
            return ret;
        }
    } node[1 << 22];

#define lson (o<<1)
#define rson (o<<1|1)

    void build(int o, int ll, int rr) {
        int mm = (ll + rr) / 2;
        l[o] = ll; r[o] = rr; m[o] = mm;
        if (l[o] != m[o]) {
            build(lson, ll, mm);
            build(rson, mm, rr);
            node[o] = node[lson] | node[rson];
        } else {
            node[o].init(ll, 0); 
        }
    }

    void update(int o, int pos, LL len) {
        if (l[o] != m[o]) {
            if (pos < m[o]) update(lson, pos, len);
            else update(rson, pos, len);
            node[o] = node[lson] | node[rson];
        } else {
            node[o].init(pos, len);
        }
    }

    data query(int o, int ll, int rr) {
        if (ll <= l[o] and r[o] <= rr) {
            return node[o];
        } else {
            if (rr <= m[o]) return query(lson, ll, rr);
            if (ll >= m[o]) return query(rson, ll, rr);
            return query(lson, ll, rr) | query(rson, ll, rr);
        }
    }
} seg;

LL len[1 << 22];
pair<int, int> ops[300005];

int main() {
    seg.build(1, 1, 1000005);
    int q; scanf("%d", &q);
    Rep (i, q) {
        char op[3]; scanf("%s", op);
        if (op[0] == '+') {
            int p, l; scanf("%d%d", &p, &l);
            ops[i] = {p, l};
            len[p] += l;
            seg.update(1, p, len[p]);
        } else if (op[0] == '-') {
            int id; scanf("%d", &id);
            int p, l; tie(p, l) = ops[id];
            len[p] -= l;
            seg.update(1, p, len[p]);
        } else if (op[0] == '?') {
            int t; scanf("%d", &t);
            auto res = seg.query(1, 0, t + 1);
            //printf("l=%d, r=%d, end=%lld, sum=%lld\n", res.l, res.r
            //, res.end, res.sum);
            printf("%lld\n", seg.query(1, 0, t+1).end - t); 
        } else assert(0);
    }
    return 0;
}
