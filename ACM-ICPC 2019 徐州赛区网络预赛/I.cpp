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

int n, m;
int p[100005], rp[100005];
int ans[100005];

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
} bit ;

struct event {
    // 0: add, 1: q+, 2: q-
    int type, x, y, q;

    bool operator < (const event &ev) const {
        if (x != ev.x) return x < ev.x;
        return type < ev.type;
    }

    void process() {
        _debug("%d: (%d, %d) %d", type, x, y, q);
        if (type == 0) bit.add(y, 1);
        else {
            int val = bit.sum(y);
            if (type == 1) ans[q] += val; else ans[q] -= val;
        }
    }
};

vector<event> ev;

int main() {
    scanf("%d%d", &n, &m); bit.init(n);
    Rep (i, n) scanf("%d", p + i), rp[p[i]] = i;
    Rep (i, n) for (int j = i + i; j <= n; j += i)
        ev.push_back(event{0, rp[i], rp[j], 0});
    rep (i, m) {
        int l, r; scanf("%d%d", &l, &r); l--;
        ev.push_back(event{1, r, r, i});
        ev.push_back(event{2, l, r, i});
        ev.push_back(event{2, r, l, i});
        ev.push_back(event{1, l, l, i});
    }
    sort(range(ev));
    for (auto& e : ev) e.process();
    rep (i, m) printf("%d\n", ans[i]);
    return 0;
}
