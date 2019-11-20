#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 4 * 500006, MAXV = 500006;

struct segtree {
    int l[MAXN], m[MAXN], r[MAXN];
    pair<int, int> val[MAXN];

#define lson (o<<1)
#define rson (o<<1|1)

    void build(int o, int ll, int rr) {
        int mm = (ll + rr) / 2;
        l[o] = ll; m[o] = mm; r[o] = rr;
        if (ll < mm) {
            build(lson, ll, mm);
            build(rson, mm, rr);
        }
    }

    void pushdown(int o) {
        if (val[o].first < 0) return;
        val[lson] = val[o];
        val[rson] = val[o];
        val[rson].second += m[o] - l[o];
        val[o] = make_pair(-1, 0);
    }

    void change(int o, int ll, int rr, pair<int, int> v) {
        if (ll <= l[o] and r[o] <= rr) {
            val[o] = make_pair(v.first, v.second - ll + l[o]);
        } else {
            pushdown(o);
            if (m[o] > ll) change(lson, ll, rr, v);
            if (m[o] < rr) change(rson, ll, rr, v);
        }
    }

    pair<int, int> query(int o, int pos) {
        if (val[o].first >= 0) return make_pair(val[o].first, val[o].second - l[o] + pos);
        if (pos < m[o]) return query(lson, pos); else return query(rson, pos);
    }
} seg;

int ts = 1;

struct BIT {
    vector<pair<int, uint8_t>> val[MAXV];

    BIT() {
        for (auto& v : val) v.emplace_back(0, 0);
    }

    int query(int n, int t) {
        uint8_t ret = 0;
        while (n < MAXV) {
            ret += upper_bound(range(val[n]), make_pair(t, (uint8_t)255))[-1].second;
            n += n & -n;
        }
        return ret;
    }

    void add(int n, uint8_t x) {
        while (n) {
            val[n].emplace_back(ts, val[n].back().second + x);
            n &= n - 1;
        }
    }

    void add(int l, int r, uint8_t x) {
        add(r, x);
        add(l, -x);
    }
} bit;

int n, m, q;
int pos[500005];

int main() {
    scanf("%d%d%d", &n, &m, &q);
    seg.build(1, 1, n + 1);
    Rep (i, m) {
        int sz; scanf("%d", &sz);
        pos[i+1] = sz + pos[i];
        Rep (j, sz) {
            int val; scanf("%d", &val);
            bit.add(pos[i]+j-1, pos[i]+j, val);
        }
    }
    rep (_, q) {
        int op; scanf("%d", &op);
        if (op == 1) {
            int i, p; scanf("%d%d", &i, &p);
            seg.change(1, p, p + pos[i+1] - pos[i], make_pair(ts, pos[i]+1));
        } else if (op == 2) {
            int p; scanf("%d", &p);
            int t, pos; tie(t, pos) = seg.query(1, p);
            printf("%d\n", t ? bit.query(pos, t) : 0);
        } else if (op == 3) {
            ts++;
            int i, l, r; scanf("%d%d%d", &i, &l, &r); l--;
            l += pos[i]; r += pos[i];
            bit.add(l, r, 1);
        } else assert(0);
    }
    return 0;
}
