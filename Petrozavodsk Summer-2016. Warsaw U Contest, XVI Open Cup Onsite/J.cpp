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
LL a, b;

typedef pair<LL, LL> pt;

pt norm(pt x) {
    LL g = abs<LL>(__gcd(x.first, x.second));
    return {x.first / g, x.second / g};
}

pt operator - (pt a, pt b) { return { a.first - b.first, a.second - b.second }; }

LL length(pt x) { return x.first * x.first + x.second * x.second; }
LL operator , (pt a, pt b) { return a.first * b.first + a.second * b.second; }

vector<pt> pts;

int getans(pt dir, const vector<pt>& vecs, LL s) {
    int l = 0, r = vecs.size();
    while (l < r) {
        int mid = (l + r) / 2;
        if ((dir, vecs[mid]) >= s) r = mid; else l = mid + 1;
    }
    return l;
}

int main() {
    scanf("%d", &n);
    scanf("%lld%lld", &a, &b); a *= 2; b = b * 2 + 1;
    rep (i, n) {
        int x, y; scanf("%d%d", &x, &y);
        pts.emplace_back(x, y);
    }
    LL ans = 0;
    rep (i, n) {
        map<pt, vector<pt>> ps;
        rep (j, n) if (i != j) ps[norm(pts[j] - pts[i])].push_back(pts[j] - pts[i]);
        for (auto& vec : ps) sort(range(vec.second), 
                [] (pt a, pt b) { return length(a) < length(b); });
        rep (j, n) if (i != j) {
            pt dir = pts[j] - pts[i];
            dir = {-dir.second, dir.first};
            auto it = ps.find(norm(dir));
            if (it == ps.end()) continue;
            ans += getans(dir, it->second, b) - getans(dir, it->second, a);
        }
    }
    cout << ans << endl;
    return 0;
}
