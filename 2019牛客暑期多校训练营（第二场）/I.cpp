#pragma GCC optimize(3)
#ifndef __LOCAL_DEBUG__
#pragma GCC target("avx512f", "avx2", "avx")
#endif
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
int a[63][63], sum[63][63];
int qsum[63][63][63][63];
int vminpref[63][63][63], vminsuf[63][63][63];
int hminpref[63][63][63], hminsuf[63][63][63];
 
void prep2() {
    memset(vminpref, 0, sizeof vminpref);
    memset(hminpref, 0, sizeof vminpref);
    memset(vminsuf, 0, sizeof vminpref);
    memset(hminsuf, 0, sizeof vminpref);
    for (int xl = 0; xl < n; xl++) for (int xr = xl + 1; xr <= n; xr++) {
        for (int l = 1; l <= m; l++)
            hminpref[xl][xr][l] = min(qsum[xl][xr][0][l], hminpref[xl][xr][l-1]);
        for (int l = m - 1; l >= 0; l--)
            hminsuf[xl][xr][l] = min(qsum[xl][xr][l][m], hminsuf[xl][xr][l+1]);
    }
 
    for (int yl = 0; yl < m; yl++) for (int yr = yl + 1; yr <= m; yr++) {
        for (int l = 1; l <= n; l++)
            vminpref[yl][yr][l] = min(qsum[0][l][yl][yr], vminpref[yl][yr][l-1]);
        for (int l = n - 1; l >= 0; l--)
            vminsuf[yl][yr][l] = min(qsum[l][n][yl][yr], vminsuf[yl][yr][l+1]);
    }
}
 
void psum() {
    memset(sum, 0, sizeof sum);
    rep (i, n) rep (j, m) sum[i+1][j+1] = sum[i+1][j] + a[i][j];
    rep (i, n) rep (j, m) sum[i+1][j+1] += sum[i][j+1];
 
    for (int xl = 0; xl <= n; xl++) for (int xr = xl; xr <= n; xr++)
    for (int yl = 0; yl <= m; yl++) for (int yr = yl; yr <= m; yr++)
        qsum[xl][xr][yl][yr] =
            sum[xr][yr] - sum[xl][yr] - sum[xr][yl] + sum[xl][yl];
    return ;
#ifdef __LOCAL_DEBUG__
    rep (i, n+1) {
        rep (j, m+1) cout << sum[i][j] << ' ';
        cout << endl;
    }
#endif
}
 
int solve4() { // T
    prep2();
    int ret = 0;
    for (int xl = 0; xl <= n; xl++) for (int xr = xl; xr <= n; xr++)
    for (int yl = 0; yl <= m; yl++) for (int yr = yl; yr <= m; yr++) {
        int ans = qsum[0][n][yl][yr] + qsum[xl][xr][0][yl];
        ans -= vminpref[yl][yr][xl] + vminsuf[yl][yr][xr] +
               hminpref[xl][xr][yl];
        int minm = 0;
        for (int l = yl; l <= yr; l++) minm = min(minm, qsum[xl][xr][yl][l]);
        ret = max(ret, ans - minm);
    }
    return ret;
}
 
int solve3() { // diagonal
    static int minpref[63][63][63];
    static int minsuf[63][63][63];
    memset(minpref, 0, sizeof minpref); memset(minsuf, 0, sizeof minsuf);
    for (int xl = 0; xl < n; xl++) for (int xr = xl + 1; xr <= n; xr++) {
        for (int l = 1; l <= m; l++)
            minpref[xl][xr][l] = min(qsum[xl][xr][0][l], minpref[xl][xr][l-1]);
        for (int l = m - 1; l >= 0; l--)
            minsuf[xl][xr][l] = min(qsum[xl][xr][l][m], minsuf[xl][xr][l+1]);
    }
    int ans = 0;
    for (int x1l = 0; x1l <= n; x1l++) for (int x2l = x1l; x2l <= n; x2l++)
    for (int x1r = x2l; x1r <= n; x1r++) for (int x2r = x1r; x2r <= n; x2r++)
        for (int yl = 0; yl <= m; yl++) for (int yr = yl; yr <= m; yr++) {
            int cur = qsum[x1l][x1r][0][yr] + qsum[x2l][x2r][yl][m];
            cur -= qsum[x2l][x1r][yl][yr] * 2;
            cur -= minpref[x1l][x1r][yl];
            cur -= minsuf[x2l][x2r][yr];
            ans = max(ans, cur);
        }
    return ans;
}
 
int solve2() { // row disjoint
    int ans[63][63]; memset(ans, 0, sizeof ans);
    for (int xl = 0; xl < n; xl++) for (int xr = xl + 1; xr <= n; xr++) {
        int minpre = 0;
        for (int l = 0; l <= m; l++) {
            int cur = qsum[xl][xr][0][l];
            minpre = min(minpre, cur);
            ans[xl][xr] = max(ans[xl][xr], cur - minpre);
        }
    }
    int ret = 0;
    for (int x1l = 0; x1l <= n; x1l++)
    for (int x1r = x1l + 1; x1r <= n; x1r++)
    for (int x2l = x1r; x2l <= n; x2l++)
    for (int x2r = x2l + 1; x2r <= n; x2r++) {
        ret = max(ret, ans[x1l][x1r] + ans[x2l][x2r]);
    }
    return ret;
}
 
int solve1() { // contain
    int ans = 0;
    static int minr[63][63][63][63];
    for (int l1 = 1; l1 <= n; l1++) for (int xl = 0; xl + l1 <= n; xl++)
    for (int l2 = 1; l2 <= m; l2++) for (int yl = 0; yl + l2 <= m; yl++) {
        int xr = xl + l1, yr = yl + l2;
        int cur = qsum[xl][xr][yl][yr];
        minr[xl][xr][yl][yr] = min({
            cur,
            minr[xl+1][xr][yl][yr],
            minr[xl][xr-1][yl][yr],
            minr[xl][xr][yl+1][yr],
            minr[xl][xr][yl][yr-1]
        });
        ans = max(ans, cur - minr[xl][xr][yl][yr]);
    }
    return ans;
}
 
int solve0() { // cross;
    prep2();
    int ans = 0;
    for (int xl = 0; xl <= n; xl++) for (int xr = xl + 1; xr <= n; xr++)
    for (int yl = 0; yl <= m; yl++) for (int yr = yl + 1; yr <= m; yr++) {
        int tot = qsum[xl][xr][0][m]+qsum[0][n][yl][yr]-qsum[xl][xr][yl][yr]*2;
        tot -= hminpref[xl][xr][yl] + hminsuf[xl][xr][yr];
        tot -= vminpref[yl][yr][xl] + vminsuf[yl][yr][xr];
        ans = max(ans, tot);   
    }
    return ans;
}
 
void transpose() {
    int aa[63][63] = {0};
    rep (i, n) rep (j, m) aa[j][i] = a[i][j];
    memcpy(a, aa, sizeof a);
    swap(n, m); psum();
}
 
void reflect() {
    rep (i, n) reverse(a[i], a[i] + m);
    psum();
}
 
int main() {
    scanf("%d%d", &n, &m);
    rep (i, n) rep (j, m) scanf("%d", &a[i][j]);
    psum();
    int ans = max(solve0(), solve1());
 
    ans = max(ans, solve2());
    transpose();
    ans = max(ans, solve2());
     
    ans = max(ans, solve3());
    reflect();
    ans = max(ans, solve3());
     
    ans = max(ans, solve4());
    reflect();
    ans = max(ans, solve4());
    transpose();
    ans = max(ans, solve4());
    reflect();
    ans = max(ans, solve4());
 
    cout << ans << endl;
    return 0;
}
