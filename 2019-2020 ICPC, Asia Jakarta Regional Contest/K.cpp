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

int n, q;
char buf[100005];

const LL mod = 1000000007;
typedef array<array<LL, 2>, 2> mat;

const mat OPA = { {{1, 1}, {0, 1}} }, OPB = { {{1, 0}, {1, 1}} };

inline mat operator * (mat a, mat b) {
    mat ret = {{}};
    rep (i, 2) rep (j, 2) rep (k, 2) ret[i][k] += a[i][j] * b[j][k];
    rep (i, 2) rep (j, 2) ret[i][j] %= mod;
    return ret;
}

inline pair<LL, LL> operator * (mat a, pair<LL, LL> b) {
    return make_pair(
        (a[0][0] * b.first + a[0][1] * b.second) % mod,
        (a[1][0] * b.first + a[1][1] * b.second) % mod
    );
}

const int MAXN = 4 * 100005;
struct {
    int l[MAXN], m[MAXN], r[MAXN];
    mat val0[MAXN], val1[MAXN];
    bool tag[MAXN];

#define lson (o<<1)
#define rson (o<<1|1)

    void pull(int o) {
        val0[o] = val0[rson] * val0[lson];
        val1[o] = val1[rson] * val1[lson];
    }

    void push_tag(int o, bool f) {
        if (not f) return;
        swap(val0[o], val1[o]);
        tag[o] ^= 1;
    }

    void push(int o) {
        if (l[o] == m[o]) return;
        if (!tag[o]) return;
        push_tag(lson, tag[o]);
        push_tag(rson, tag[o]);
        tag[o] = false;
    }

    void build(int o, int ll, int rr) {
        int mm = (ll + rr) / 2;
        l[o] = ll; r[o] = rr; m[o] = mm;
        tag[o] = false;
        if (ll == mm) {
            if (buf[ll] == 'A') val0[o] = OPA, val1[o] = OPB; 
            else val0[o] = OPB, val1[o] = OPA;
        } else {
            build(lson, ll, mm);
            build(rson, mm, rr);
            pull(o);
        }
    }

    void flip(int o, int ll, int rr) {
        if (ll <= l[o] and r[o] <= rr) {
            push_tag(o, 1);
        } else {
            push(o);
            if (m[o] > ll) flip(lson, ll, rr);
            if (m[o] < rr) flip(rson, ll, rr);
            pull(o);
        }
    }

    mat query(int o, int ll, int rr) {
        if (ll <= l[o] and r[o] <= rr) {
            return val0[o];
        } else {
            push(o);
            if (rr <= m[o]) return query(lson, ll, rr);
            if (ll >= m[o]) return query(rson, ll, rr);
            return query(rson, ll, rr) * query(lson, ll, rr);
        }
    }
} tr;

int main() {
    scanf("%d%d", &n, &q);
    scanf("%s", buf);
    tr.build(1, 0, n);
    while (q--) {
        int tp, l, r; scanf("%d%d%d", &tp, &l, &r); l--;
        if (tp == 1) {
            tr.flip(1, l, r);
        } else {
            pair<LL, LL> vec;
            scanf("%lld%lld", &vec.first, &vec.second);
            LL a, b; tie(a, b) = tr.query(1, l, r) * vec;
            printf("%lld %lld\n", a, b);
        }
    }
    return 0;
}
