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
vector<pair<int, int>> ans;

int main() {
    cin >> n;
    ans.push_back({0, 0});
    ans.push_back({6, 8});
    for (int i = 2; i < n - 1; i++) {
        int x, y; tie(x, y) = ans.back();
        if (i & 1) ans.emplace_back(x + 3, y + 4);
        else ans.emplace_back(x + 3, y - 4);
    }
    ans.emplace_back(ans.back().first, 0);
    for (auto p : ans) {
        int x, y; tie(x, y) = p;
        tie(x, y) = make_pair(5 * x + 12 * y, 12 * x - 5 * y);
        cout << x << ' ' << y << endl;
    }
    return 0;
}
