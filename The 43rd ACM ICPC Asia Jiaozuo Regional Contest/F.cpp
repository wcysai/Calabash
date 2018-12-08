#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n, m;
char g[10240][10240];
int dist[10240][10240];
int xs, ys, xt, yt;

void ff() {
    dist[xs][ys] = 0;
    deque<pair<int, int>> dq;
    auto update = [&] (int x, int y, int d) {
        if (g[x][y] == '.') d++;
        else if (g[x][y] != ' ') return;
        if (dist[x][y] > d) {
            dist[x][y] = d;
            if (g[x][y] == ' ') dq.emplace_front(x, y);
            else dq.emplace_back(x, y);
        }
    };
    dq.emplace_back(xs, ys);
    while (dq.size()) {
        int x, y; tie(x, y) = dq.front(); dq.pop_front();
        update(x-1, y, dist[x][y]); update(x+1, y, dist[x][y]);
        update(x, y-1, dist[x][y]); update(x, y+1, dist[x][y]);
    }
}

inline void replace(int i, int j) {
    if (g[i][j] == ' ') g[i][j] = '.';
}

void reconstruct() {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j += 2) {
            replace(4 * i, 6 * j + 3);
            replace(4 * i, 6 * j + 4);
            replace(4 * i, 6 * j + 5);
        }
        for (int j = 1; j < m; j += 2) {
            replace(4 * i + 2, 6 * j + 3);
            replace(4 * i + 2, 6 * j + 4);
            replace(4 * i + 2, 6 * j + 5);
        }
    }
    for (int j = 1; j < m; j++) {
        for (int i = 0; i < 4 * n + 3; i++) {
            replace(i, 6 * j + 1);
        }
    }
}


void work() {
    scanf("%d %d", &n, &m); getchar();
    rep (i, 4 * n + 3) rep (j, 6 * m + 3) g[i][j] = 0, dist[i][j] = INT_MAX;
    rep (i, 4 * n + 3) fgets(g[i], sizeof(g[i]), stdin);
    rep (i, 4 * n + 3) rep (j, 6 * m + 3) {
        if (g[i][j] == 'S') tie(xs, ys) = {i ,j};
        if (g[i][j] == 'T') tie(xt, yt) = {i, j};
    }
    g[xs][ys] = ' ';
    g[xt][yt] = ' ';
    reconstruct();
//    rep (i, 4 * n + 3) puts(g[i]); 
    ff();
    printf("%d\n", (dist[xt][yt] > INT_MAX / 2) ? -1 : (dist[xt][yt]+1));
}   

int main() {
    int T; scanf("%d\n", &T);
    while (T--) work();
    return 0;
}
