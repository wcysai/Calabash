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

bool g[2048][2048];
int iso[2048], p[2048];

inline void edge(int u, int v) { g[u][v] = g[v][u] = 1; }

void generate5() {
    rep (i, 5) edge(i, (i + 1) % 5);
    rep (i, 5) iso[i] = i * 2 % 5;
}

void generate4() {
    rep (i, 3) edge(i, i + 1);
    iso[0] = 2; iso[1] = 0; iso[2] = 3; iso[3] = 1;
}

void join4(int x) {
    edge(x, x + 1); edge(x + 1, x + 2); edge(x + 2, x + 3);
    for (int i = x + 1; i < x + 3; i++) rep (j, x) edge(i, j);
    iso[x] = x + 1;
    iso[x+1] = x + 3;
    iso[x+2] = x;
    iso[x+3] = x + 2;
}

int main() {
    int T; scanf("%d", &T);
    Rep (t, T) {
        int n; scanf("%d", &n);
        printf("Case #%d: ", t);
        if (n % 4 >= 2) {
            puts("No");
            continue;
        }
        puts("Yes");
        if (n == 1) {
            puts("0");
            puts("1");
            continue;
        }
        memset(g, 0, sizeof g);
        if (n % 4 == 1) {
            generate5();
            for (int i = 5; i < n; i += 4) join4(i);
        } else {
            generate4();
            for (int i = 4; i < n; i += 4) join4(i);
        }
        rep (i, n) {
            rep (j, n) putchar(g[i][j] ? '1' : '0');
            puts("");
        }
        rep (i, n) p[iso[i]] = i;
        rep (i, n) printf("%d%c", p[i] + 1, i == n - 1 ? '\n' : ' ');
        rep (i, n) rep (j, n) assert(i == j || g[i][j] != g[p[i]][p[j]]);
    }
    return 0;
}
