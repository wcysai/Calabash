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

typedef array<LL, 4> cost_t;

struct {
    int color;
    int child[2][2];
} quad[512000];

int alloc() {
    static int nxt = 1;
    return nxt++;
}

void build(int i, int x, int y, int depth, int color) {
    if (depth == 0) {
        quad[i].color = color;
        return;
    }
    int mask = 1 << (depth - 1);
    int xx = bool(x & mask), yy = bool(y & mask);
    if (quad[i].child[xx][yy] == 0) 
        quad[i].child[xx][yy] = alloc();
    build(quad[i].child[xx][yy], x & ~mask, y & ~mask, depth - 1, color);
}

cost_t getcost(int i, int depth) {
    int dep = depth;
    LL sz = LL(1 << dep) * LL(1 << dep);
    if (i == 0) return {0, 0, 0, 0};
    if (dep == 0) {
        cost_t ans = {0, 1, 1, 1};
        ans[quad[i].color] = 0;
        return ans;
    } else {
        cost_t cost[2][2], ans = {0, 0, 0, 0};
        rep (x, 2) rep (y, 2) 
            cost[x][y] = getcost(quad[i].child[x][y], dep - 1);

        Rep (i, 3) 
            ans[i] = cost[0][0][i] + cost[0][1][i] + cost[1][0][i] + cost[1][1][i];

        int perm[] = {0, 1, 2, 3};
        ans[0] = LLONG_MAX;
        do {
           ans[0] = min(ans[0], 
            cost[0][0][perm[0]] + cost[0][1][perm[1]] + 
            cost[1][0][perm[2]] + cost[1][1][perm[3]]);
        } while (next_permutation(range(perm)));
        return ans;
    }
}

int k, n;

int main() {
	scanf("%d%d", &k, &n);
    alloc();
    rep (_, n) {
        int x, y, c;
        char str[5];
        scanf("%d%d%s", &x, &y, str);
        x--; y--;
        if (str[0] == 'J') c = 1; else if (str[0] == 'O') c = 2; else c = 3;
        build(1, x, y, k, c);
    }
    cout << getcost(1, k)[0] << endl;
	return 0;
}
