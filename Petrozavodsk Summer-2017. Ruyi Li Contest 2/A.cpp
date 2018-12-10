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

const int MAXN = 50004;
int n, m, q;
bitset<MAXN> a, ans;
vector<int> as;

int main() {
    scanf("%d%d%d", &n, &m, &q);
    rep (i, n) {
        int aa; scanf("%d", &aa);
        a[aa] = 1;
        as.push_back(aa);
    }
    rep (i, m) {
        int b; scanf("%d", &b);
        if (b > 500) {
            bitset<MAXN> mask; mask.reset(); mask = ~mask; mask >>= MAXN - b;
            for (int bb = 0; bb < MAXN; bb += b) {
                ans ^= (a >> bb) & mask;
            }
        } else {
            for (int a : as) ans.flip(a % b);
        }
    }
    rep (i, q) {
        int qq; scanf("%d", &qq);
        printf("%d\n", int(ans[qq]));
    }

    return 0;
}
