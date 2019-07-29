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

const int mod = 1'000'000'007;

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

LL inv(LL x) {
    return powmod(x, mod - 2);
}

int n, k;
int S[6400][6400];

const int MAXN = 6100;
void init() {
    for (int i = 0; i <= MAXN; i++) {
        S[i][0] = 0;
        S[i][i] = 1;
    }
    for (int i = 1; i <= MAXN; i++) 
        for (int j = 1; j < i; j++) 
            S[i][j] = (1ll * (i-1) * S[i-1][j] + S[i-1][j-1]) % mod;
    /* 
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%d\t", S[i][j]);
        }
        puts("");
    }
    */
}

LL val[8192];

void interp() {
//    _debug("k=%d", k);
    for (int n = 1; n <= 2 * k + 5; n++) {
        for (int i = 0; i <= min(n, k); i++) {
            val[n] += S[n][n-i];
        }
        val[n] %= mod;
    }
}

LL lagrange(int x) {
    LL ans = 0;
    for (int i = 1; i <= 2 * k + 3; i++) {
        LL down = 1, up = val[i];
        for (int j = 1; j <= 2 * k + 3; j++) {
            if (i == j) continue;
            down = down * (i - j) % mod;
            up = up * (x - j) % mod;
        }
        down = (down + mod) % mod;
        up = (up + mod) % mod;
        ans = (ans + up * inv(down)) % mod;
    }
    return ans;
}

int main() {
    init();
    cin >> n >> k;
    interp();
    cout << lagrange(n) << endl;
    return 0;
}
