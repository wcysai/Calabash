#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr,"[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void)0)
#endif
typedef long long LL;
typedef unsigned long long ULL;
template <typename T> inline T maxz(T& x, T y) { return x = max(x, y); }
template <typename T> inline T minz(T& x, T y) { return x = min(x, y); }

int n;
LL a[3008], psum[3008];
LL dp[3008], sval[3008];

void subwork(int r) {
    for (int i = 1; i <= r; i++) {
        sval[i] = min(a[i] + 2 * (psum[r] - psum[i]), 
                      (3 * (r - i + 1) - 2) * a[i] + (psum[r] - psum[i]));
    }
}

int main() {
    while (scanf("%d", &n), n) {
        Rep (i, n) scanf("%lld", a + i);
        partial_sum(a + 1, a + n + 1, psum + 1);
//        Rep (i, n) printf("psum[%d]=%lld\n", i, psum[i]);
        memset(dp, 0, sizeof dp);
        dp[0] = 0;
        Rep (i, n) {
           subwork(i);
//           Rep (j, i) _debug("swork[%d, %d]=%lld", j, i, sval[j]);
           dp[i] = LLONG_MAX;
           LL tot = 0;
           for (int j = i - 1; j >= 0; j--) { 
                tot += sval[j+1];
                dp[i] = min(dp[i], dp[j] + tot + ((i - j) * 4 - 2) * (psum[n] - psum[i]));
           }
//           _debug("dp[%d]=%lld", i, dp[i]);
        }
        cout << dp[n] - psum[n] << endl;
    }
    return 0;
}
