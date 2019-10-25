#pragma GCC optimize("fast-math")
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

const int mod = 2017;
int c[2048][2048];

void init() {
    for (int i = 0; i <= 2017; i++) for (int j = 0; j <= i; j++)
        if (j == 0 or j == i) c[i][j] = 1; else c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
}

int cb(int x, int y) {
    if (x < y) return 0;
    int ans = 1;
    while (x or y) {
        ans = ans * c[x % mod][y % mod] % mod;
        x /= mod; y /= mod;
    }
    return ans;
}

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
        rep (i, n) if (i < (rev[i] >> sh)) swap(a[i], a[rev[i]>>sh]);
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2*k) {
                for (int j = 0; j < k; j++) {
                    num z = a[i+j+k] * roots[j+k];
                    a[i+j+k] = a[i+j] - z;
                    a[i+j] += z;
                }
            }
        }
    }

    vector<int> operator * (const vector<int>& a, const vector<int>& b) {
        int sz = a.size() + b.size() - 1;
        vector<int> ret(sz);
        int nbase = 0;
        while ((1 << nbase) < sz) nbase++;
        ensure_base(nbase);
        sz = 1 << nbase;
        vector<num> fa(sz);
        rep (i, a.size()) fa[i].real(a[i]);
        rep (i, b.size()) fa[i].imag(b[i]);
        fft(fa);
        num r(0, -0.25 / sz);
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            num z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
            if (i != j) fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
            fa[i] = z;
        }
        fft(fa, sz);
        rep (i, ret.size()) ret[i] = llround(real(fa[i])) % mod;
        return ret;
    }
}

void printvec(const vector<int>& v, const char *name = "") {
    printf("%s:", name);
    for (int x : v) printf(" %d", x);
    puts("");
}


int n;
vector<int> a;

int main() {
    using namespace poly;
    init();
    scanf("%d", &n);
    rep (i, n) {
        int x; scanf("%d", &x);
        a.push_back(x);
    }
    for (int i = n - 1; i; i--) a[i-1] = min(a[i-1], a[i]);
    adjacent_difference(range(a), a.begin()); reverse(range(a));
    vector<int> s = {1};
    for (int y : a) {
//        _debug("%d(%d)", s.size(), y);
        s.push_back(s.back());
        if (y == 0) continue;
        int n = s.size();
        vector<int> ker(n);
        rep (i, n) ker[i] = cb(y + i-1, i);// printf("(%d, %d)", y+i-1, i); puts("");
//        printvec(ker, "ker");
//        printvec(s, "s");
        s = s * ker; s.resize(n);
//        printvec(s, "res");
    }
    cout << s.back() << endl;
    return 0;
}
