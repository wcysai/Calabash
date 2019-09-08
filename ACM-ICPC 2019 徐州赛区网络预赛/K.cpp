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
int x[1024], y[1024];
map<ULL, int> mp;

ULL encode(int x, int y) {
    union {
        struct { int xx, yy; };
        LL ret;
    } s;
    s.xx = x; s.yy = y;
    return s.ret;
}

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d%d", x + i, y + i);
    rep (i, n) rep (j, i) mp[encode(x[i] + x[j], y[i] + y[j])] += 2;
    rep (i, n) mp[encode(x[i] * 2, y[i] * 2)] ++;
    int ans = INT_MAX;
    for (auto p : mp) ans = min(ans, n - p.second);
    cout << ans << endl;
    return 0;
}
