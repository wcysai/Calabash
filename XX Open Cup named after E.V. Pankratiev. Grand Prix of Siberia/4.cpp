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
typedef __int128_t i128;

map<int, int> cnt;

i128 sqrti(i128 x) {
    LL y = sqrt((double)x);
    while ((y+1)*(y+1) <= x) y++;
    return y;
}

void solve2(i128 a, i128 b, i128 c) {
    i128 delta = b * b - 4 * a * c;
    if (delta < 0) return;
    i128 rd = sqrti(delta); if (rd * rd != delta) return;
    i128 num1 = -b + rd, num2 = -b - rd, denom = 2 * a;
    if (num1 % denom == 0) cnt[num1 / denom]++;
    if (num2 % denom == 0) cnt[num2 / denom]++;
}

i128 a, b, c, d;

i128 eval(i128 x) {
    return ((a * x + b) * x + c) * x + d;
}

void check_root(i128 x) {
    if (eval(x)) return;
    cnt[x]++;
    b += a * x; c += b * x; d += c * x; assert(d == 0);
    solve2(a, b, c);
    throw 0;
}

int sgn(i128 x) { if (x) return x > 0 ? 1 : -1; return 0; }

void solve(int l, int r) {
    if (l > r) return;
    if (sgn(eval(l)) * sgn(eval(r)) > 0) return;
    while (r - l > 1) {
       int m = l + (r - l) / 2;
       if (sgn(eval(m)) * sgn(eval(l)) <= 0) r = m; else l = m;
    }
    check_root(l); check_root(r);
}

vector<int> sp;

void solvesp(i128 a, i128 b, i128 c) {
    i128 delta = b * b - 4 * a * c;
    if (delta < 0) return;
    i128 rd = sqrti(delta);
    i128 num1 = -b + rd, num2 = -b - rd, denom = 2 * a;
    i128 r1 = num1 / denom, r2 = num2 / denom;
    if (abs((double)r1) <= 1000000000) { check_root(r1); sp.push_back(r1); }
    if (abs((double)r2) <= 1000000000) { check_root(r2); sp.push_back(r2); }
}

int main() {
    int n; scanf("%d", &n);
    while (n--) {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        i128 g = __gcd(__gcd(a, b), __gcd(c, d));
        a /= g; b /= g; c /= g; d /= g;
        ::a = a; ::b = b; ::c = c; ::d = d;
        sp = {-1000000005, 1000000005};
        try {
            solvesp(3 * a, 2 * b, c);
            sort(range(sp));
            rep (i, sp.size() - 1) solve(sp[i] + 1, sp[i+1] - 1);
        } catch (...) { }
    }
    if (cnt.empty()) return puts("NO"), 0;
    puts("YES");
    int rt, cn;
    tie(rt, cn) = *max_element(range(cnt), [] (pair<int, int> x, pair<int, int> y) {
        return x.second < y.second;
    });
    printf("%d %d", rt, cn);
    return 0;
}
