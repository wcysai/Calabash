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

bool vis[1 << 20];
int game_over[1 << 20], result[1 << 20];
vector<pair<int, int>> step[4][1 << 20];

#define next aeurgaou

int next;
int g[3][3];

int check() {
    bool has_empty = false;
    rep (i, 3) rep (j, 3)
            if (g[i][j] == 0) has_empty = true;

    rep (i, 3)
        if (g[i][0] and g[i][0] == g[i][1] and g[i][1] == g[i][2])
            return g[i][0];

    rep (j, 3)
        if (g[0][j] and g[0][j] == g[1][j] and g[1][j] == g[2][j])
            return g[0][j];

    if (g[0][0] and g[0][0] == g[1][1] and g[1][1] == g[2][2])
        return g[0][0];

    if (g[2][0] and g[2][0] == g[1][1] and g[1][1] == g[0][2])
        return g[2][0];

    return has_empty ? 0 : 3;
}

unsigned pack() {
    unsigned ans = 0;
    rep (i, 3) rep (j, 3) {
            ans <<= 2;
            ans |= g[i][j];
        }
    ans = ans << 2 | next;
    return ans;
}

void unpack(unsigned state) {
    next = state & 3;
    state >>= 2;
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            g[i][j] = state & 3;
            state >>= 2;
        }
    }
}

int bfs() {
    unsigned state = pack();
    if (vis[state]) return result[state];
    vis[state] = true;
    if ((game_over[state] = check())) {
        result[state] = game_over[state];
        return game_over[state];
    }
    next = 3 - next;
    rep (i, 3) {
        rep (j, 3) {
            if (g[i][j] == 0) {
                g[i][j] = (3 - next);
                int result = bfs();
                step[result][state].push_back({i, j});
                g[i][j] = 0;
            }
        }
    }
    next = 3 - next;
    int res;
    if (step[next][state].size()) res = next;
    else if (step[3][state].size()) res = 3;
    else res = 3 - next;
    return result[state] = res;
}

void init() {
    memset(g, 0, sizeof g); next = 1;
    bfs();
    memset(g, 0, sizeof g); next = 2;
    bfs();
    memset(g, 0, sizeof g);
}

void work() {
    // char msg[64];
    while (true) {
#ifdef  __LOCAL_DEBUG__
        printf("next=%d\n", next);
        rep (i, 3) {
            rep (j, 3) printf("%d ", g[i][j]);
            puts("");
        }
#endif
        unsigned state = pack();
        if (game_over[state]) exit(0);
        if (next == 1) { // my turn
            int x, y;
            if (step[1][state].size()) {
                tie(x, y) = step[1][state].front();
            } else {
                assert(step[3][state].size() > 0);
                tie(x, y) = step[3][state].front();
            }
            printf("%d %d\n", x + 1, y + 1);
            fflush(stdout);
            g[x][y] = next;
        } else { // jury's turn
            int x, y; scanf("%d%d", &x, &y);
            x--; y--;
            g[x][y] = next;
        }
        next = 3 - next;
    }
}

int main() {
    init();
    char str[10]; scanf("%s", str);
    if (str[0] == 'X') next = 1; else next = 2;
    work();
    return 0;
}
