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

LL k;
int n;
string s;
bool rem[128];

LL check() {
    LL x = 0;
    rep (i, n) {
        if (rem[i]) continue;
        x = x << 1;
        if (s[i] == '1') x++;
    }
    _debug("x=%lld", x);
    return x;
}   

int main() {
    cin >> k >> s;
    n = s.size();
    vector<pair<int, int>> pi;
    for (int i = 1; i < n; i++) {
        if (s[i] == '1') pi.emplace_back(-1, i);
        else pi.emplace_back(0, i);
    }
    sort(range(pi));
    int ans = 0;
    for (auto p : pi) {
        if (check() <= k) {
            cout << ans << endl;
            return 0;
        }
        rem[p.second] = true;
        ans++;
    }
    cout << ans << endl;
    return 0;
}
