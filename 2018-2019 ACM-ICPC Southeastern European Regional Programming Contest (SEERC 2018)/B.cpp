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

ULL n, d;

ULL c2(ULL x) {
    ULL y = x + 1;
    if (x & 1) y >>= 1; else x >>= 1;
    return x * y;
}

ULL s3(ULL x) {
    ULL fact[3] = {n, n + 1, 2 * n + 1};
    rep (i, 3) if (fact[i] % 2 == 0) {
        fact[i] /= 2;
        break;
    }
    rep (i, 3) if (fact[i] % 3 == 0) {
        fact[i] /= 3;
        break;
    }
    return fact[0] * fact[1] * fact[2];
}

ULL calc() {
    if (n & 1) {
        n /= 2;
        return s3(n);
    } else {
        n /= 2; n--;
        return 3 * c2(n) + s3(n);
    }
}

int main() {
    int a[4]; cin >> a[0] >> a[1] >> a[2] >> n;
    sort(a, a + 3);
    d = unique(a, a + 3) - a;
    ULL ans = calc();
    if (d == 2) ans *= 3; else if (d == 3) ans *= 6;
    cout << ans << endl;
    return 0;
}
