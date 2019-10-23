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
string name[100005], clr[100005];
int p[100005];
string gname[5];
string gclr;
int best[100005][2];
bool good[100005];
int dp[100005][6][6][6];

void update(int &x, int y) { x = max(x, y); }

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        rep (i, n) cin >> name[i] >> clr[i] >> p[i];
        rep (i, 5) cin >> gname[i];
        cin >> gclr;
        vector<string> names(name, name + n);
        sort(range(names)); names.erase(unique(range(names)), names.end());
        m = names.size();
        rep (i, m) best[i][0] = best[i][1] = good[i] = 0;
        rep (i, 5) {
            auto it = lower_bound(range(names), gname[i]);
            if (it == names.end()) continue;
            if (*it != gname[i]) continue;
            good[it - names.begin()] = true;
        }
        rep (i, n) {
            int id = lower_bound(range(names), name[i]) - names.begin();
            update(best[id][clr[i] == gclr], p[i]);
        }
        rep (i, m + 1) rep (j, 6) rep (k, 6) rep (l, 6) dp[i][j][k][l] = INT_MIN;
        dp[0][0][0][0] = 0;
        rep (i, m) rep (sel, 6) rep (ng, sel + 1) rep (nc, sel + 1) {
            int cv = dp[i][sel][ng][nc]; if (cv < 0) continue;
            if (sel < 5) {
                if (best[i][0]) update(dp[i+1][sel+1][ng+good[i]][nc], cv + best[i][0]);
                if (best[i][1]) update(dp[i+1][sel+1][ng+good[i]][nc+1], cv + best[i][1]);
            }
            update(dp[i+1][sel][ng][nc], dp[i][sel][ng][nc]);
        }
        int ans = 0;
        rep (ng, 6) rep (nc, 6) {
            int val = dp[m][5][ng][nc];
            if (val < 0) continue;
            update(ans, val + val * (ng + nc * 2) / 10);
        }
        printf("%d\n", ans);
    }
    return 0;
}
