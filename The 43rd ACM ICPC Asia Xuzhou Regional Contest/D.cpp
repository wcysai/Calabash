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
int a[256];
char mat[256][256];
const int mod = 1'000'000'007;
int f[256][256][256], g[256][256][256], h[256][256][256];
int pf[256][256][256], pg[256][256][256], ph[256][256][256];

int madd(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

void work() {
    memset(f, 0, sizeof f); memset(pf, 0, sizeof pf);
    memset(g, 0, sizeof g); memset(pg, 0, sizeof pg);
    memset(h, 0, sizeof h); memset(ph, 0, sizeof ph);

    scanf("%d", &n);
    Rep (i, n) scanf("%d", a + i);
    Rep (i, n) scanf("%s", mat[i] + 1);
    int ans = 0;
    Rep (i, n) {
        Rep (j, n) {
            Rep (k, n) {
                if (a[i] == a[j] and a[j] == a[k])
                    f[i][j][k] = (1 + ph[i][j][k-1]) % mod;
                if (a[j] == a[k] and mat[a[j]][a[i]] == '1')
                    g[i][j][k] = pf[i-1][j][k];
                if (a[i] == a[j] and mat[a[k]][a[j]] == '1')
                    h[i][j][k] = pg[i][j-1][k];

                pf[i][j][k] = (pf[i-1][j][k] + f[i][j][k]) % mod;
                pg[i][j][k] = (pg[i][j-1][k] + g[i][j][k]) % mod;
                ph[i][j][k] = (ph[i][j][k-1] + h[i][j][k]) % mod;

                ans = (ans + f[i][j][k]) % mod;
            }
        }
    }
    printf("%d\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    while (t--) work();
    return 0;
}
