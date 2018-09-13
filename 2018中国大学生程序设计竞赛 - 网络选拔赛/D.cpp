#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        LL n, a, b, c; scanf("%lld%lld", &n, &a);
        switch (n) {
        case 1:
            printf("%lld %lld\n", 1, a+1);
            break;
        case 2:
            if (a & 1) {
                LL m = (a+1)/2, n = (a-1)/2;
                b = 2*m*n;
                c = m*m +n *n;
            } else {
                LL m = a / 2, n = 1;
                b = m * m - 1;
                c = n*n+m*m;
            }
            printf("%lld %lld\n", b, c);
            break;
        default:
            printf("-1 -1\n");
        }
    }
    return 0;
}
