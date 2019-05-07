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

const int MAXN = 100005;

struct twoSAT {
    int n;
    vector<int> G[MAXN*2];
    bool mark[MAXN*2];
    int S[MAXN*2], c;

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n * 2; i ++) G[i].clear();
        memset(mark, 0, sizeof mark);
    }

    bool dfs(int x) {
        if (mark[x^1]) return false;
        if (mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for (int i = 0; i < G[x].size(); i++) 
            if (!dfs(G[x][i])) return false;
        return true;
    }

    void add_clause(int x, bool xval, int y, bool yval) {
        x = x * 2 + xval;
        y = y * 2 + yval;
        G[x].push_back(y);
    }

    bool solve() {
        for (int i = 0; i < n * 2; i += 2) {
            if (!mark[i] && !mark[i + 1]) {
                c = 0;
                if (!dfs(i)) {
                    while (c > 0) mark[S[--c]] = false;
                    if (!dfs(i + 1)) return false;
                }
            }
        }
        return true;
    }

    inline bool value(unsigned i) { return mark[2*i+1]; }
} sat;

int m, n;
pair<int, bool> pred[10240][3];

int main() {
    scanf("%d%d", &m, &n);
    sat.init(m);
    rep (i, n) {
        rep (j, 3) {
            int id; char clr[3];
            scanf("%d%s", &id, clr);
            pred[i][j] = {id - 1, (clr[0] == 'R' ? true : false)};
        }
        rep (j, 3) {
            rep (k, 3) if (k != j) {
                sat.add_clause(pred[i][j].first, !pred[i][j].second,
                    pred[i][k].first, pred[i][k].second);
            }   
        }
    }
    if (!sat.solve()) {
        puts("-1");
    } else {
        rep (i, m) putchar(sat.value(i) ? 'R' : 'B'); 
    }
    return 0;
}
