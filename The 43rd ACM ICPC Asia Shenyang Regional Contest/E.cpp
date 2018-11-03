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

typedef pair<LL, int> pos_t;
typedef pair<pos_t, pos_t> node;

const LL INF = LLONG_MAX / 4;
constexpr pos_t idl_pos_t(INF, 0), idr_pos_t(-INF, 0);
constexpr node idl_node(idl_pos_t, idl_pos_t), idr_node(idr_pos_t, idr_pos_t);

inline node merge_l(node a, node b) {
    pos_t vec[4] = {a.first, a.second, b.first, b.second};
    sort(vec, vec + 4);
    if (vec[1].second == vec[0].second) return {vec[0], vec[2]};
    else return {vec[0], vec[1]};
}

inline node merge_r(node a, node b) {
    pos_t vec[4] = {a.first, a.second, b.first, b.second};
    sort(vec, vec + 4, greater<pos_t>());
    if (vec[1].second == vec[0].second) return {vec[0], vec[2]};
    else return {vec[0], vec[1]};
}

const int MAXN = 100005 * 4;

struct segtree {
    int l[MAXN], m[MAXN], r[MAXN];
    node nl[MAXN], nr[MAXN];

#define lson (o<<1)
#define rson (o<<1|1)

    void pull(int o) {
        nl[o] = merge_l(nl[lson], nl[rson]);
        nr[o] = merge_r(nr[lson], nr[rson]);
    }

    template <typename T>
    void build(int o, int ll, int rr, T fn) {
        int mm = (ll + rr) / 2;
        l[o] = ll; r[o] = rr; m[o] = mm;
        if (ll == mm) {
            fn(ll, nl[o], nr[o]);
        } else {
            build(lson, ll, mm, fn);
            build(rson, mm, rr, fn);
            pull(o);
        }
    }

    void modify(int o, int x, node _nl, node _nr) {
        if (l[o] == m[o]) {
            nl[o] = _nl;
            nr[o] = _nr;
        } else {
            if (x < m[o]) modify(lson, x, _nl, _nr);
            else modify(rson, x, _nl, _nr);
            pull(o);
        }
    }

    pair<node, node> query(int o, int ll, int rr) {
        if (ll <= l[o] && r[o] <= rr) {
            return {nl[o], nr[o]};
        } else {
            node ansl = idl_node, ansr = idr_node, curl, curr;
            if (m[o] > ll) {
                tie(curl, curr) = query(lson, ll, rr);
                ansl = merge_l(ansl, curl);
                ansr = merge_r(ansr, curr);
            }
            if (m[o] < rr) {
                tie(curl, curr) = query(rson, ll, rr);
                ansl = merge_l(ansl, curl);
                ansr = merge_r(ansr, curr);
            }
            return {ansl, ansr};
        }
    }

    LL Query(int ll, int rr) {
        node ansl, ansr; tie(ansl, ansr) = query(1, ll, rr);
        if (ansl.first.second != ansr.first.second) return ansr.first.first - ansl.first.first;
        return max(ansr.second.first - ansl.first.first, ansr.first.first - ansl.second.first);
    }
} seg1, seg2;

int n;
LL x[100005], y[100005];
int c[100005];

void update_ninja(int i) {
    seg1.modify(1, i, {{x[i] + y[i], c[i]}, idl_pos_t}, {{x[i] + y[i], c[i]}, idr_pos_t});
    seg2.modify(1, i, {{x[i] - y[i], c[i]}, idl_pos_t}, {{x[i] - y[i], c[i]}, idr_pos_t});
}

void seg1_initializer(int i, node &nl, node &nr) {
    nl = {{x[i] + y[i], c[i]}, idl_pos_t};
    nr = {{x[i] + y[i], c[i]}, idr_pos_t};
}

void seg2_initializer(int i, node &nl, node &nr) {
    nl = {{x[i] - y[i], c[i]}, idl_pos_t};
    nr = {{x[i] - y[i], c[i]}, idr_pos_t};
}

LL query_do(int l, int r) {
    LL ans = max(seg1.Query(l, r), seg2.Query(l, r));
    return ans < 0 ? 0 : ans;
}

void work() {
    int m; scanf("%d%d", &n, &m);
    Rep (i, n) {
        int xx, yy, cc; scanf("%d%d%d", &xx, &yy, &cc);
        x[i] = xx; y[i] = yy; c[i] = cc;
    }
    seg1.build(1, 1, n + 1, seg1_initializer);
    seg2.build(1, 1, n + 1, seg2_initializer);
    while (m--) {
        int q; scanf("%d", &q);
        if (q == 1) {
            int kk, xx, yy; scanf("%d%d%d", &kk, &xx, &yy);
            x[kk] += xx; y[kk] += yy;
            update_ninja(kk);
        } else if (q == 2) {
            int kk, cc; scanf("%d%d", &kk, &cc);
            c[kk] = cc;
            update_ninja(kk);
        } else if (q == 3) {
            int l, r; scanf("%d%d", &l, &r); r++;
            cout << query_do(l, r) << endl;
        } else assert(0);
    }

}

int main() {
    int T; scanf("%d", &T);
    Rep (t, T) {
        printf("Case #%d:\n", t);
        work();
    }
    return 0;
}
