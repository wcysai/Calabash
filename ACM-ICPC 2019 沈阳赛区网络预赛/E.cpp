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

int n, p;
int c[1024][1024];
int b[1 << 20];
int cnt[1 << 20];

int solve() {
    c[0][0] = 1;
    Rep (i, p) c[i][0] = c[i][i] = 1;
    Rep (i, p) for (int j = 1; j < i; j++) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % p;
    b[0] = 1;
    rep (i, p) {
        b[i+1] = 0;
        for (int k = 0; k <= i; k++) b[i+1] = (b[i+1] + b[k] * c[i][k]) % p;
    }
    rep (i, max(n, p) + 1) cnt[i] = 0;
    cnt[n] = 1;
    for (int i = n; i >= p; i--) {
        cnt[i] %= p;
        cnt[i-p] += cnt[i];
        cnt[i-p+1] += cnt[i];
    }
    int ans = 0;
    rep (i, p) ans = (ans + cnt[i] % p * b[i]) % p;
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &p);
        printf("%d\n", solve());
    }
    return 0;
}
