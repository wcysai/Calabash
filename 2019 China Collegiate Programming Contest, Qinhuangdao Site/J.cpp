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
LL a, b;
char buf[10000006], *p;
int fail[10000006];

void construct() {
    int len = n;
    fail[0] = fail[1] = 0;
    for (int i = 1; i < len; i++) {
        int j = fail[i];
        while (j and p[i] != p[j]) j = fail[j];
        fail[i + 1] = p[i] == p[j] ? j + 1 : 0;
    }
}

int main() {
    scanf("%lld%lld", &a, &b);
    scanf("%s", buf);
    p = strchr(buf, '.') + 1;
    n = strlen(p);
    reverse(p, p + n);
    construct();
    LL ans = -LLONG_MAX;
    Rep (i, n) ans = max(ans, a * i - b * (i - fail[i]));
    cout << ans << endl;
    return 0;
}
