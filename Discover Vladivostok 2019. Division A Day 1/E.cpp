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

int n;
char str[1 << 23];
bool x[1 << 23];
bool y[1 << 23];
bool dp[24][1 << 23];

int main() {
    scanf("%d", &n); scanf("%s", str);
    rep (i, n) dp[0][i] = x[i] = str[i] == '-';
    Rep (d, 23) rep (i, n) {
        dp[d][i] = dp[d-1][i];
        if (i & (1 << (d - 1))) dp[d][i] ^= dp[d-1][i - (1 << (d - 1))];
    }
    rep (i, n) putchar(dp[23][i] ? '-' : '+');
    putchar('\n');
    return 0;
}
