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

int n, m, p;

int digitsum(LL x) {
    int ans = 0;
    while (x) ans += x % 10, x /= 10;
    return ans;
}

int getvalue(int i, int j, int n) {
    int border = min({i - 1, j - 1, n - i, n - j});
    int sz = n - border - border;
    i -= border; j -= border;
    LL ans = 0;
    if (i == 1) ans = sz + sz + j - 2;
    else if (j == 1) ans = sz + sz - i;
    else if (i == sz) ans = sz + 1 - j;
    else if (j == sz) ans = sz * 3 + i - 3;
    else assert(0);
    ans += 1ll * n * n - 1ll * sz * sz;
    return digitsum(ans);
}

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
} bit;

int ans[100005];

struct event {
    // tp : 0 add, 1 delans, 2 incans
    int x, y1, y2, tp, id;

    bool operator < (const event& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return tp < rhs.tp;
    }

    void process() {
        if (tp == 0) bit.add(y1, getvalue(x, y1, n));
        else {
            LL as = bit.sum(y2) - bit.sum(y1 - 1);
            if (tp == 1) ans[id] -= as; else ans[id] += as;
        }
    }
};

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &p);
        bit.init(n);
        vector<event> events;
        rep (i, m) {
            int x, y; scanf("%d%d", &x, &y);
            events.push_back(event{x, y, 0, 0, 0});
        }
        rep (i, p) {
            ans[i] = 0;
            int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            events.push_back(event{x1 - 1, y1, y2, 1, i});
            events.push_back(event{x2, y1, y2, 2, i});
        }
        sort(range(events));
        for (auto& ev : events) ev.process();
        for (int i = 0; i < p; i++) printf("%d\n", ans[i]);
    }
    return 0;
}
