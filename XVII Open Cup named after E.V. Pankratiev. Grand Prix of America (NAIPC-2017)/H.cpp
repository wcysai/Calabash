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

const LL mod = 1000000007;

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

int n;
int adj[320][320];
int seq[320];
bool done[320];
LL fact[320], ifact[320];

vector<int> sz;
LL cap[320], cp[320];

LL comb(LL n, LL m) {
    if (m > n) return 0;
    LL ans = fact[n];
    ans = ans * ifact[m] % mod;
    return ans * ifact[n - m] % mod;
}

void calc() {
    cap[0] = 1;
    Rep (i, n) {
        cap[i] = 1;
        for (int u : sz) {
            if (u <= i) {
                cap[i] = cap[i] * powmod(2, u) % mod;
            } else {
                LL tot = 0;
                for (int j = 0; j <= i; j++)
                    tot += comb(u, j);
                tot %= mod;
                cap[i] = cap[i] * tot % mod;
            }
        }
       // _debug("cap[%d]=%lld", i, cap[i]);
    }
    // cap[2] = (powmod(2, n) - 1 - n + mod) % mod;
    LL tot = 0;
    for (int i = n; i; i--) {
        cap[i] = (cap[i] - cap[i-1] + mod) % mod;
        tot += cap[i] * i;
        tot %= mod;
    }
    // cout << tot << endl;
    Rep (i, n) _debug("cap[%d]=%lld", i, cap[i]);
}

void work() {
    for (int i = 0; i < n; i++) {
        map<int, int> mp;
        for (int j = 0; j < i; j++) {
            mp[seq[j]]++;
        }
        sz.clear();
        for (auto p : mp)
            sz.push_back(p.second);
        calc();
        for (int i = 1; i <= n; i++) cp[i] = (cp[i] + cap[i-1]) % mod;
    }
    LL ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = (ans + i * cp[i]) % mod;
        _debug("cp[%d]=%lld", i, cp[i]);
    }
    cout << ans << endl;
}


void init() {
    ifact[0] = fact[0] = 1;
    Rep (i, 300) fact[i] = fact[i-1] * i % mod;
    Rep (i, 300) ifact[i] = powmod(fact[i], mod - 2);
}

int main() {
    init();
    scanf("%d", &n);
    if (n == 1) {
        puts("1");
        return 0;
    }
    rep (i, n) rep (j, n) scanf("%d", &(adj[i][j]));
    for (int i = 1; i < n; i++) {
        for (int u = 0; u < n; u++) {
            int clr = 0;
            if (done[u]) continue;
            for (int v = 0; v < n; v++) {
                if (done[v] || v == u) continue;
                if (clr && adj[u][v] != clr) goto cont1;
                clr = adj[u][v];
            }
            seq[i - 1] = clr;
            done[u] = true;
            goto cont2;
            cont1:;
        }
        assert(0);
        cont2:;
    }
    seq[n] = 0;
    work();
    return 0;
}


/*
4
 0 1 1 1
 1 0 2 2
 1 2 0 3
 1 2 3 0
 */
