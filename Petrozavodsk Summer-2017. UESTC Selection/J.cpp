#pragma GCC optimize(3)
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
int a[1 << 20];
LL dp[1 << 20];
       // f  t c
LL from[32][32];

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d", a + i);
    for (int i = 1; i < n; i++) {
        int x = a[i-1], y = a[i];
        if (x == y) continue;
        int top = 31 - __builtin_clz(x ^ y);
        bool bit1 = x & (1 << top);
        for (int i = 0; i <= top; i++) {
            bool bx = x & (1 << i), by = y & (1 << i);
            if (bx == by) continue;
            if (bx != bit1) from[top][i] -= 1 << i; else from[top][i] += 1 << i;
        }
    }
    for (int i = 19; i >= 0; i--) for (int f = 1 << i; f >= 0; f -= (1 << i)) {
        for (int mask = 0; mask < (1 << 20); mask += 1 << (1 + i)) {
            int cm = mask | f;
            LL val = dp[mask];
            for (int p = i; p < 20; p++) if (bool(f) ^ bool(cm & (1 << p)))
                val -= from[p][i]; else val += from[p][i];
            dp[cm] = val;
        }
    }
    auto it = min_element(dp, dp + (1 << 20));
    cout << it - dp << ' ' << *it << endl;
    return 0;
}
