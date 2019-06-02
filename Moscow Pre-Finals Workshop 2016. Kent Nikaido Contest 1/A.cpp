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
char g[64][64];
int cnt[4];

int main() {
    cin >> n;
    for (int i = n - 1; i >= 0; i--) cin >> g[i];
    rep (i, n) rep (j, n) if (g[i][j] == 'o') cnt[(i-j)&3] ^= 1;
    cout << cnt[0] << endl;
    return 0;
}
