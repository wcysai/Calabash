#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

const LL mod = 998244353;

LL fact[1024], ifact[1024];
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
    return fact[a] * ifact[b] % mod * ifact[a - b] % mod;
}

int n;
int a[512];
LL dp[512][512];

int main() {
    scanf("%d", &n); Rep (i, n) scanf("%d", a + i);
    fact[0] = 1; Rep (i, 1023) fact[i] = fact[i - 1] * i % mod;
    copy(range(fact), ifact);
    for (LL& x : ifact) x = powmod(x, mod - 2);
    Rep (i, n + 1) dp[i][i] = 1;
    for (int l = 1; l <= n; l++) {
        for (int lpos = 1; lpos + l <= n + 1; lpos++) {
            int rpos = lpos + l;
            for (int mid = lpos; mid < rpos; mid++) {
                if (a[mid] == a[lpos - 1] || a[mid] == a[rpos]) 
                    continue;
                dp[lpos][rpos] += 
                    dp[lpos][mid] * dp[mid+1][rpos] % mod *
                    comb(rpos - lpos - 1, mid - lpos) % mod;
                dp[lpos][rpos] %= mod;
            }
        }
    }
    cout << dp[1][n + 1] << endl;
    return 0;
}
