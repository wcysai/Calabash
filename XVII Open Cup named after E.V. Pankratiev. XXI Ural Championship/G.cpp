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

LL xx, yy;
map<LL, int> work(vector<pair<int, int>> a) {
    map<LL, int> cnt;
    for (unsigned mask = 0; mask < (1 << a.size()); mask++) {
        pair<int, int> res = {0, 0};
        rep (i, a.size()) if (mask & (1u << i)) 
            res.first += a[i].first, res.second += a[i].second;
        cnt[(res.first * yy - res.second * xx)] ++;
    }
    return cnt;
}

int n;
vector<pair<int, int>> a, b;
map<LL, int> aa, bb;
int main() {
    scanf("%d", &n);
    scanf("%lld%lld", &xx, &yy);
    rep (i, n) {
        int x, y; scanf("%d%d", &x, &y);
        ((i & 1) ? a : b).emplace_back(x, y);
    }
    aa = work(a);
    bb = work(b);
    LL ans = -1;
    for (auto p : aa) ans += 1ll * p.second * bb[-p.first];
    cout << ans << endl;
    return 0;
}
