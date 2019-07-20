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
 
int n, k;
int rk[128];
LL ww[128], w[128];
char gg[128][128], g[128][128];
typedef __int128 bs;
bs adj[128];
 
int main() {
    scanf("%d%d", &n, &k);
    vector<pair<int, int>> wts;
    rep (i, n) scanf("%lld", ww + i), wts.emplace_back(ww[i], i);
    sort(range(wts));
    rep (i, n) rk[wts[i].second] = i;
    rep (i, n) w[rk[i]] = ww[i];
    rep (i, n) scanf("%s", gg[i]);
    rep (i, n) rep (j, n) g[rk[i]][rk[j]] = gg[i][j];
    rep (i, n) rep (j, n) if (g[i][j] == '1') adj[i] |= (bs(1) << j);  
 
    priority_queue<pair<LL, bs>, vector<pair<LL, bs>>, greater<>> q;
    q.emplace(0ll, bs(0));
    while (q.size()) {
        if (--k == 0) {
            cout << q.top().first << endl;
            return 0;
        }
        LL wt; bs clq;
        tie(wt, clq) = q.top(); q.pop();
        int from = n;
        while (from and (clq & (bs(1) << (from - 1))) == 0) from--;
        for (int i = from; i < n; i++)
            if ((adj[i] & clq) == clq)
                q.emplace(wt + w[i], clq | (bs(1) << i));
    }
    cout << -1 << endl;
    return 0;
}
