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

int n, m, T;
LL mod = 1'000'000'007;

inline LL _mod(LL x) {
    if (x > 7'000000'000000'000000) return x % mod;
    return x;
}

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

LL inv(LL x) {
    return powmod(x, mod - 2);
}

struct matrix {
    int a[70][70] = {0};

    void set_identity() {
        rep (i, n) rep (j, n) a[i][j] = (i == j);
    }

    matrix operator * (const matrix& rhs) {
        matrix ans;
        LL tmp[70][70] = {0};
        rep (i, n) rep (j, n) rep (k, n)
                    tmp[i][k] = _mod(tmp[i][k] + LL(a[i][j]) * rhs.a[j][k]);
        rep (i, n) rep (j, n) ans.a[i][j] = tmp[i][j] % mod;
        return ans;
    }

    void apply(int b[]) {
        LL r[80] = {0};
        rep (i, n) rep (j, n)
            r[j] = _mod(r[j] + LL(b[i]) * a[i][j]);
        rep (i, n) b[i] = r[i] % mod;
    }

    int inner_product(int b[]) {
        LL ans = 0;
        rep (i, n) ans = _mod(ans + LL(b[i]) * a[i][n - 1]);
        return ans % mod;
    }

    void get(int pos, int b[]) {
        rep (i, n) b[i] = a[i][pos];
    }

    void print() {
        rep (i, n)
            rep (j, n)
                printf("%d%c", a[i][j], j == n - 1 ? '\n' : ' ');
    }
} A, power[205];

int deg[128];
char arr[128][128];

void init() {
    power[0].set_identity();
    Rep (i, 203) power[i] = power[i-1] * A;
}

int last_update_time = 1;
int cur[80];

vector<int> ins[2000006];

int main() {
    scanf("%d%d%d", &n, &m, &T);
    rep (i, n) scanf("%s", arr[i]);
    rep (i, n) rep (j, n) if (arr[i][j] == '1') deg[i]++;
    _debug("!");
    rep (i, n) {
        int dinv = inv(deg[i]);
        rep (j, n)
            if (arr[i][j] == '1') A.a[i][j] = dinv;
    }

    // A.print();
    init();
    // rep (i, 6) power[i].print();
    // _debug("!");
    rep (i, m) {
        int t, v; scanf("%d%d", &t, &v); v--;
        ins[t].push_back(v);
    }
    int ans = 0;
    Rep (i, T) {
        if (ins[i].size() or i - last_update_time >= 200) {
            power[i - last_update_time].apply(cur);
            for (int v : ins[i])
                cur[v] = (cur[v] + 1) % mod;
            last_update_time = i;
        }
        // printf("%d: ", i);
        // rep (i, n) printf("%d ", cur[i]); puts("");
        int cans = power[i - last_update_time].inner_product(cur);
        // power[i - last_update_time].print();
        // printf("cans = %d\n", cans);
        ans ^= cans;
    }
    printf("%d", ans);
    return 0;
}

/*
3 1 6
110
011
101
1 1

1: 1 0 0
1 0 0
0 1 0
0 0 1
cans = 0
2: 1 0 0
500000004 500000004 0
0 500000004 500000004
500000004 0 500000004
cans = 500000004
3: 1 0 0
250000002 500000004 250000002
250000002 250000002 500000004
500000004 250000002 250000002
cans = 500000004
4: 1 0 0
250000002 375000003 375000003
375000003 250000002 375000003
375000003 375000003 250000002
cans = 375000003
5: 1 0 0
812500006 812500006 375000003
375000003 812500006 812500006
812500006 375000003 812500006
cans = 812500006
6: 1 0 0
93750001 812500006 93750001
93750001 93750001 812500006
812500006 93750001 93750001
cans = 812500006
375000003
 */
