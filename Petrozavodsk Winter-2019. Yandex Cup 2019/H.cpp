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
int a[512][512];

int main() {
    scanf("%d", &n);
    rep (i, n) rep (j, n) scanf("%d", &a[i][j]);
    int ans = 0;
    rep (i, n) ans = max(ans, *min_element(a[i], a[i] + n));
    cout << ans << endl;
    return 0;
}
