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

#define next qur

int n;
char str[100005];
int nextc[100005][4], next[100005];
int jp[100005][32];

int main() {
    scanf("%s", str);
    n = strlen(str);
    rep (i, n) {
        if (str[i] == 'e') str[i] = 0;
        else if (str[i] == 'a') str[i] = 1;
        else if (str[i] == 's') str[i] = 2;
        else if (str[i] == 'y') str[i] = 3;
        else assert(0);
    }
    rep (i, 4) nextc[n][i] = nextc[n+1][i] = nextc[n+2][i] = n+1;
    for (int i = n - 1; i >= 0; i--) {
        rep (j, 4) {
            nextc[i][j] = nextc[i+1][j];
            if (str[i] == j) nextc[i][j] = i + 1;
        }
    }
    rep (i, n + 3) next[i] =
        nextc[
            nextc[
                nextc[
                    nextc[i][0]
                ][1]
            ][2]
        ][3];
    rep (i, n + 3) jp[i][0] = next[i];
    for (int f = 1; f < 20; f++) rep (i, n + 3) jp[i][f] = jp[jp[i][f-1]][f-1];
    int m; scanf("%d", &m);
    while (m--) {
        int l, r; scanf("%d%d", &l, &r); l--;
        int ans = 0;
        for (int f = 19; f >= 0; f--) if (jp[l][f] <= r) {
            ans += 1 << f;
            l = jp[l][f];
        }
        printf("%d\n", ans);
    }
    return 0;
}
