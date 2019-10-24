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

const int MAXN = 200005 * 30;

struct Trie {
    int n;
    int tr[MAXN][2];
    int tag[MAXN];

    void init() {
        tag[0] = 0;
        tr[0][0] = tr[0][1] = 0;
        n = 1;
    }

    pair<int, int> query(int bits) {
        if (n == 1) return make_pair(INT_MAX, INT_MAX);
        bitset<32> bs = bits;
        int p = 0;
        for (int id = 30; id >= 0; id--) {
            if (tr[p][bs[id]]) {
                p = tr[p][bs[id]];
                bs[id] = 0;
            } else {
                p = tr[p][!bs[id]];
                bs[id] = 1;
            }
        }
        return make_pair(int(bs.to_ulong()), tag[p]);
    }

    void insert(int bits, int id) {
        bitset<32> bs = bits;
        int p = 0;
        for (int id = 30; id >= 0; id--) {
            if (!tr[p][bs[id]]) {
                tr[n][0] = tr[n][1] = 0;
                tag[n] = 0;
                tr[p][bs[id]] = n++;
            }
            p = tr[p][bs[id]];
        }
        tag[p] = id;
    }
} tr;

int n, rem;
int fa[100005], pr[100005], wpr[100005];
int val[100005];
vector<int> cc[100005];
LL ans = 0;

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void unite(int u, int v, int w) {
    u = find(u); v = find(v);
    if (u == v) return;
    fa[u] = v;
    ans += w;
    rem--;
}

inline void update(int u, pair<int, int> qpr) {
    u = find(u);
    if (wpr[u] > qpr.first) tie(wpr[u], pr[u]) = qpr;
}

int main() {
    scanf("%d", &n); rem = n;
    Rep (i, n) scanf("%d", val + i);
    iota(fa + 1, fa + n + 1, 1);
    while (rem > 1) {
        Rep (i, n) cc[i].clear();
        Rep (i, n) cc[find(i)].push_back(i);
        Rep (i, n) wpr[i] = INT_MAX;
        // pos
        tr.init();
        Rep (i, n) {
            for (int u : cc[i]) update(u, tr.query(val[u]));
            for (int u : cc[i]) tr.insert(val[u], u);
        }
        // neg
        tr.init();
        for (int i = n; i; i--) {
            for (int u : cc[i]) update(u, tr.query(val[u]));
            for (int u : cc[i]) tr.insert(val[u], u);
        }
        Rep (i, n) unite(i, pr[i], wpr[i]);
        _debug("!");
    }
    cout << ans << endl;
    return 0;
}
