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
 
const LL mod = 1000000007;
 
LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}
 
LL inv(LL x) { return powmod(x, mod - 2); }
 
int n;
LL a[1024];
 
int main() {
    while (~scanf("%d", &n)) {
        rep (i, n) scanf("%lld", a + i);
        LL ans = 0;
        rep (i, n) {
            LL tot = a[i];
            rep (j, n) if (i != j) {
                tot *= (a[j] * a[j] - a[i] * a[i]) % mod + mod;
                tot %= mod;
            }
            ans += inv(tot);
            ans %= mod;
        }
        printf("%lld\n", ans * inv(2) % mod);
    }
    return 0;
}
