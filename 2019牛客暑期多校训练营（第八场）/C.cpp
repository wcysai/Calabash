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
int m[2048][2048];

void make(int i, int j, int n) {
    if (n == 1) {
        m[i][j] = 1;
        return;
    }
    make(i, j, n / 2);
    make(i + n / 2, j, n / 2);
    make(i, j + n / 2, n / 2);
    make(i + n / 2, j + n / 2, n / 2);
    for (int x = i + n / 2; x < i + n; x++)
        for (int y = j + n / 2; y < j + n; y++)
            m[x][y] = -m[x][y];
}

int main() {
    cin >> n;
    make(0, 0, n);
    rep (i, n) {
        rep (j, n) printf("%d ", m[i][j]);
        puts("");
    }
    return 0;
}
