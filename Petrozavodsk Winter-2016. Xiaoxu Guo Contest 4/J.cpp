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

inline int lowbit(int x) { return x & -x; }
int n;
int bit[2048][2048];

void add(int x, int y, int d) {
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            bit[i][j] += d;
}

int sum(int x, int y) {
    int s = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            s += bit[i][j];
    return s;
}

int sum(int xl, int xr, int yl, int yr) {
    int ret = sum(xr, yr) - sum(xr, yl) - sum(xl, yr) + sum(xl, yl);
    return ret;
}

int a[2048];
int p[4], s[2];

int main() {
    scanf("%d", &n);
    rep (i, 4) scanf("%d", p + i);
    Rep (i, n) scanf("%d", a + i);

    rep (i, 2) {
        int u = p[i+2], l, r; tie(l, r) = minmax(p[0], p[1]);
        if (u < l) s[i] = 0; else if (u < r) s[i] = 1; else s[i] = 2;
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if ((a[i] < a[j]) == (p[2] < p[3])) add(a[i], a[j], 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++)
            if ((a[i] < a[j]) == (p[2] < p[3])) add(a[i], a[j], -1);
        int bnd[4] = {0, 0, 0, n};
        for (int j = 1; j < i; j++) if ((a[j] < a[i]) == (p[0] < p[1])) {
            tie(bnd[1], bnd[2]) = minmax(a[j], a[i]);
            ans += sum(bnd[s[0]], bnd[s[0]+1], bnd[s[1]], bnd[s[1]+1]);
        }
    }
    cout << ans << endl;
    return 0;
}
