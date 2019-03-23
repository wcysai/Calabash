#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL; 

struct bit_purq {
    int N;
    vector<LL> tr, keys;
    
    int getkey(LL key) { return lower_bound(range(keys), key) - keys.begin() + 1; }

    void init(vector<LL> Keys) { 
        keys = move(Keys);
        sort(range(keys)); keys.erase(unique(range(keys)), keys.end());
        tr.assign(N = keys.size() + 5, LLONG_MAX / 3); 
    }

    LL query(LL key) {
        int n = getkey(key);
        LL ans = LLONG_MAX / 3;
        while (n) { ans = min(ans, tr[n]); n &= n - 1; }
        return ans;
    }

    void update(LL key, LL x) {
        int n = getkey(key);
        while (n < N) { tr[n] = min(tr[n], x); n += n & -n; } 
    }
} bit1, bit2;

int n; 
LL a[1 << 20];
LL c[1 << 20], rmc[1 << 20];
LL pans;
bool old[1 << 20];

void prep() {
    pans = 0;
    set<LL> s;
    map<LL, int> next_occ;
    for (int i = 0; i < n; i++) 
        c[i] = LL(n + i + 1) * (n - i) / 2;
    for (int i = 0; i < n; i++) {
        old[i] = s.count(a[i]);
        if (!old[i]) {
            pans += c[i];
            s.insert(a[i]);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        rmc[i] = 0;
        if (!old[i]) {
            rmc[i] -= c[i];
            if (next_occ.count(a[i]))
                rmc[i] += c[next_occ[a[i]]];
        }
        next_occ[a[i]] = i;
    }
}

LL work1() {
    LL ans = 0;
    set<LL> s; s.insert(LLONG_MIN / 3); s.insert(LLONG_MAX / 3);
    auto mindis = [&] (LL x) {
        auto p = s.lower_bound(x);
        return min(abs(x - *p), abs(x - *prev(p)));
    };
    for (int i = 0; i < n; i++) {
        ans = min(ans, rmc[i] + mindis(a[i]));
        s.insert(a[i]);
    }
    _debug("%lld", ans);
    return ans;
}

LL work2() {
    LL ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        LL cur = rmc[i] + c[i];
        cur += min(bit1.query(a[i]) + a[i], bit2.query(-a[i]) - a[i]);
        ans = min(ans, cur);
        if (!old[i]) {
            bit1.update(a[i], -a[i] - c[i]);
            bit2.update(-a[i], a[i] - c[i]);
        }
    }
    _debug("%lld", ans);
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        vector<LL> pos;
        rep (i, n) scanf("%lld", a + i);
        pos.assign(a, a + n);
        bit1.init(pos);
        for (LL& x : pos) x = -x;
        bit2.init(pos);
        prep();
        LL best = min(work1(), work2());
        printf("%lld\n", pans + best);
    }
    return 0;
}
