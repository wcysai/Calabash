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

int n;
map<int, int> ax[300005], ay[300005];
const LL mod = 998244353;

void rmedge(int u, int v) {
    ax[u].erase(v);
    ay[v].erase(u);
}

LL get_cycle(int f) {
    int u = f, v, w;
    LL pw1 = 1, pw2 = 1;
    while (ax[u].size()) {
        tie(v, w) = *(ax[u].begin());
        rmedge(u, v);
        pw1 = pw1 * w % mod;
        tie(u, w) = *(ay[v].begin());
        rmedge(u, v);
        pw2 = pw2 * w % mod;
    }
    _debug("%lld %lld", pw1, pw2);
    return (pw1 + pw2) % mod;
}

int main() {
    scanf("%d", &n);
    rep (i, n) {
        rep (_, 2) {
            int u, w; scanf("%d%d", &u, &w); u--;
            ax[i][u] = w;
            ay[u][i] = w;
        }
    }
    queue<int> q;
    auto del = [&] (int u) {
        for (auto p : ax[u]) {
            int v, w; tie(v, w) = p;
            rmedge(u, v);
            if (ay[v].size() == 1) q.push(v);
        }
    };
    rep (i, n) if (ay[i].size() == 1) q.push(i);
    LL ans = 1;
    while (q.size()) {
        int v = q.front(); q.pop();
        assert(ay[v].size() == 1);
        int u, w; tie(u, w) = *(ay[v].begin());
        _debug("%d %d", u, w);
        ans = ans * w % mod;
        del(u);
    }

    int cnt = 0;
    rep (i, n) cnt += bool(ax[i].size()) - bool(ay[i].size());
    if (cnt) {
        puts("0");
        return 0;
    }
    
    rep (i, n) if (ax[i].size()) ans = ans * get_cycle(i) % mod;
    
    cout << ans << endl;

    return 0;
}
