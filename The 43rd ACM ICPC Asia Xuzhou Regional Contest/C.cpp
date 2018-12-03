#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else 
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

int n, hn;
int hh[64], dh[64];
double lookup[64][64];
double d[250000];
vector<pair<int, double>> e;

void desc() {
    memcpy(dh, hh, sizeof hh);
    sort(dh, dh + n);
    hn = unique(dh, dh + n) - dh;
    rep (i, n) hh[i] = lower_bound(dh, dh + hn, hh[i]) - dh;
    rep (i, hn) rep (j, hn) {
        if (i != j) 
            lookup[i][j] = hypot(dh[i] - dh[j], 1.0) / fabs(dh[i] - dh[j]);
    }
}

inline int enc(int x, int y, int z) {
    return x << 12 | y << 6 | z;
}

inline tuple<int, int, int> dec(int x) {
    int a, b, c;
    c = x & 0b111111; x >>= 6;
    b = x & 0b111111; x >>= 6;
    a = x;
    return make_tuple(a, b, c);
}

double work() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++)
        scanf("%d", hh + i);
    desc();
    fill(range(d), DBL_MAX);
    d[enc(0, n, 0)] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> q;
    auto touch = [&] (int u, double dist) {
        if (d[u] > dist) {
            d[u] = dist;
            q.emplace(dist, u);
        }
    };
    q.emplace(0.0, enc(0, n, 0));
    while (q.size()) {
        double dd; int u; tie(dd, u) = q.top(); q.pop();
        int x, y, h; tie(x, y, h) = dec(u);
        if (dd > d[u]) continue;
        if (x > 0 and hh[x] == h) touch(enc(x - 1, y, h), 
                dd + (hh[x-1] == hh[x]));
        if (x < n and hh[x+1] == h) touch(enc(x + 1, y, h), 
                dd + (hh[x+1] == hh[x]));
        if (y > 0 and hh[y] == h) touch(enc(x, y - 1, h), 
                dd + (hh[y] == hh[y-1]));
        if (y < n and hh[y+1] == h) touch(enc(x, y + 1, h),
                dd + (hh[y+1] == hh[y]));

        if (x == n or y == n) continue;
        h++;
        if (h >= min(hh[x], hh[x+1]) and h <= max(hh[x], hh[x+1]) and
            h >= min(hh[y], hh[y+1]) and h <= max(hh[y], hh[y+1])) {
            touch(enc(x, y, h), dd + 
                    (lookup[hh[x]][hh[x+1]] + lookup[hh[y]][hh[y+1]]) 
                    * (dh[h] - dh[h-1])
                 );
        }
        h-=2;
        if (h >= min(hh[x], hh[x+1]) and h <= max(hh[x], hh[x+1]) and
            h >= min(hh[y], hh[y+1]) and h <= max(hh[y], hh[y+1])) {
            touch(enc(x, y, h), dd +
                    (lookup[hh[x]][hh[x+1]] + lookup[hh[y]][hh[y+1]])
                    * (dh[h+1] - dh[h]));
        }
    }
    return d[enc(n, 0, 0)] ;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) printf("%.12f\n", work());
    return 0;
}
