#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr,"[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void)0)
#endif
typedef long long LL;
typedef unsigned long long ULL;
template <typename T> inline T maxz(T& x, T y) { return x = max(x, y); }
template <typename T> inline T minz(T& x, T y) { return x = min(x, y); }

LL mod = 242'121'643;

LL fact[128], ifact[128];

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

LL comb(LL a, LL b) {
    if (a < 0 or b < 0 or a - b < 0) return 0;
    return fact[a] * ifact[b] % mod * ifact[a-b] % mod;
}

void init() {
    ifact[0] = fact[0] = 1;
    Rep (i, 110) fact[i] = fact[i-1] * i%mod;
    Rep (i, 110) ifact[i] = powmod(fact[i], mod - 2);
}

int n, k;
int a[128];

int main() {
    init();
    while (scanf("%d%d", &n, &k), n) {
        int n0 = 0, n1 = 0;
        rep (i, n) {
            scanf("%d", a + i);
            if (a[i] == 1) n1++; else n0++;
        }
        // _debug("n1=%d, n0=%d", n1, n0);
        LL ans = 0;
        for (int i = 1; i <= 100; i += 2) {
        //    printf("c(%d, %d) * c(%d, %d)\n", n1, i, n0, k-i);
            ans += comb(n1, i) * comb(n0, k - i) % mod;
        }
        ans %= mod;
        cout << ans << endl;
    }
    return 0;
}
