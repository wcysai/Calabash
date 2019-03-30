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
int a[32];
int r[100005][31];
int pos[100005][31];
double totp[32];
double wt[32];

int main() {
    scanf("%d%d", &m, &n);
    rep (i, n) scanf("%d", &a[i]);
    int totn = accumulate(a, a + n, 0);
    assert(totn == 30);
    rep (i, m) {
        rep (j, totn) scanf("%d", &r[i][j]), r[i][j]--;
        bool rec[32] = {0};
        int ptr = 0;
        rep (j, totn) if (!rec[r[i][j]]) {
            rec[r[i][j]] = true;
            pos[i][r[i][j]] = ptr;
            r[i][ptr] = r[i][j];
            totp[r[i][j]] += ptr;
            ptr++;
        }
    }
    int ord[32]; iota(ord, ord + n, 0);
    sort(ord, ord + n, [] (int i, int j) { return totp[i] > totp[j]; });
    wt[ord[0]] = 1.0; 
    for (int i = 1; i < n; i++) {
        int u = ord[i-1], v = ord[i];
        int nok = 0;
        rep (i, m) if (pos[i][v] < pos[i][u]) nok++;
        if (nok == m) {
            wt[v] = wt[u] * 10000000;
        } else {
            wt[v] = wt[u] * 1.0 * nok / (m - nok);
        }
    }
    rep (i, n) wt[i] /= a[i];
    double nfact = accumulate(wt, wt + n, 0.0);
    rep (i, n) printf("%.307f\n", max(1e-299, min(1.0, wt[i] / nfact))); 
    return 0;
}
