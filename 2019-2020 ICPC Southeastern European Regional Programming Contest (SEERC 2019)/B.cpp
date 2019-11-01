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

int n, s1, s2;
struct obj {
    int e1, t1, e2, t2;

    void read() {
        scanf("%d%d%d%d", &e1, &t1, &e2, &t2);
    }

    bool operator < (const obj& a) const {
        return e1 < a.e1;
    }
} objs[512];

LL dp[2][512][512];

void update(LL& x, LL y) {
    x = min(x, y);
}

const LL INF = LLONG_MAX / 2;

void clear(int id) {
    rep (i, s1 + 1) rep (j, s2 + 1) dp[id][i][j] = INF;
}

int main() {
    scanf("%d%d%d", &n, &s1, &s2);
    rep (i, n) objs[i].read();
    sort(objs, objs + n);
    clear(0); clear(1);
    dp[0][0][0] = 0;
    rep (i, n) {
        int cur = i & 1, nxt = cur ^ 1;
        rep (ce1, s1 + 1) rep (ce2, s2 + 1) {
            if (dp[cur][ce1][ce2] == INF) continue;
            update(dp[nxt][ce1][ce2], dp[cur][ce1][ce2]); // don't attack
            if (ce1 < s1) {
                int ne1 = ce1 + objs[i].e1, ne2 = ce2;
                if (ne1 > s1) {
                    ne2 += ne1 - s1;
                    ne1 = s1;
                    ne2 = min(ne2, s2);
                }
                update(dp[nxt][ne1][ne2], dp[cur][ce1][ce2] + objs[i].t1);
            }
            update(dp[nxt][ce1][min(s2, ce2 + objs[i].e2)],
                dp[cur][ce1][ce2] + objs[i].t2); // in level 2
        }
        clear(cur);
    }
    LL ans = dp[n&1][s1][s2];
    if (ans == INF) ans = -1;
    cout << ans << endl;
    return 0;
}
