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

struct bit_purq {
    int N;
    vector<int> tr;
    void init(int n) { tr.assign(N = n + 5, 0); }
    int sum(int n) {
        int ans = 0;
        while (n) { ans += tr[n]; n &= n - 1; }
        return ans;
    }
    void add(int n, int x) {
        while (n < N) { tr[n] += x; n += n & -n; }
    }
} t1, t2;

int n;

int search() {
    int lv = 0, rv = t2.sum(n), pos = 0;
    for (int i = 20; i >= 0; i--) {
        if (pos + (1 << i) <= n and
                lv + t1.tr[pos + (1 << i)] <= rv - t2.tr[pos + (1 << i)]) {
            lv += t1.tr[pos + (1 << i)];
            rv -= t2.tr[pos + (1 << i)];
            pos += 1 << i;
        }
    }
    return pos;
}

struct prod {
    int id, a, b;
    bool operator < (const prod& rhs) const {
        return a * rhs.b < b * rhs.a;
    }
} p[256000];

int iid[256000];

void insert(int id) {
    _debug("%d", id);
    t1.add(id, p[id].a);
    t2.add(id, p[id].b);
}

void query() {
    int pos = search(), pid = pos + 1;
    _debug("pos=%d", pos);
    int work1 = t1.sum(pos), work2 = t2.sum(n) - t2.sum(pid);
    int a = p[pid].a, b = p[pid].b;
    LL num = 1ll * a * b + 1ll * a * work2 + 1ll * b * work1,
        denom = a + b, g = __gcd(num, denom);
    printf("%lld/%lld\n", num / g, denom / g);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        t1.init(n); t2.init(n);
        Rep (i, n) {
            p[i].id = i - 1;
            scanf("%d%d", &p[i].a, &p[i].b);
        }
        sort(p + 1, p + 1 + n);
        Rep (i, n) _debug("id=%d, (%d, %d)", p[i].id, p[i].a, p[i].b);
        Rep (i, n) iid[p[i].id] = i;
        rep (i, n) {
            insert(iid[i]);
            query();
        }
    }
    return 0;
}
