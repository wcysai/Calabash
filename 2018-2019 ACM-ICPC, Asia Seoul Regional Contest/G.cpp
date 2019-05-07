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
vector<tuple<int, int, LL>> ts;

LL subcalc(int s, int a, int b, int c) {
    LL ans = 0;
    ans += a * a * b;
    ans += (s - a - b) * a * b * 2;
    ans += a * b * b;
    return ans;
}

LL calc(int s, int a, int b, int c) {
    LL ans = 0;
    ans += subcalc(s, a, b, c);
    ans += subcalc(s, a, c, b);
    ans += subcalc(s, b, a, c);
    ans += subcalc(s, b, c, a);
    ans += subcalc(s, c, a, b);
    ans += subcalc(s, c, b, a);
    return ans;
}

int main() {
    cin >> n;
    rep (i, n) {
        int s, a, b, c; cin >> s >> a >> b >> c;
        ts.emplace_back(i, s, calc(s, a, b, c));
    }
    sort(range(ts), [] (auto x, auto y) {
        LL id1, s1, v1, id2, s2, v2;
        tie(id1, s1, v1) = x;
        tie(id2, s2, v2) = y;
        v1 *= s2 * s2 * s2;
        v2 *= s1 * s1 * s1;
        if (v1 == v2) return id1 < id2;
        return v1 < v2;
    });
    for (auto x : ts) cout << get<0>(x) + 1<< ' ';
    return 0;
}
