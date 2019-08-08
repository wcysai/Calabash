#pragma GCC optimize(3)
#pragma GCC target("avx512f")
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

int n;
LL cnt[210];

void solve() {
    memset(cnt ,0, sizeof cnt);
    LL totcost = 0;
    map<int, vector<pair<int, int>>> trees;
    for (int i = 0; i < n; i++) {
        int h, c, p; scanf("%d%d%d", &h, &c, &p);
        trees[h].emplace_back(c, p);
        totcost += 1ll * c * p;
    }
    LL ans = LLONG_MAX;
    for (const auto& p : trees) {
        LL sz = 0;
        for (auto pr : p.second) {
            sz += pr.second;
            totcost -= 1ll * pr.first * pr.second;
        }

        LL csz = accumulate(range(cnt), 0ll);
        LL cost = totcost;

        if (sz <= csz) {
            LL rem = csz - sz + 1;
            rep (i, 205) {
                if (cnt[i] >= rem) {
                    cost += i * rem;
                    break;
                } else {
                    cost += i * cnt[i];
                    rem -= cnt[i];
                }
            }
        }

        ans = min(ans, cost);
        for (auto pr : p.second) cnt[pr.first] += pr.second;
    }
    cout << ans << endl;
}

int main() {
    while (scanf("%d", &n) == 1) solve();
}
