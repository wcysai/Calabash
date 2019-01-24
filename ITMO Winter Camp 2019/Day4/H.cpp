#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
//#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;

int k, n;
LL a[200005];

int check(LL s) {
    map<LL, int> sel;
    sel[a[0]] = 1;
    auto update = [&] (LL x, int val) {
        if (val <= sel[x]) return;
        sel[x] = val;
        while (next(sel.find(x)) != sel.end()) {
            auto it = next(sel.find(x));
            if (it->second <= val) sel.erase(it);
            else break;
        }
    };

    for (int i = 1; i < n; i++) {
        if (s - a[i] < 0) continue;
        auto it = sel.upper_bound(s - a[i]);
        if (it == sel.begin()) continue;
        update(a[i], prev(it)->second + 1);
    }
    
    int ans = 0;
    for (auto p : sel) 
        if (p.first + a[0] <= s)
            ans = max(ans, p.second);
    return ans;
}

int main() {
    scanf("%d%d", &n, &k);
    rep (i, n) scanf("%lld", a+i);
    rotate(a, min_element(a, a+n), a+n);
    LL l = a[0] + a[0], r = *max_element(a, a+n) * 2 + 5;
    while (r > l) {
        LL mid = l + (r - l) / 2;
        if (check(mid) >= k) r = mid;
        else l = mid + 1;
    }
    printf("%lld\n", r);
    return 0;
}
