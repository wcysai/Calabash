#pragma GCC optimize("fast-math")
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

const int mod = 1000003;

LL powmod(LL b, LL e, LL m) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>=  1;
    }
    return r;
}

inline int addmod(int& x, int y) {
    x += y; if (x >= mod) x -= mod;
    return x;
}

int n, m, p;

namespace poly {
    typedef complex<double> num;

    int base = 1;
    vector<num> roots = {0, 1};
    vector<int> rev = {0, 1};

    void ensure_base(int nbase) {
        if (nbase <= base) return;
        rev.resize(1 << nbase);
        rep (i, 1 << nbase) rev[i] = (rev[i>>1]>>1)|((i&1)<<(nbase-1));
        roots.resize(1<<nbase);
        while (base < nbase) {
            double angle = 2 * acos(-1) / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                roots[i<<1] = roots[i];
                roots[i<<1|1] = polar(1.0, angle*(2*i+1-(1<<base)));
            }
            base++;
        }
    }

    void fft(vector<num>& a, int n = -1) {
        if (n < 0) n = a.size();
        assert((n & (n - 1)) == 0);
        int zeros = __builtin_ctz(n), sh = base - zeros;
        ensure_base(zeros);
        rep (i, n) if (i < (rev[i] >> sh)) swap(a[i], a[rev[i] >> sh]);
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    num z = a[i+j+k] * roots[j+k];
                    a[i+j+k] = a[i+j]-z;
                    a[i+j] += z;
                }
            }
        }
    }

    vector<int> operator * (const vector<int> &a, const vector<int> &b) {
        int sz = a.size() + b.size() - 1;
        vector<int> res(sz);
        int nbase = 0;
        while ((1 << nbase) < sz) nbase++;
        ensure_base(nbase);
        sz = 1 << nbase;
        vector<num> fa(sz), fb(sz);
        rep (i, a.size()) fa[i] = num(a[i] & ((1 << 15) - 1), a[i] >> 15);
        fft(fa, sz);
        rep (i, b.size()) fb[i] = num(b[i] & ((1 << 15) - 1), b[i] >> 15);
        fft(fb, sz);
        double ratio = 0.25 / sz;
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            num ra[2], rb[2];
            rep (s, 2) {
                num a1 = (fa[i] + conj(fa[j])),
                    a2 = (fa[i] - conj(fa[j])) * num(0, -1),
                    b1 = (fb[i] + conj(fb[j])) * ratio,
                    b2 = (fb[i] - conj(fb[j])) * num(0, -ratio);
                ra[s] = a1 * b1 + a2 * b2 * num(0, 1);
                rb[s] = a1 * b2 + a2 * b1;
                swap(i, j);
            }
            rep (s, 2) fa[j] = ra[s], fb[j] = rb[s], swap(i, j);
        }
        fft(fa, sz); fft(fb, sz);
        rep (i, res.size()) res[i] = (
             llround(real(fa[i])) +
            (llround(real(fb[i])) % mod << 15)  +
            (llround(imag(fa[i])) % mod << 30)
        ) % mod;
        return res;
    }

    vector<int> modexp(const vector<int> &vec) {
        vector<int> ret(m);
        rep (i, vec.size()) addmod(ret[i % m], vec[i]);
        return ret;
    }

    vector<int> permute(const vector<int> &vec, int pp) {
        vector<int> ret(m);
        assert(vec.size() == m);
        rep (i, m) addmod(ret[1ll * i * pp % m], vec[i]);
        return ret;
    }
};

vector<int> gf[22];

void printvec(const vector<int> &x ) {
    for (int y : x) cout << y << ',' ;
    cout << endl;

}

int compute_ans(const vector<int>& res) {
    LL ans = 0;
    for (int x : res) ans = (ans + LL(x - 1) * x) % mod;
    ans = ans % mod * ((mod + 1) / 2) % mod;
    return ans;
}

int main() {
    using namespace poly;
    cin >> n >> m >> p;
    gf[0].resize(256);
    for (int i = 'A'; i <= 'Z'; i++) gf[0][i] = 1;
    gf[0] = modexp(gf[0]);

    int sh = p;
    Rep (i, 21) {
        gf[i] = modexp(permute(gf[i-1], sh) * gf[i-1]);
        sh = 1ll * sh * sh % m;
    }

    vector<int> res(m); res[0] = 1;
    rep (i, 21) if (n & (1 << i))
        res = modexp(permute(res, powmod(p, 1 << i, m)) * gf[i]);

    cout << compute_ans(res) << endl;
    return 0;
}
