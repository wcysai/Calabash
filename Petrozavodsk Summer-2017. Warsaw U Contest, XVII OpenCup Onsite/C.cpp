#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARG__)
#else
#define _debug(fmt, ...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n, m;
int nxt[100005];
int first[100005], last[100005];
int a[100005];

int sz;
LL lth[5005];
LL dp[5120][5120];

LL work(int pos) {
    sz = 0;
    while (nxt[pos] != -1) {
        lth[++sz] = nxt[pos] - pos;
        int tmp = nxt[pos];
        nxt[pos] = -1;
        pos = tmp;
    }
    Rep (i, sz) dp[i][i] = lth[i];
    partial_sum(lth + 1, lth + sz + 1, lth + 1);
    for (int len = 1; len < sz; len++) {
        for (int l = 1; l + len <= sz; l++) {
            int r = l + len;
            dp[l][r] = lth[r] - lth[l-1] + max(dp[l+1][r], dp[l][r-1]);
        }
    }
    return dp[1][sz];
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, n) nxt[i] = -1;
    rep (i, n) scanf("%d", a + i);
    rep (i, n) last[a[i]] = i + 1;
    for (int i = n - 1; i >= 0; i--) first[a[i]] = i;
    Rep (i, m)
        nxt[first[i]] = last[i];
    LL ans = 0;
    rep (i, n) {
        if (nxt[i] != -1) ans += work(i);
    }
    cout << ans << endl;
    return 0;
}
