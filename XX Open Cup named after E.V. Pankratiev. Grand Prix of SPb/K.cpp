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

int a, b, n;
int x[200005], y[200005];

int main() {
    cin >> a >> b; n = a * b * 2;
    rep (i, a) for (int j = i * (2 * b); j < (i + 1) * (2 * b); j++) x[j] = i;
    int ans = INT_MAX;
    rep (k, 2 * a) {
        map<pair<int, int>, int> mp;
        rep (i, b) for (int j = i * (2 * a) + k; j < (i + 1) * (2 * a) + k; j++)
            y[j % n] = i;
        rep (i, n) mp[{x[i], y[i]}]++;
        int minv = INT_MAX, maxv = INT_MIN;
        for (auto pr : mp) minv = min(minv, pr.second), maxv = max(maxv, pr.second);
        if (mp.size() < a + b) minv = 0;
        ans = min(ans, maxv - minv);
    }
    int g = __gcd(ans, n);
    printf("%d / %d\n", ans / g, n / g);
    return 0;
}
