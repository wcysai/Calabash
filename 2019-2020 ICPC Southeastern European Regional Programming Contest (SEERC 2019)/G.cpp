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

int n, m, q;
    //  n * m       n * q
char p1[128][128], p2[128][128];
char g[128][128][128];
char pp1[128][128], pp2[128][128];
                // m  * q             m             q
void solve(char g[128][128], char p1[128], char p2[128]) {
    vector<int> id1, id2;
    rep (i, m) if (p1[i] == '1') id1.push_back(i);
    rep (j, q) if (p2[j] == '1') id2.push_back(j);
    if (id1.empty() and id2.empty()) return;
    assert(id1.size() and id2.size());
    int i = 0, j = 0;
    if (id1.size() < id2.size()) {
        rep (_, id2.size() - id1.size())
            g[id1[0]][id2[j++]] = 1;
    } else if (id2.size() < id1.size()) {
        rep (_, id1.size() - id2.size())
            g[id1[i++]][id2[0]] = 1;
    }
    while (i < id1.size() and j < id2.size()) {
        g[id1[i]][id2[j]] = 1;
        i++; j++;
    }
    assert(i == id1.size() and j == id2.size());
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    rep (i, n) scanf("%s", p1[i]);
    rep (i, n) scanf("%s", p2[i]);
    // part 1
    memset(g, 1, sizeof g);
    rep (i, n) rep (j, m) if (p1[i][j] == '0') rep (k, q) g[i][j][k] = 0;
    rep (i, n) rep (k, q) if (p2[i][k] == '0') rep (j, m) g[i][j][k] = 0;
    rep (i, n) rep (j, m) pp1[i][j] = '0';
    rep (i, n) rep (k, q) pp2[i][k] = '0';
    int cnt = 0;
    rep (i, n) rep (j, m) rep (k, q) if (g[i][j][k]) {
        cnt++;
        pp1[i][j] = pp2[i][k] = '1';
    }
    if (memcmp(p1, pp1, sizeof p1) or memcmp(p2, pp2, sizeof p2))
        return puts("-1"), 0;
    printf("%d\n", cnt);
    rep (i, n) rep (j, m) rep (k, q) if (g[i][j][k])
        printf("%d %d %d\n", i, j, k);
    // part 2
    memset(g, 0, sizeof g);
    rep (i, n) solve(g[i], p1[i], p2[i]);
    cnt = 0;
    rep (i, n) rep (j, m) rep (k, q) if (g[i][j][k]) cnt++;
    printf("%d\n", cnt);
    rep (i, n) rep (j, m) rep (k, q) if (g[i][j][k]) printf("%d %d %d\n", i, j, k);
    return 0;
}
