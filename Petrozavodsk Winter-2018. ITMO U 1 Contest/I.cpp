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

const int NMAX = 1 << 20;

const LL P = 998244353, G = 3;

struct NTT {
    int rev[NMAX];
    LL omega[NMAX], oinv[NMAX];
    LL g, g_inv;
    int K, N;

    LL powmod(LL b, LL e) {
        LL r = 1;
        while (e) {
            if (e & 1) r = r * b % P;
            b = b * b % P;
            e >>= 1;
        }
        return r;
    }

    explicit NTT (int k) {
        K = k; N = 1 << k;
        g = powmod(G, (P-1) / N);
        g_inv = powmod(g, N-1);
        omega[0] = oinv[0] = 1;
        rep (i, N) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (K - 1));
            if (i) {
                omega[i] = omega[i-1] * g % P;
                oinv[i] = oinv[i-1] * g_inv % P;
            }
        }

    }

    void _ntt(LL *a, LL *w) {
        rep (i, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int l = 2; l <= N; l *= 2) {
            int m = l / 2;
            for (LL *p = a; p != a + N; p += l) {
                rep (k, m) {
                    LL t = w[N / l * k] * p[k + m] % P;
                    p[k + m] = (p[k] - t + P) % P;
                    p[k] = (p[k] + t) % P;
                }
            }
        }
    }

    void ntt(LL *a) {_ntt(a, omega);}
    void intt(LL *a) {
        LL inv = powmod(N, P - 2);
        _ntt(a, oinv);
        rep (i, N) a[i] = a[i] * inv % P;
    }
/*
    void conv(LL* a, LL* b) {
        ntt(a); ntt(b);
        rep (i, N) a[i] = a[i] * b[i] % P;
        intt(a);
    }
*/
    void conv2(LL* a, LL* b) {
        ntt(a);
        rep (i, N) a[i] = a[i] * b[i] % P;
        intt(a);
    }
} ntt(20);

int n, m, c;
LL x[1 << 20], y[1 << 20];
int perm[1 << 20];
bool ok[1 << 20];
mt19937_64 gen(time(NULL));

void epoch() {
    memset(y, 0, sizeof y);
    rep (i, n) {
        LL r = gen() % P;
        y[i] += r;
        y[perm[i]] -= r;
    }
    rep (i, n) {
        y[i] %= P; if (y[i] < 0) y[i] += P;
    }
    reverse(y, y + n);
    ntt.conv2(y, x);
    rep (i, m - n + 1) {
        ok[i] |= bool(y[i + n - 1]);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &c);
    rep (i, n) {
        scanf("%d", perm + i);
        perm[i]--;
    }
    rep (i, m) scanf("%lld", x + i);
    ntt.ntt(x);
    rep (_, 5) epoch();
    rep (i, m - n + 1) {
        putchar('0' + !ok[i]);
    }
    return 0;
}

/*
3 7 3
3 2 1
1 2 1 3 1 2 1
 */

/*
3 5 1
2 1 3
1 1 2 2 3
 */
