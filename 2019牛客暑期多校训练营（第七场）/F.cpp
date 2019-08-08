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
    vector<LL> tr1;
    vector<LL> tr2;

    void init(int n) {
        tr1.assign(N = n + 5, 0);
        tr2.assign(N = n + 5, 0);
    }

    LL sum1(int n) {
        LL ans = 0;
        while (n) { ans += tr1[n]; n &= n - 1; }
        return ans;
    }

    LL sum2(int n) {
        LL ans = 0;
        while (n) { ans += tr2[n]; n &= n - 1; }
        return ans;
    }

    void add(int n, LL x) {
        LL xx = x * n;
        while (n < N) { tr1[n] += x; tr2[n] += xx; n += n & -n; }
    }
} bit;

int n, m;
int e[100005], l[100005], c[100005];
vector<pair<int, bool>> events[100005];

int main() {
    int T; scanf("%d", &T);
    Rep (tt, T) {
        LL ans = 0;
        bit.init(200005);
        scanf("%d", &n);
        rep (i, n) scanf("%d%d%d", e + i, l + i, c + i);
        for (int i = 0; i <= n; i++) events[i].clear();
        scanf("%d", &m);
        rep (i, m) {
            int t, ll, rr;
            scanf("%d%d%d", &t, &ll, &rr);
            events[ll-1].emplace_back(t, true);
            events[rr].emplace_back(t, false);
        }
        set<int> sps;
        for (int i = 0; i < n; i++) {
            for (auto ev : events[i]) {
                int t; bool dir; tie(t, dir) = ev;
                if (dir) {
                    if (sps.size()) {
                        auto it = sps.lower_bound(t);
                        if (it == sps.begin()) {
                            bit.add(*it - t, 1);
                        } else if (it == sps.end()) {
                            bit.add(t - *prev(it), 1);
                        } else {
                            auto it2 = prev(it);
                            bit.add(*it - *it2, -1);
                            bit.add(t - *it2, 1);
                            bit.add(*it - t, 1);
                        }
                    }
                    sps.insert(t);
                } else {
                    if (sps.size() > 1) {
                        auto it = sps.lower_bound(t);
                        if (it == prev(sps.end())) {
                            bit.add(t - *prev(it), -1);
                        } else if (it == sps.begin()) {
                            bit.add(*next(it) - t, -1);
                        } else {
                            bit.add(t - *prev(it), -1);
                            bit.add(*next(it) - t, -1);
                            bit.add(*next(it) - *prev(it), 1);
                        }
                    }
                    sps.erase(t);
                }
            }
            if (sps.size()) ans += min(e[i] + 1ll * l[i] * (*sps.begin()), 1ll * c[i]);
            if (l[i] == 0) continue;
            LL ns1 = bit.sum2(c[i] / l[i]), ns2 = bit.sum1(200005) - bit.sum1(c[i] / l[i]);
            ans += ns1 * l[i] + ns2 * c[i];
        }
        printf("Case #%d: %lld\n", tt, ans);
    }
    return 0;
}
