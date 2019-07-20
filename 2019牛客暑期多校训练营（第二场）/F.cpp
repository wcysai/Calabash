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
LL wt[32][32];
 
LL calc(unsigned mask) {
    LL ans = 0;
    rep (i, n + n) rep (j, n + n)
        if (bool(mask & (1 << i)) != bool(mask & (1 << j)))
            ans += wt[i][j];
    return ans;
}
 
LL iteration() {
    int id[32]; iota(id, id + n + n, 0);
    random_shuffle(id, id + n + n);
    unsigned mask = 0;
    rep (i, n) mask |= (1 << id[i]);
    LL ans = calc(mask);
    while (true) {
        bool flag = false;
        for (int i = 0; i < n + n; i++) if (mask & (1 << i)) {
            for (int j = 0; j < n + n; j++) if (!(mask & (1 << j))) {
                unsigned newmask = mask ^ (1 << i) ^ (1 << j);
                LL val = calc(newmask);
                if (val > ans) {
                    ans = val;
                    mask = newmask;
                    flag = true;
                }
            }
        }
        if (!flag) break;
    }
    return ans;
}
 
int main() {
    scanf("%d", &n);
    rep (i, n + n) rep (j, n + n) scanf("%lld", &wt[i][j]);
 
    clock_t start = clock();
    LL ans = 0;
    while (clock() - start < 3 * CLOCKS_PER_SEC) {
        ans = max(ans, iteration());
    }
    cout << ans / 2 << endl;
    return 0;
}
