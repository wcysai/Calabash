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

map<int, vector<pair<int, int>>> segs;
LL ans = 0;

void propagate(int i) {
    for (auto p : segs[i]) {
        int l, r; tie(l, r) = p;
        ans += r - l;
        if (r - l > 2) segs[i+1].emplace_back(l+1, r-1);
    }
}

void merge(vector<pair<int, int>>& segs) {
    vector<pair<int, int>> ans;
    sort(range(segs));
    int ll, rr; tie(ll, rr) = segs.front();
    for (auto p : segs) {
        int l, r; tie(l, r) = p;
        if (l <= rr) {
            rr = max(rr, r);
        } else {
            ans.emplace_back(ll, rr);
            ll = l; rr = r;
        }
    }
    ans.emplace_back(ll, rr);
    segs = move(ans);
}

int main() {
    int n; scanf("%d", &n);
    rep (i, n) {
        int x, y; scanf("%d%d", &x, &y);
        segs[x].emplace_back(y, y + 2);
    }
    for (auto& p : segs) {
        merge(p.second);
        propagate(p.first);
    }
    cout << ans / 2 << endl;
    return 0;
}
