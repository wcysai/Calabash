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

const int MAXN = 64;
const LL mod = 1'000'000'007;
int n;
LL sz[MAXN], sumd[MAXN];
int p1[MAXN], p2[MAXN];
LL v1[MAXN], v2[MAXN], len[MAXN];

map<pair<LL, LL>, LL> dist_mem[MAXN];
LL dist(int tr, LL u, LL v) {
    if (tr == 0) return 0;
    if (u > v) swap(u, v);
    if (dist_mem[tr].count(make_pair(u, v))) return dist_mem[tr][make_pair(u, v)];
    int t1 = p1[tr], t2 = p2[tr];
    LL ev1 = v1[tr], ev2 = v2[tr];
    LL ans = 0;
    if (u < sz[t1] and v < sz[t1]) ans = dist(t1, u, v);
    else if (u >= sz[t1] and v >= sz[t1]) ans = dist(t2, u - sz[t1], v - sz[t1]);
    else {
        if (u >= sz[t1]) swap(u, v);
        ans = (dist(t1, u, ev1) + len[tr] + dist(t2, ev2, v - sz[t1])) % mod;
    }
    return dist_mem[tr][minmax(u, v)] = ans;
}

unordered_map<LL, LL> apspd_mem[MAXN];
LL apspd(int tr, LL v) {
    if (tr == 0) return 0;
    if (apspd_mem[tr].count(v)) return apspd_mem[tr][v];
    int t1 = p1[tr], t2 = p2[tr];
    LL ev1 = v1[tr], ev2 = v2[tr];
    LL orig_v = v;
    if (v >= sz[t1]) { v -= sz[t1]; swap(t1, t2); swap(ev1, ev2); }
    LL ans = (apspd(t1, v) + apspd(t2, ev2) +
       (dist(t1, v, ev1) + len[tr]) * (sz[t2] % mod)
    ) % mod;
    return apspd_mem[tr][orig_v] = ans;
}

int main() {
    int T; cin >> T;
    sz[0] = 1;
    while (T--) {
        for (auto& mem : apspd_mem) mem.clear();
        for (auto& mem : dist_mem) mem.clear();
        cin >> n;
        Rep (i, n) {
            cin >> p1[i] >> p2[i] >> v1[i] >> v2[i] >> len[i];
            sz[i] = sz[p1[i]] + sz[p2[i]];
            sumd[i] = (sumd[p1[i]] + sumd[p2[i]] +
                apspd(p1[i], v1[i]) * (sz[p2[i]] % mod) % mod +
                apspd(p2[i], v2[i]) * (sz[p1[i]] % mod) % mod +
                (sz[p1[i]] % mod) * (sz[p2[i]] % mod) % mod * len[i]) % mod;
            cout << sumd[i] << endl;
        }
    }
    return 0;
}
