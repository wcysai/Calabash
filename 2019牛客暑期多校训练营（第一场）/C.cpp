#pragma GCC optimize(3)
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
 
int n, m;
int a[10240];
int cnt, sum;
 
bool check(int th) {
    cnt = 0; sum = m;
    rep (i, n) if (a[i] >= th) {
        cnt++;
        sum -= a[i];
    }
    rep (i, n) if (a[i] >= th)
        if (a[i] * cnt < -sum) return false;
    return true;
}
 
void printfrac(LL num, LL denom) {
    LL g = __gcd(num, denom);
    num /= g; denom /= g;
    if (denom < 0) { num = -num; denom = -denom; }
    if (denom == 1) printf("%lld\n", num); else printf("%lld/%lld\n", num, denom);
}
 
void printans(int th) {
    LL to = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < th) {
            to += 1ll * a[i] * a[i] * cnt * cnt;
        } else {
            to += 1ll * sum * sum;
        }
    }
    printfrac(to, 1ll * cnt * cnt * m * m);
}
 
int main() {
    while (~scanf("%d%d", &n, &m)) {
        rep (i, n) scanf("%d", a + i);
        int l = *min_element(a, a + n);
        int r = *max_element(a, a + n);
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (!check(mid)) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        check(l); printans(l);
    }
    return 0;
}
