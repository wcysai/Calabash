#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
int n, m;
int g[1024][1024];
bool done[1024][1024];
int qs[100005], ans[100005];

inline int id(int i, int j) {
    if (i < 0 or i >= n or j < 0 or j >= m) return -1;
    return i * m + j;
}

struct {
    int fa[1 << 20];
    int sz;

    void init(int n) {
        sz = 0;
        iota(fa, fa + n, 0);
    }
    
    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    void unite(int u, int v) {
        u = find(u); v = find(v);
        fa[u] = v;
        sz -= u != v;
    }

} ufs;

void unite(int x1, int y1, int x2, int y2) {
    int id1 = id(x1, y1), id2 = id(x2, y2);
    if (id1 < 0 or id2 < 0) return; 
    if (!done[x1][y1] or !done[x2][y2]) return;
    ufs.unite(id1, id2);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        memset(done, 0, sizeof done);
        vector<tuple<int, int, int>> pos;
        scanf("%d%d", &n, &m);
        ufs.init(n * m);
        rep (i, n) rep (j, m) {
            scanf("%d", &g[i][j]);
            pos.emplace_back(g[i][j], i, j);
        }
        sort(range(pos), greater<decltype(pos[0])>());
        int q, qq, ptr = 0;
        scanf("%d", &q); qq = q;
        rep (i, q) scanf("%d", qs + i);
        while (q--) {
            while (ptr < pos.size() and get<0>(pos[ptr]) > qs[q]) {
                int x, y; tie(ignore, x, y) = pos[ptr];
                done[x][y] = true; ufs.sz++;
                ptr++;
                unite(x, y, x-1, y);
                unite(x, y, x, y-1);
                unite(x, y, x+1, y);
                unite(x, y, x, y+1);
            }
            ans[q] = ufs.sz;
        }
        rep (i, qq) printf("%d ", ans[i]);
        puts("");
    }
    return 0;
} 
