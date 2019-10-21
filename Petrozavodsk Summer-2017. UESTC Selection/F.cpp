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

int ops[31], ans;

int solve(int p, int q, int rs) {
    int n = 0, res = p - q + rs, cost = rs;
    for (int i = 30; i >= 0; i--) {
        while (res >= ops[i]) {
            res -= ops[i];
            n++;
            cost += i + 1;
        }
        if (cost >= ans) return INT_MAX;
    }
    assert(res == 0);
    if (rs < n - 1) cost += n - 1 - rs;
    return cost;
}

int main() {
    int T; scanf("%d", &T);
    ops[0] = 1;
    for (int i = 1; i <= 30; i++) ops[i] = ops[i-1] * 2 + 1;
    while (T--) {
        int p, q; scanf("%d%d", &p, &q);
        if (p <= q) {
            printf("%d\n", q - p);
            continue;
        }
        ans = INT_MAX;
        for (int i = 0; i < ans; i++)
            ans = min(ans, solve(p, q, i));

        printf("%d\n", ans);
    }
    return 0;
}
