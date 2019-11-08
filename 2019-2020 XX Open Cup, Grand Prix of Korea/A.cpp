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
char mat[512][512];

[[noreturn]] void fail() {
    puts("-1");
    exit(0);
}

int check(int x1, int y1, int x2, int y2) {
    char c1 = mat[x1][y1], c2 = mat[x2][y2];
    if (x1 == x2 and y1 == y2) {
        if (c1 == '8') return 0;
        fail();
    } else {
        switch (c1) {
        case '6':
            if (c2 == '9') return 0;
            if (c2 == '6') return 1;
            fail();
        case '7':
            if (c2 == '7') return 1;
            fail();
        case '8':
            if (c2 == '8') return 0;
            fail();
        case '9':
            if (c2 == '9') return 1;
            if (c2 == '6') return 0;
            fail();
        default:
            assert(0);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, n) scanf("%s", mat[i]);
    int ans = 0;
    rep (i, n) rep (j, m) ans += check(i, j, n - 1 - i, m - 1 - j);
    printf("%d\n", ans / 2);
    return 0;
}
