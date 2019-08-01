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

ULL x0, x1, a, b, mod;
string n;

typedef array<array<ULL, 2>, 2> mat;

mat mmult(mat a, mat b) {
    mat r; memset(&r, 0, sizeof r);
    rep (i, 2) rep (j, 2) rep (k, 2) r[i][k] = (r[i][k] + a[i][j] * b[j][k]) % mod;
    return r;
}

mat powmod(mat b, int e) {
    mat r; rep (i, 2) rep (j, 2) r[i][j] = bool(i == j);
    while (e) {
        if (e & 1) r = mmult(r, b);
        b = mmult(b, b);
        e >>= 1;
    }
    return r;
}

mat powmod(mat b) {
    mat r; rep (i, 2) rep (j, 2) r[i][j] = bool(i == j);
    for (char ch : n) {
        int d = ch - '0';
        r = mmult(r, powmod(b, d));
        b = powmod(b, 10);
    }
    return r;
}

int main() {
    cin >> x0 >> x1 >> a >> b >> n >> mod;
    reverse(range(n));
    mat trans = {{{a, b}, {1, 0}}};
    trans = powmod(trans);
    ULL ans = trans[1][0] * x1 + trans[1][1] * x0;
    cout << ans % mod << endl;
    return 0;
}
