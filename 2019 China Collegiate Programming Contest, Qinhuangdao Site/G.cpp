
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
char g[16][16];
int w[16][16];
int dp[1 << 24];
typedef bitset<32> bs;

void dp_set(unsigned mask, int val) {
    if (dp[mask] > val) dp[mask] = val;
}

int main() {
    fill(range(dp), INT_MAX);
    scanf("%d", &n);
    rep (i, n) scanf("%s", g[i]);
    rep (i, n) rep (j, n) scanf("%d", &w[i][j]);
    unsigned mterm = (1 << n) - 1, minit = mterm << n;
    dp[minit] = 0;
    for (int mask = (1 << (n + n)) - 1; mask >= 0; mask--) if (__builtin_popcount(mask) == n) {
        bs cur(mask);
        int cost = dp[mask]; if (cost == INT_MAX) continue;
        int bp[32], bw[32], bn = 0;
        int wp[32], ww[32], wn = 0;
        int sp[32], sw[32], sn = 0;
        int x = 0, y = 0;
        rep (i, n + n - 1) {
            if (!cur[i] and cur[i+1]) {
                if (g[x][y] == 'B') {
                    bp[bn] = i; bw[bn] = w[x][y]; bn++;
                } else if (g[x][y] == 'W') {
                    wp[wn] = i; ww[wn] = w[x][y]; wn++;
                } else {
                    sp[sn] = i; sw[sn] = w[x][y]; sn++;
                }
            }
            if (cur[i]) y++; else x++;
        }
        rep (i, bn) {
            bs nmask = cur;
            nmask[bp[i]] = 1; nmask[bp[i]+1] = 0;
            dp_set(nmask.to_ulong(), cost + bw[i]);
        }
        rep (i, wn) {
            bs nmask = cur;
            nmask[wp[i]] = 1; nmask[wp[i]+1] = 0;
            dp_set(nmask.to_ulong(), cost + ww[i]);
        }
        rep (i, sn) {
            bs nmask = cur;
            nmask[sp[i]] = 1; nmask[sp[i]+1] = 0;
            dp_set(nmask.to_ulong(), cost + sw[i]);
        }
        rep (i, bn) rep (j, wn) {
            bs nmask = cur;
            nmask[bp[i]] = 1; nmask[bp[i]+1] = 0;
            nmask[wp[j]] = 1; nmask[wp[j]+1] = 0;
            dp_set(nmask.to_ulong(), cost + abs(bw[i] - ww[j]));
        }
    }
    cout << dp[mterm] << endl;
    return 0;
}
