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

const LL mod = 1'000'000'007;
const int N = mod - 5;
int n;

template <typename T>
void mmult(T a, T b) {
    LL ans[128][128] = {0};
    rep (i, n) rep (j, n) rep (k, n) ans[i][k] += a[i][j] * b[j][k] % mod;
    rep (i, n) rep (j, n) a[i][j] = ans[i][j] % mod;
}

template <typename T1, typename T2>
void apply(T1 a, T2 v) {
    LL res[128] = {0};
    rep (i, n) rep (j, n) res[i] += a[i][j] * v[j] % mod;
    rep (i, n) v[i] = res[i] % mod;
}

LL powm[32][128][128];
LL trans[128][128];

void init_powmod() {
    memcpy(powm[0], trans, sizeof trans);
    for (int i = 1; i < 30; i++) {
        memcpy(powm[i], powm[i-1], sizeof trans);
        mmult(powm[i], powm[i]);
    }
}

template <typename T>
void powmod_vec(int e, T v) {
    while (e) {
        apply(powm[__builtin_ctz(e)], v);
        e &= e - 1;
    }
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

typedef vector<LL> VLL;
typedef vector<VLL> VVLL;

LL gauss(VVLL &a, VVLL &b) {
    const int n = a.size(), m = b[0].size();
    vector<int> irow(n), icol(n), ipiv(n);
    LL det = 1;

    rep (i, n) {
        int pj = -1, pk = -1;
        rep (j, n) if (!ipiv[j]) rep (k, n) if (!ipiv[k])
        if (pj == -1 || a[j][k] > a[pj][pk]) {
            pj = j; pk = k;
        }
        if (a[pj][pk] == 0) return 0;
        ipiv[pk]++;
        swap(a[pj], a[pk]);
        swap(b[pj], b[pk]);
        if (pj != pk) det = (mod - det) % mod;
        irow[i] = pj;
        icol[i] = pk;

        LL c = powmod(a[pk][pk], mod - 2);
        det = det * a[pk][pk] % mod;
        a[pk][pk] = 1;
        rep (j, n) a[pk][j] = a[pk][j]*c%mod;
        rep (j, m) b[pk][j] = b[pk][j]*c%mod;
        rep (j, n) if (j != pk) {
            c = a[j][pk];
            a[j][pk] = 0;
            rep (k, n) a[j][k] = (a[j][k] + mod - a[pk][k] * c % mod) % mod;
            rep (k, m) b[j][k] = (b[j][k] + mod - b[pk][k] * c % mod) % mod;
        }
    }

    for (int j = n - 1; j >= 0; j--) if (irow[j] != icol[j]) {
        for (int k = 0; k < n; k++) swap(a[k][irow[j]], a[k][icol[j]]);
    }
    return det;
}

LL a[128], b[128], x[128];
LL tx[128];
LL mat[128][128];

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%lld", a + i); reverse(a, a + n);
    rep (i, n) scanf("%lld", b + i);
    mt19937 gen(time(NULL));
    rep (i, n - 1) trans[i][i+1] = 1;
    rep (i, n) trans[n-1][i] = a[i];
/*
    rep (i, n) {
        rep (j, n) cout << trans[i][j] << ' ';
        cout << endl;
    }
    */
    init_powmod();
    rep (i, n) x[i] = gen() % mod;
    rep (i, n) {
        memcpy(tx, x, sizeof x);
        powmod_vec(N - b[i], tx);
        rep (j, n) mat[j][i] = tx[j];
    }
    powmod_vec(N, x);
    VVLL M(n), X(n);
    rep (i, n) rep (j, n) M[i].push_back(mat[i][j]);
    rep (i, n) X[i].push_back(x[i]);
    gauss(M, X);
    rep (i, n) cout << X[i][0] << ' '; cout << endl;
    return 0;
}
