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
pair<ULL, ULL> a[100005];
ULL ans = 0;

int main() {
    scanf("%d", &n);
    rep (i, n) {
        ULL x, y; scanf("%llu%llu", &x, &y);
        ans = max(ans, x * y * 5);
        if (x < y) swap(x, y);
        a[i] = make_pair(x, y);
    }
    sort(a, a + n, greater<>());
    ULL maxb = 0;
    rep (i, n) {
        ans = max(ans, a[i].first * min(maxb, a[i].second) * 10);
        maxb = max(maxb, a[i].second);
    }
    cout << ans / 10 << '.' << ans % 10 << endl;
    return 0;
}
