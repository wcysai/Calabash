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

bool arr[128][128], lt[128][128];
int n, m;

int a[128], perm[128];
LL dp[128];

bool check(int i, int j) {
    if (perm[i] > perm[j]) return false;
    for (int k = i + 1; k < j; k++)
        if (perm[k] > perm[i] and perm[k] < perm[j]) return false;

    return true;
}

bool cmp(int u, int v) {
    return lt[u][v];
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        u--; v--;
        if (u > v) swap(u, v);
        arr[u][v] = true;
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i][j])
                lt[j][i] = true;
            else
                lt[i][j] = true;

    rep (i, n) a[i] = i;
    sort(a, a + n, cmp);
    rep (i, n) perm[a[i]] = i;
    LL beg = LLONG_MAX;
    rep (i, n) if (perm[i] < beg) {
        dp[i] = 1;
        beg = perm[i];
    }
    rep (i, n) {
        for (int j = i - 1; j >= 0; j--) {
            if (check(j, i)) dp[i] += dp[j];
        }
    }
    beg = LLONG_MIN;
    LL ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (perm[i] > beg) {
            beg = perm[i];
            ans += dp[i];
        }
    }
    cout << ans << endl;
    return 0;
}
