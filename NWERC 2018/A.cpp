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
int x[100005], y[100005];

struct item {
    int sz;
    double val;
    double cost;

    bool operator < (const item& rhs) const {
        return val < rhs.val;
    }

    item& operator += (const item& a) {
        cost += a.cost;
        double newval = (val * sz + a.val * a.sz) / (sz + a.sz);
        cost += (newval - val) * (newval - val) * sz + 
                (newval - a.val) * (newval - a.val) * a.sz;
        val = newval;
        sz += a.sz;
        return *this;
    }
};

vector<item> items;

void push_item(item it) {
    if (items.empty() or items.back() < it) {
        items.push_back(it);   
    } else {
        item cur = items.back(); items.pop_back();
        cur += it;
        push_item(cur);
    }
}

double compute_cost() {
    double ans = 0.0;
    for (auto& x : items) ans += x.cost;
    items.clear();
    return ans;
}

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d%d", x + i, y + i);
    double ans = 0.0;
    rep (i, n) push_item({1, x[i], 0});
    ans += compute_cost();
    rep (i, n) push_item({1, y[i], 0});
    ans += compute_cost();
    printf("%.9f\n", ans);
    return 0;
}
