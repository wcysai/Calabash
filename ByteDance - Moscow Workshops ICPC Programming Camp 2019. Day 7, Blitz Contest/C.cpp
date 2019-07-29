#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n;
int cnt[6];
int a[1 << 20];

int main() {
    int T = 0;
    while (scanf("%d", &n), n) {
        T++;
        memset(cnt ,0, sizeof cnt);
        rep (i, n) scanf("%d", a + i);
        reverse(a, a + n);
        LL ans = 0, denom = n * LL(n - 1) / 2, g;
        rep (i, n) {
            for (int j = a[i] + 1; j < 6; j++) 
                ans += LL(j - a[i]) * LL(j - a[i]) * cnt[j];
            cnt[a[i]]++;
        }
        g = __gcd(ans, denom); ans /= g; denom /= g;
        
        printf("Case #%d: The contest badness is %lld", T, ans);
        if (denom != 1) printf("/%lld", denom); 
        puts(".");
    }
    return 0;
}
