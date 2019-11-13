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

int h, w, k, q;

struct subsolver {
    char str[100005];
    int next[100005];
    int jp[100005][20];

    void init() {
        scanf("%s", str);
        next[w] = w;
        for (int i = w - 1; i >= 0; i--) {
            next[i] = next[i+1];
            if (str[i] == 'X') next[i] = i;
        }
        rep (i, w) jp[i][0] = next[min(w, next[i] + k)];
        jp[w][0] = w;
        for (int k = 1; k < 20; k++) rep (i, w + 1)
            jp[i][k] = jp[jp[i][k-1]][k-1];
    }

    void print() {
        rep (i, w) printf("%d ", jp[i][0]); puts("");
    }

    int solve(int l, int r) {
        int ans = 0;
        if ((l = next[l]) >= r) return 0;
        for (int k = 19; k >= 0; k--) {
            if (jp[l][k] < r) {
                l = jp[l][k];
                ans += 1 << k;
            }
        }
        return ans + 1;
    }
} solver[15];

int main() {
    scanf("%d%d%d%d", &h, &w, &k, &q);
    rep (i, h) solver[i].init();
    while (q--) {
        int d, l, r; scanf("%d%d%d", &d, &l, &r); l--;
        int ans = 0;
        rep (i, d) ans += solver[i].solve(l, r);
        printf("%d\n", ans);
    }
    return 0;
}
