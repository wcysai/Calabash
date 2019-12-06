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
 
const int NMAX = 1 << 21;
 
typedef complex<double> cplx;
const double PI = 2 * acos(0.0);
struct FFT {
    int rev[NMAX];
    cplx omega[NMAX], oinv[NMAX];
    int K, N;
 
    FFT(int k) {
        K = k; N = 1 << k;
        rep (i, N) {
            rev[i] = (rev[i>>1]>>1)|((i&1)<<(K-1));
            omega[i] = polar(1.0, 2.0 * PI / N * i);
            oinv[i] = conj(omega[i]);
        }
    }
 
    void dft(cplx* a, cplx* w) {
        rep (i, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int l = 2; l <= N; l *= 2) {
            int m = l / 2;
            for (cplx *p = a; p != a + N; p += l) {
                rep (k, m) {
                    cplx t = w[N/l*k] * p[k+m];
                    p[k+m] = p[k] - t; p[k] += t;
                }
            }
        }
    }
 
    void fft(cplx* a) { dft(a, omega); }
    void ifft(cplx* a) {
        dft(a, oinv);
        rep (i, N) a[i] /= N;
    }
    void conv(cplx* a, cplx* b) {
        fft(a); fft(b);
        rep (i, N) a[i] *= b[i];
        ifft(a);
    }
} fft(21);
 
void read_set(bool x[]) {
    int n; scanf("%d", &n);
    rep (i, n) {
        int v; scanf("%d", &v);
        x[v] = true;
    }
}
 
int p, ord, inv[1 << 20];
bool S[1 << 20], V[1 << 20], prop[1 << 20];
int dlog[1 << 20], prt[1 << 20];
cplx A[1 << 21], B[1 << 21];
 
LL sqr(LL x) { x %= p; return x * x % p; }
 
bool primitive_root(LL r) {
    LL cur = r;
    prt[0] = 1;
    for (int i = 1; i < ord; i++) {
        if (cur == 1) return false;
        dlog[cur] = i;
        prt[i] = cur;
        cur = cur * r % p;
    }
    /*
    printf("r=%lld\n", r);
    printf("prt:"); rep (i, ord) printf(" %d", prt[i]); puts("");
    printf("dlg:"); Rep (i, ord) printf(" %d", dlog[i]); puts("");
*/
    return true;
}
 
int eval(LL a, LL b = 1) {
    LL n1 = (sqr(2 * a + 3 * b) + 5 * sqr(a)) % p;
    LL d1 = sqr(3 * a + b);
    LL n2 = (sqr(2 * a + 5 * b) + 3 * sqr(b)) % p;
    LL d2 = sqr(3 * a + 2 * b);
    if (d1 == 0 || d2 == 0) return false;
    LL val = (n1 * inv[d1] + n2 * inv[d2]) % p;
//    if (V[val]) printf("%lld %lld\n", a, b);
    return V[val];
}
 
int main() {
    scanf("%d", &p); ord = p - 1;
    inv[1] = 1;
    for (int i = 2; i < p; i++) {
        inv[i] = (p - LL(p / i) * inv[p % i] % p) % p;
        assert(LL(i) * inv[i] % p == 1);
    }
    read_set(S); read_set(V);
    for (int i = 2; !primitive_root(i); i++);
    LL ans = 0;
    /*
    rep (i, p) if (S[i]) rep (j, p) if (S[j]) if (eval(i, j)) ans++;
    cout << ans << endl; return 0;
    ans = 0;
    */
    if (S[0]) for (int i = 1; i < p; i++) if (S[i]) ans += eval(0, i) + eval(i, 0);
    for (int i = 1; i < p; i++) if (eval(i)) prop[dlog[i]] = true;
    rep (i, ord) if (S[prt[i]]) {
        A[i] += 1.0;
        B[(ord-i)%ord] += 1.0;
    }
    fft.conv(A, B);
    rep (i, ord + ord) if (prop[i%ord]) ans += llround(real(A[i]));
    cout << ans << endl;
    return 0;
}