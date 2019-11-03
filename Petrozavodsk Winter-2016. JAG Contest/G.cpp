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

int a, b, c, n;
map<tuple<int, int, int>, int> id;
vector<tuple<int, int, int>> cubes;
bool vis[20005];

vector<int> conns;
map<tuple<int, int, int>, int> sid;

void dfs(int id) {
    if (vis[id]) return;
    vis[id] = true; conns.push_back(id);
    int x, y, z; tie(x, y, z) = cubes[id];
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                int xx = x + i, yy = y + j, zz = z + k;
                auto it = ::id.find(make_tuple(xx, yy, zz));
                if (it != ::id.end()) dfs(it->second);
                else if (xx >= 0 and xx < a and yy >= 0 and yy < b and zz >= 0 and zz < c)
                    sid.emplace(make_tuple(xx, yy, zz), sid.size());
            }
        }
    }
}

int fa[1 << 25];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void unite(int u, int v) { u = find(u); v = find(v); fa[u] = v; }

const int dx[6] = {-1, 1, 0, 0, 0, 0};
const int dy[6] = {0, 0, -1, 1, 0, 0};
const int dz[6] = {0, 0, 0, 0, -1, 1};

int work(int id) {
    conns.clear(); sid.clear();
    dfs(id);
    iota(fa, fa + sid.size(), 0);
    for (auto pt : sid) {
        int x, y, z; tie(x, y, z) = pt.first;
        rep (i, 6) {
            auto it = sid.find(make_tuple(x + dx[i], y + dy[i], z + dz[i]));
            if (it != sid.end()) unite(pt.second, it->second);
        }
    }
    int ret = -1;
    rep (i, sid.size()) if (fa[i] == i) ret++;
    return ret;
}

int main() {
    scanf("%d%d%d%d", &a, &b, &c, &n);
    rep (i, n) {
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        id[make_tuple(x, y, z)] = i;
        cubes.emplace_back(x, y, z);
    }
    int ans = 1;
    rep (i, n) if (!vis[i]) ans += work(i);
    printf("%d\n", ans);
    return 0;
}
