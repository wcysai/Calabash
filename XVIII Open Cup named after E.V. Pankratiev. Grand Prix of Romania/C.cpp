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
char gg[2048][2048], canvas[2048][2048];
int g[2048][2048];

inline bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs(int x, int y, int tag) {
    if (!valid(x, y)) return;
    if (g[x][y] >= 0) return;
    g[x][y] = tag;
    dfs(x-1, y, tag);
    dfs(x, y-1, tag);
    dfs(x+1, y, tag);
    dfs(x, y+1, tag);
}

int vn = 0;

vector<pair<int, int>> adj[2048 * 2048];
bool done[2048 * 2048];
int d[2048 * 2048];
vector<int> pq[2048];

void work() {
    pq[0].push_back(0);
    for (int i = 0; i <= n; i++) {
        while (pq[i].size()) {
            int u = pq[i].back(); pq[i].pop_back();
            if (done[u]) continue;
            done[u] = true;
            d[u] = i;
            for (auto p : adj[u]) {
                int v, w; tie(v, w) = p;
                pq[i + w].push_back(v);
            }
        }
    }
}

void paint() {
    rep (i, n) rep (j, m) canvas[i][j] = '.';
    rep (i, n) rep (j, m) {
            if (g[i][j]) {
                canvas[i + d[g[i][j]]][j] = '#';
            }
        }
    rep (i, n) printf("%s\n", canvas[i]);
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, n) scanf("%s", gg[i]);
    rep (i, n) rep (j, m) {
            if (gg[i][j] == '#') g[i][j] = -1;
            else g[i][j] = 0;
        }
    rep (i, n) rep (j, m) {
            if (g[i][j] == -1) {
                dfs(i, j, ++vn);
            }
        }
    rep (j, m) {
        for (int i = n - 1; i >= 0; i--) {
            if (g[i][j]) {
                adj[0].emplace_back(g[i][j], n - 1 - i);
                break;
            }
        }
    }
    rep (i, n) {
        rep (j, m) {
            if (g[i][j]) {
                for (int y = i - 1; y >= 0; y--) {
                    if (g[y][j]) {
                        adj[g[i][j]].emplace_back(g[y][j], i - 1 - y);
                        break;
                    }
                }
            }
        }
    }
    work();
    paint();
    return 0;
}
/*
 10 10
 ..........
 ..######..
 ..#....#..
 ..#.#..#..
 ..#..#.#..
 ..#....#..
 ..######..
 ..........
 ..#....#..
 .......#..
 */
