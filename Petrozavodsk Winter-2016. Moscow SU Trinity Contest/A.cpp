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

const LL p = 1012423549;

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % p;
        b = b * b % p;
        e >>= 1;
    }
    return r;
}

typedef vector<LL> VLL;
typedef vector<VLL> VVLL;

int rref(VVLL& a) {
    int n = a.size(), m = a[0].size();
    int r = 0;
    rep (c, m) {
        int j = r;
        for (int i = r + 1; i < n; i++)
            if (abs(a[i][c]) > abs(a[j][c])) j = i;
        if (a[j][c] == 0) continue;
        swap(a[j], a[r]);

        LL s = powmod(a[r][c], p - 2);
        rep (j, m) a[r][j] = a[r][j] * s % p;
        rep (i, n) if (i != r) {
            LL t = a[i][c];
            rep (j, m) a[i][j] = (a[i][j] - t * a[r][j] % p + p) % p;
        }
        r++;
        if (r == min(n, m)) return r;
    }
    return r;
}

int h, w;
VVLL M;

int main() {
    cin >> h >> w;
    assert(1 <= h and h <= 200); assert(1 <= w and w <= 200);
    M.resize(h); for (auto& v : M) v.resize(w);
    rep (i, h) rep (j, w) {
        cin >> M[i][j];
        assert(M[i][j] >= -1000000 and M[i][j] <= 1000000);
        M[i][j] = (M[i][j] + p) % p;
    }
    cout << rref(M) << endl;
    return 0;
}
