#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)

typedef long long LL;
typedef unsigned long long ULL;

int w, h;
char g[512][512], gg[512][512];

bool valid(int x, int y) {
    return x >= 0 and x < w and y >= 0 and y < h;
}

void rec(int x, int y) {
    if (!valid(x, y)) return;
    if (g[x][y] != '.') return;
    g[x][y] = '!';
    if (g[x+1][y] == '.') rec(x+1, y);
    else if (g[x+1][y] == '#') {
        rec(x, y-1);
        rec(x, y+1);
    }
}

int main() {
    scanf("%d%d", &w, &h);
    rep (i, w) scanf("%s", g[i]);
    memcpy(gg, g, sizeof g);
    rep (i, h) rec(0, i);
    // rep (i, w) printf("%s\n", g[i]);
    rep (i, w) {
        rep (j, h) {
            if (g[i][j] == '.') {
                gg[i][j] = 'X';
                puts("Yes");
                rep (i, w) printf("%s\n", gg[i]);
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}
