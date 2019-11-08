#pragma GCC optimize(3)
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

const int mod = 1'000'000'007;
const int MAXN = 300500 * 4;

LL powmod(LL b, LL e = mod - 2) {
    LL r = 1;
    b = (b % mod + mod) % mod;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

typedef array<array<LL, 2>, 2> mat;

mat operator * (mat a, mat b) {
    mat c = {{}};
    rep (i, 2) rep (j, 2) rep (k, 2) c[i][k] += a[i][j] * b[j][k];
    rep (i, 2) rep (j, 2) c[i][j] %= mod;
    return c;
}

mat inv(mat a) {
    LL det = powmod(a[0][0] * a[1][1] - a[0][1] * a[1][0]);
    mat ret;
    ret[0][0] = a[1][1] * det % mod;
    ret[1][0] = (mod - a[1][0]) * det % mod;
    ret[0][1] = (mod - a[0][1]) * det % mod;
    ret[1][1] = a[0][0] * det % mod;
    return ret;
}

mat pref[300005], cur[300005];
int lead[300005];
int gid = 1;

list<vector<LL>> gs;

void group0() {
    lead[gid] = lead[gid-1];
    pref[gid] = mat{{{2, 0}, {0, 1}}} * pref[gid - 1];
    cur[gid] = mat{{{2, 1}, {0, 1}}};
    gs.emplace_back(vector<LL>{0});
    gid++;
}

void group1(int k) {
    lead[gid] = gid;
    pref[gid] = mat{{{1, k}, {0, 1}}} * pref[gid - 1];
    cur[gid] = mat{{{1, 0}, {0, 1}}};
    gs.back().emplace_back(gs.back().back() + k);
    gid++;
}

int query(LL id) {
    int ret = gid;
    for (auto it = gs.rbegin(); it != gs.rend(); it++) {
        const vector<LL>& vec = *it;
        if (id >= vec.back())  {
            id -= vec.back();
            ret -= vec.size();
            if (id & 1) return ret; else id /= 2;
            if (id == 0) return lead[ret];
        } else {
            id = vec.back() - 1 - id;
            auto it = upper_bound(range(vec), id);
            return ret - (vec.end() - it);
        }
    }
    return 0;
}

int main() {
    int q; scanf("%d", &q);
    pref[0] = cur[0] = mat{{{1, 0}, {0, 1}}};
    gs.emplace_back(vector<LL>{0});
    while (q--) {
        int op; scanf("%d", &op);
        if (op == 1) {
            int k; scanf("%d", &k);
            if (k == 0) group0(); else group1(k);
        } else if (op == 2) {
            int g, x; scanf("%d%d", &g, &x);
            auto mat = pref[gid-1] * inv(pref[g]) * cur[g];
            printf("%lld\n", (mat[0][0] * (x - 1) + mat[0][1]) % mod);
        } else {
            int id; scanf("%d", &id);
            printf("%d\n", query(id));
        }
    }
    return 0;
}
