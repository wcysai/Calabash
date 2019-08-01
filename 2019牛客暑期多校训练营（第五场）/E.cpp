#pragma GCC optimize(3)
#pragma GCC target("avx")
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

int n, m;
uint32_t e[32];
uint8_t ans[1 << 26];
bitset<1 << 26> ind;

void make_ind() {
    ind[0] = 1;
    for (int sz = 0; sz < n; sz++)
        for (uint32_t mask = 0; mask < (1u << sz); mask++)
            if (ind[mask] and (mask & e[sz]) == 0) ind[mask | (1 << sz)] = 1;
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        e[u] |= 1u << v;
        e[v] |= 1u << u;
    }
    make_ind();
    uint32_t tot = 0;
    for (uint32_t mask = 1; mask < (1u << n); mask++) {
        if (ind[mask]) {
            ans[mask] = __builtin_popcount(mask);
            continue;
        }
        uint32_t bit = mask & -mask;
        if (uint32_t bs = e[__builtin_ctz(bit)] & mask)
            ans[mask] = max(ans[mask ^ bit], ans[mask ^ (bs & -bs)]);
        else ans[mask] = ans[mask ^ bit] + 1;
    }
    cout << accumulate(ans, ans + (1 << n), 0u) << endl;
    return 0;
}
