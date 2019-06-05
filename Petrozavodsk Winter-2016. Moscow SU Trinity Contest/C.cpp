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

int n;
const int wrap = 1296000;
vector<pair<int, int>> rg;

void addrange(int l, int r) {
    if (l >= wrap) {
        l -= wrap;
        r -= wrap;
    }
    if (r <= wrap) {
        rg.emplace_back(l, r);
    } else {
        rg.emplace_back(l, wrap);
        rg.emplace_back(0, r - wrap);
    }
}

[[noreturn]] void getans(int x) {
    puts("YES");
    double rho = (x + 0.5) / wrap * 2 * acos(-1);
    complex<double> cplx = polar(1000000000.0 - 1.0, rho);
    printf("%d %d", int(cplx.real()), int(cplx.imag()));
    exit(0);
}

int main() {
    scanf("%d", &n);
    rep (i, n) {
        int x, y, dr, dl;
        scanf("%d%d%d%d", &x, &y, &dr, &dl);
        addrange(dl, dl + dr);
    }
    sort(range(rg));
    int cr = 0;
    for (auto p : rg) {
       int l, r; tie(l, r) = p;
       if (l > cr) getans(cr);
       cr = max(cr, r);
    }
    if (cr < wrap) getans(cr);
    puts("NO");
    return 0;
}
