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

int n, a;
int head[12], tail[12];

int main() {
    scanf("%d%d", &n, &a); 
    {
        int cur = 1;
        for (int i = 0; i < n; i++) {
            cur = cur * a % 10;
            tail[cur] ++;    
        }
    }

    {
        long double cur = 1.0;
        for (int i = 0; i < n; i++) {
            cur = cur * a;
            if (cur >= 10.0) cur /= 10.0;
            head[int(cur)]++;
        }
    }
    assert(head[0] == 0);
    Rep (i, 9) printf("%d ", head[i]); puts("");
    rep (i, 10) printf("%d ", tail[i]); puts("");
    return 0;
}
