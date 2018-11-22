#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr,"[%s] "fmt"\n", ##__VA_ARGS__)
#else
#define _debug(...) ((void)0)
#endif
typedef long long LL;
typedef unsigned long long ULL;
template <typename T> inline T maxz(T& x, T y) { return x = max(x, y); }
template <typename T> inline T minz(T& x, T y) { return x = min(x, y); }

int n;

int x[4096], y[4096];
LL d[4096];

LL norm(int x, int y) {
    return 1ll * x * x + 1ll * y * y;
}

int main() {
    while (scanf("%d", &n), n) {
        rep (i, n) {
            scanf("%d%d", x + i, y + i); 
            d[i] = norm(x[i], y[i]); 
        }
        
        vector<tuple<LL, LL, LL>> vt;

        rep (i, n) {
            rep (j, i) {
                LL d1 = d[i], d2 = d[j];
                if (d1 > d2) swap(d1, d2);
                vt.emplace_back(d1, d2, norm(x[i] - x[j], y[i] - y[j]));
            }
        }

        sort(range(vt));

        int m; scanf("%d", &m);
        while (m--) {
            LL a, b, c;
            scanf("%lld%lld%lld", &a, &b, &c);
            if (a > b) swap(a, b);
            auto tup = make_tuple(a, b, c);
            printf("%d\n", int(upper_bound(range(vt), tup) - lower_bound(range(vt), tup)));
        }
    }
    return 0;
}
