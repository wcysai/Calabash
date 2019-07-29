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

LL mulmod(LL a, LL b, LL p) {
    return __int128_t(a) * b % p;
}

LL powmod(LL b, LL e, LL p) {
    LL r = 1;
    while (e) {
        if (e & 1) r = mulmod(r, b, p);
        b = mulmod(b, b, p);
        e >>= 1;
    }
    return r;
}


bool test(LL n){
    if (n < 3) return n == 2;
    const LL a[] = {2ll, 325ll, 9375ll, 28178ll, 450775ll,
        9780504ll, 1795265022ll, LLONG_MAX};
    LL r = 0, d = n-1, x;
    while (~d & 1) d >>= 1, r++;
    for (int i=0; a[i] < n; i++){
        x = powmod(a[i], d, n); // ! powmod must use for 64bit mulmod
        if (x == 1 || x == n-1) goto next;
        rep (i, r) {
            x = mulmod(x, x, n);
            if (x == n-1) goto next;
        }
        return false;
next:;
    }
    return true;
}

LL solve(LL p) {
    LL q = p - 1, r = q;
    while (!test(q)) {
        r = mulmod(r, powmod(q, p - 2, p), p);
        q--;
    }
    _debug("%lld", r);
    return r;

}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        LL x; scanf("%lld", &x);
        printf("%lld\n", solve(x));
    }
    return 0;
}
