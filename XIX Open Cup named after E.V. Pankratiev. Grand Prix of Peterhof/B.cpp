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

LL add(LL x, LL y) {
    if (x == -1) return y;
    if (y == -1) return x;
#ifdef __LOCAL_DEBUG__
    return x | y;
#endif
    printf("? %lld %lld\n", x, y);
    fflush(stdout);
    LL ret; scanf("%lld", &ret);
    return ret;
}

void answer(LL ans) {
    printf("! %lld\n", ans);
    fflush(stdout);
}

int n, k;
LL a[2048];
int p[2048], ip[2048];
int sn;
int pos[2048];

struct leaf {
    int l, r;
    vector<LL> pre, suf;
    
    void init(int _l, int _r) {
        l = _l; r = _r;
        pre.push_back(-1);
        for (int i = l; i < r; i++) 
            pre.push_back(add(pre.back(), a[ip[i]]));
        suf.push_back(-1);
        for (int i = r - 1; i >= l; i--) {
            suf.push_back(add(suf.back(), a[ip[i]]));
        }
//        reverse(range(suf));
    }
    
    LL total() {
        return pre.back(); 
    }
} lf[2048];
LL total[2048];

LL brute_query(int l, int r) {
    LL ret = -1;
    for (int i = l; i < r; i++) 
        ret = add(ret, a[ip[i]]);
    return ret;
}

const int MAXN = 2048 * 4;
struct segtree {
    int l[MAXN], m[MAXN], r[MAXN];
    vector<LL> suf[MAXN], pre[MAXN];

#define lson (o<<1)
#define rson (o<<1|1)

    void build(int o, int ll, int rr) {
        _debug("%d %d %d", o, ll, rr);
        int mm = (ll + rr) / 2;
        l[o] = ll;
        r[o] = rr;
        m[o] = mm;
        if (ll != mm) {
            build(lson, ll, mm);
            build(rson, mm, rr);
        }
        suf[o].push_back(-1);
        for (int i = mm - 1; i >= ll; i--) {
            suf[o].push_back(add(suf[o].back(), total[i]));
        }
        pre[o].push_back(-1);
        for (int i = mm; i < rr; i++) {
            pre[o].push_back(add(pre[o].back(), total[i]));
        }
    }
    

    LL query(int o, int ll, int rr) {
        _debug("%d %d %d", o, ll, rr);
        if (ll == rr) return -1;
    //    print(o);
        if (ll <= m[o] and m[o] < rr) {
            return add(suf[o][m[o] - ll], pre[o][rr - m[o]]);
        } else {
            if (m[o] <= ll) return query(rson, ll, rr);
            if (m[o] >= rr) return query(lson, ll, rr);
            assert(0);
        }
    }
} seg;

void preprocess() {
    srand(time(NULL));
    Rep (i, n) p[i] = i - 1;
// #ifndef __LOCAL_DEBUG__
    random_shuffle(p + 1, p + n + 1);
// #endif
//    cerr << "p: "; Rep (i, n) cerr << p[i] << ' '; cerr << endl;
    Rep (i, n) ip[p[i]] = i;
    sn = n / int(ceil(log2(n))); if (sn == 0) sn = 1;
    for (int i = 0; i < sn; i++) 
        pos[i] = n * i / sn;
    pos[sn] = n;
    _debug("sn=%d", sn);
//    cerr << "sn: " << sn << endl;
//    cerr << "pos: ";
//    rep (i, sn + 1) cerr << pos[i] << ' ' ; cerr << endl;
    rep (i, sn) {
        lf[i].init(pos[i], pos[i+1]);
        total[i] = lf[i].total();
    }
    seg.build(1, 0, sn);
}

LL query(int l, int r) {
    if (l == r) return -1;
    int lbnd = upper_bound(pos, pos + sn, l) - pos;
    int rbnd = lower_bound(pos, pos + sn, r) - pos;
    if (lbnd < rbnd) {
        rbnd--;
        _debug("[%d,%d) [%d|%d]", l, r, lbnd, rbnd);
        LL res1 = lf[lbnd-1].suf[pos[lbnd] - l];
        LL res2 = lf[rbnd].pre[r - pos[rbnd]];
  //      cout << res1 <<' ' << res2 << endl;
        return add(add(res1, res2), seg.query(1, lbnd, rbnd));
    } else return brute_query(l, r);
}

int main() {
    int q;
    scanf("%d%d%d", &n, &q, &k);
    Rep (i, n) scanf("%lld", a + i);
    preprocess();
    while (q--) {
        printf("next\n"); fflush(stdout);
        LL cur = -1;
        int s[32];
        Rep (i, k) {
            int x; scanf("%d", &x);
            s[i] = p[x];
        }
        s[0] = 0;
        s[k + 1] = n;
        sort(s, s + k + 2);
        assert(s[0] == 0 and s[k+1] == n);
        for (int i = 0; i < k + 1; i++) 
            cur = add(cur, query((i ? s[i] + 1 : 0), s[i+1])); 
        answer(cur);
    }
    return 0;
}
