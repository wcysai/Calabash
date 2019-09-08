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

const LL mod = 998244353;

struct mat {
    LL x[2][2] = { {0, 0}, {0, 0} };

    mat() = default;

    mat(int a, int b, int c, int d) {
        x[0][0] = a; x[0][1] = b; x[1][0] = c; x[1][1] = d;
    }

    mat operator * (const mat& a) {
        mat r;
        rep (i, 2) rep (j, 2) rep (k, 2) r.x[i][k] += x[i][j] * a.x[j][k];
        rep (i, 2) rep (j, 2) r.x[i][j] %= mod;
        return r;
    }
};

mat pe0[1 << 20], pe6[1 << 20], pe12[1 << 22];

void prep() {
    pe0[0] = mat(1, 0, 0, 1);
    pe0[1] = mat(3, 2, 1, 0);
    for (int i = 2; i <= 1000000; i++) pe0[i] = pe0[i-1] * pe0[1];
    pe6[0] = pe0[0];
    pe6[1] = pe0[1000000];
    for (int i = 2; i <= 1000000; i++) pe6[i] = pe6[i-1] * pe6[1];
    pe12[0] = pe0[0];
    pe12[1] = pe6[1000000];
    for (int i = 2; i <= 3000000; i++) pe12[i] = pe12[i-1] * pe12[1];
}

LL query(LL n) {
    LL seg1 = n % 1000000; n /= 1000000;
    LL seg2 = n % 1000000; n /= 1000000;
    LL seg3 = n;
    return (pe0[seg1] * pe6[seg2] * pe12[seg3]).x[1][0];
}

int main() {
    prep();
    int q; scanf("%d", &q);
    LL n; scanf("%lld", &n);
    LL pr = 0;
    while (q--) {
        LL ans = query(n);
        pr ^= ans;
        n ^= ans * ans;
    }
    cout << pr << endl;
    return 0;
}
