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

const int N = 64;
const int INF = 0x3f3f3f3f;
int n;
int cost[N][N];
int lx[N], ly[N], match[N], slack[N], pre[N];
bool vy[N];
void augment(int root) {
    memset(vy, 0, sizeof vy);
    memset(slack, INF, sizeof slack);
    int py;
    match[py = 0] = root;
    do {
        vy[py] = true;
        int x = match[py], delta = INF, yy;
        for (int y = 1; y <= n; y++) {
            if (!vy[y]) {
                if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
                    slack[y] = lx[x] + ly[y] - cost[x][y];
                    pre[y] = py;
                }
                if (slack[y] < delta) {
                    delta = slack[y];
                    yy = y;
                }
            }
        }
        for (int y = 0; y <= n; ++y) {
            if (vy[y]) {
                lx[match[y]] -= delta;
                ly[y] += delta;
            }
            else
                slack[y] -= delta;
        }
        py = yy;
    } while (match[py] != -1);
    do {
        int y = pre[py];
        match[py] = match[y];
        py = y;
    } while (py);
}

void km() {
    for (int i = 1; i <= n; ++i) {
        lx[i] = ly[i] = 0;
        match[i] = -1;
        for (int j = 1; j <= n; ++j)
            lx[i] = max(lx[i], cost[i][j]);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) augment(i);
}

int g[64][64], gg[64][64];
int main() {
    cin >> n;
    Rep (i, n) Rep (j, n) cin >> g[i][j];
    memcpy(gg, g, sizeof g);
    Rep (i, n) Rep (j, n) cost[i][j] = gg[i][j];
    km();

    LL ans = 0;
    Rep (i, n) Rep (j, n) ans += (g[i][j] = lx[i] + ly[j]);
    Rep (i, n ) Rep (j, n ) assert(g[i][j] >= gg[i][j]);
    cout << ans << endl;
    Rep (i, n) Rep (j, n) cout << g[i][j] << (j == n ? '\n' : ' ');
    return 0;
}
