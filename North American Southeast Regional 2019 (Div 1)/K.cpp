#pragma GCC optimize("fast-math")
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

typedef complex<double> point;
int n;
point pos[2048];
double args[2048][2048];
vector<pair<double, int>> ord[2048];
int ans;
double tot_ang;
set<pair<int, int>> vis;
int occ[100005];
vector<pair<int, int>> ops;

void work(int i, int j) {
  //  _debug("%d %d", i, j);
    if (vis.count(make_pair(i, j))) return ;
    vis.emplace(i, j); ops.emplace_back(i, j);
    int k1 = upper_bound(range(ord[j]), make_pair(args[i][j], INT_MAX))
        - ord[j].begin(); k1 = ord[j][k1 % (n - 1)].second;
    double ang1 = args[j][k1] - args[i][j];
    if (ang1 < 0) ang1 += 2 * acos(-1);
    int k2 = upper_bound(range(ord[j]), make_pair(args[j][i], INT_MAX))
        - ord[j].begin(); k2 = ord[j][k2 % (n - 1)].second;
    double ang2 = args[j][k2] - args[j][i];
    if (ang2 < 0) ang2 += 2 * acos(-1);
//    _debug("%d: %f, %d: %f", k1, ang1, k2, ang2);
    int k = ang1 < ang2 ? k1 : k2;
    tot_ang += min(ang1, ang2);
    work(j, k);
}

int main() {
    scanf("%d", &n);
    rep (i, n) {
        int x, y; scanf("%d%d", &x, &y);
        pos[i] = point(x, y);
    }
    rep (i, n) {
        rep (j, n) args[i][j] = arg(pos[j] - pos[i]);
        rep (j, n) if (i != j) ord[i].emplace_back(args[i][j], j);
        sort(range(ord[i]));
    }
    rep (i, n) rep (j, n) if (i != j and !vis.count(make_pair(i, j))) {
    //    _debug("!!!");
        tot_ang = 0;
        work(i, j);
      //  _debug("tot_ang=%f", tot_ang);
        int cnt = lround(2 * acos(-1) / tot_ang);
        for (auto p : ops) occ[p.first]++;
        for (auto p : ops) {
            ans = max(ans, occ[p.first] * cnt);
            occ[p.first] = 0;
            ops.clear();
        }
    }
    cout << ans << endl;
    return 0;
}
