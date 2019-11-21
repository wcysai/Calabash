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

int read_grade() {
    double x; scanf("%lf", &x); return lround(x * 10);
}

int n, k;
int H[100005], h[100005];

vector<int> pos;

double incr(int h1, int h2, int j) {
    if (h1 <= j) return 1.0;
    return double(j - h2) / (h1 - h2);
}

double solve() {
    pos.clear();
    double ans = 0.0;
    for (int i = n; i; i--) {
        if (pos.empty() or h[i] > h[pos.back()]) pos.push_back(i);
        int j = *lower_bound(range(pos), i, [] (int u, int v) { return h[u] < h[v]; });
        ans = max(ans, j - i + incr(h[i-1], h[i], h[j]));
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; i++) scanf("%d", H + i);
    int max_slope = INT_MIN;
    rep (i, n) max_slope = max(max_slope, H[i+1] - H[i]);
    rep (_, k) {
        int s = read_grade();
        if (s > max_slope) {
            puts("impossible");
            continue;
        }
        for (int i = 0; i <= n; i++) h[i] = H[i] - s * i;
        double ans = solve();
        reverse(h, h + n + 1); rep (i, n + 1) h[i] = -h[i];
        ans = max(ans, solve());
        printf("%.12f\n", ans);
    }
    return 0;
}
