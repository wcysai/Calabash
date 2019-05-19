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
int x[100005], r[100005];

[[noreturn]] void fail() {
    cout << -1 << endl;
    exit(0);
}

int main() {
    scanf("%d", &n);
    rep (i, n)  scanf("%d%d", x + i, r + i);
    int lptr = 0, xmax = x[0] + r[0];
    for (int i = 1; i < n; i++) {
        if (x[i] > xmax) fail();
        xmax = max(xmax, x[i] + r[i]);
        while (lptr < i and x[lptr] >= x[i] - r[i]) lptr++;
    }
    if (lptr != n - 1) fail();
    cout << (x[n-1] - x[0]) * 3ll << endl;
    return 0;
}
