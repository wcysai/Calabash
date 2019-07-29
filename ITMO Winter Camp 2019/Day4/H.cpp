#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i < int(n); i++)
#define range(x) begin(x), end(x)
 
int k, n;
int a[200005];
 
int check(int s) {
    map<int, int> sel;   
    sel[a[0]]++;
    auto update = [&] (int x, int val) {
        val = max(val, prev(sel.upper_bound(x))->second);
        if (sel[x] >= val) return;
        sel[x] = val;
        while (true) {
            auto it = sel.upper_bound(x);
            if (it == sel.end() or it->second > val) break;
            sel.erase(it);
        }
    };
 
    for (int i = 1; i < n; i++) {
        auto it = sel.upper_bound(s - a[i]);
        if (it == sel.begin()) continue;
        update(a[i], prev(it)->second + 1);
    }
     
    vector<int> v;

    int ans = 0;
    for (auto p : sel) {
        v.push_back(p.second);
        if (p.first + a[0] <= s) 
            ans = max(ans, p.second);
    }
    assert(is_sorted(range(v)));
    return ans;
}
 
int main() {
    scanf("%d%d", &n, &k);
    rep (i, n) scanf("%d", a+i);
    rotate(a, min_element(a, a+n), a+n);
    int l = a[0] + a[0], r = 2000000005;
    while (r > l) {
        int mid = l + (r - l) / 2;
        if (check(mid) >= k) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", r);
    return 0;
}
