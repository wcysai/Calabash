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

mt19937 gen(time(NULL));
int n;
bitset<12005> bs[6400];
char buf[12005];

int main() {
    scanf("%d", &n); n++;
    rep (i, n) {
        scanf("%s", buf);
        for (int c = 0; buf[c]; c++) {
            int mask = buf[c] - 33;
            rep (j, 6) if (mask & (1 << j)) bs[i].set(c * 6 + j) ;
        }
    }
    while (true) {
        int u = gen() % n, v = gen() % n;
        if (u == v) continue;
        int sz = (bs[u] & bs[v]).count();
        _debug("%d %d %d", u, v, sz);
        if (sz >= n / 2) {
            printf("%d %d\n", u + 1, v + 1);
            return 0;
        }
    }
    return 0;
}
close
