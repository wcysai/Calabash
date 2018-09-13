//
// Created by sy_chen on 18-9-11.
//

#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define Rep(i, n) for (int i = 1; i <=n; i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

typedef long long LL;
typedef unsigned long long ULL;

/*
#define double long double
const double EPS = 1e-6;

int fcmp(double a, double b = 0.0) {
    if (fabs(a - b) < EPS) return 0;
    return a < b ? -1 : 1;
}
*/

int n;
LL x[100005], y[100005];
LL k[100005], rk[100005];

const LL mod = 1003911991, inv2 = (mod + 1) / 2;

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

LL _mod(LL x) {
    return (x + mod) % mod;
}

LL inv(LL x) {
    return powmod(x, mod - 2);
}

int main() {
    scanf("%d", &n);
    assert(inv2 == inv(2));
    rep (i, n + 1) scanf("%lld%lld", x + i, y + i);
    rep (i, n) k[i] = _mod(y[i+1] - y[i]) * inv(x[i+1] - x[i]) % mod;
    for (int i = 1; i < n; i++) {
        rk[i] = _mod(k[i] - k[i-1]) * inv2 % mod;
    }
    LL yval = 0, xx = x[n];
    for (int i = 1; i < n; i++) {
        yval += (xx - x[i]) * rk[i];
        yval %= mod;
    }
    if (_mod(yval - y[n])) {
        cout << "No" << endl;
        return 0;
    }
    if (_mod(k[0] + k[n-1])) {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    return 0;
}
