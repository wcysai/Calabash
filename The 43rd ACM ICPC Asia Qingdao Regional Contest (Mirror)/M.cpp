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

int cnt[12] = {1, 0, 0, 0, 1, 0, 1, 0, 2, 1};

int func(int x) {
    char str[32]; sprintf(str, "%d", x);
    int ret = 0;
    for (int i = 0; str[i]; i++) {
        ret += cnt[str[i] - '0'];
    }
    return ret;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int x, n; scanf("%d%d", &x, &n);
        while (n-- and x > 1)
            x = func(x);
        //  _debug("n=%d", n);
        if ((n + 1) & 1) x = 1 - x;
        printf("%d\n", x);
    }
    return 0;
}