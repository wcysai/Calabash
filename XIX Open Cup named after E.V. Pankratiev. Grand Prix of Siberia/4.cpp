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
int d[2048][2048];

int main() {
    scanf("%d", &n);
    Rep (i, n) Rep (j, n) scanf("%d", &d[i][j]);
    Rep (k, n) Rep (i, n) {
        for (int j = (k != n and i != n) ? n : 1; j <= n; j++) {
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }
    Rep (i, n) Rep (j, n) printf("%d%c", d[i][j], j == n ? '\n' : ' ');
    return 0;
}
