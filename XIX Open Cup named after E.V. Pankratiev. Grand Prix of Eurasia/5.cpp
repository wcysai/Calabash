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

int main(){
    int T; scanf("%d", &T);
    while (T--) {
        int t; scanf("%d", &t);
        int a = 1, b = - 1 - t, c = t;
        if (b == 0 || abs(b) > 1000000) {
            b = 1 - t; c = -t;
        }
        printf("%d %d %d\n", a, b, c);
    }
    return 0;
}
