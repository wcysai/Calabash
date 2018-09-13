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
        int p; scanf("%d", &p);
        rep (i, p) {
            rep (j, p) {
                printf("%d%c", (i+j)%p, j==p-1?'\n':' ');
            }
        }
        rep (i, p) {
            rep (j, p) {
                printf("%d%c", int((1ll*i*j)%p), j==p-1?'\n':' ');
            }
        }
    }
    return 0;
}
