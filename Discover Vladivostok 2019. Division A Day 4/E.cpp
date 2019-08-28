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

typedef double T;

typedef complex<T> pt, vec;
inline pt operator ^ (pt a, pt b) { return a * b; }
inline T operator , (pt a, pt b) { return real(a) * real(b) + imag(a) * imag(b); }
inline T operator * (pt a, pt b) { return real(a) * imag(b) - imag(a) * real(b); }

inline bool rotOrder(vec a, vec b, vec c) {
    return double(a * b) * (b * c) >= 0;
}

struct polygon : vector<pt> {
    pt& operator [] (int id) {
        while (id < 0) id += int(size());
        while (id >= int(size())) id -= int(size());
        return at(id);
    }

    void make_hull(vector<pt> pts) {
        sort(pts.begin(), pts.end(), [] (pt a, pt b) {
            return make_pair(real(a), imag(a)) < make_pair(real(b), imag(b));
        });
        int k = 0;
        resize(pts.size() * 2);
        for (int i = 0; i < pts.size(); i++) {
            while (k > 1 and (at(k-1) - at(k-2)) * (pts[i] - at(k-1)) <= 0) k--;
            at(k++) = pts[i];
        }
        for (int i = pts.size() - 2, t = k; i >= 0; i--) {
            while (k > t and (at(k-1) - at(k-2)) * (pts[i] - at(k-1)) <= 0) k--;
            at(k++) = pts[i];
        }
        resize(k-1);
    }
} poly;


double ans = 1e110;
pt pts[4];

pt getIntersection(pt P, vec v, pt Q, vec w) {
    return P + v * (w * (P - Q) / (v * w));
}

void update(pt u, pt v, pt w, pt x, pt v1, pt v2, pt v3, pt v4) {
    pt pp[4] = {
        getIntersection(u, v1, x, v4),
        getIntersection(v, v2, u, v1),
        getIntersection(w, v3, v, v2),
        getIntersection(x, v4, w, v3)
    };
    double area = abs(pp[0] - pp[1]) * abs(pp[1] - pp[2]);
    if (area < ans) {
        ans = area;
        memcpy(pts, pp, sizeof pts);
    }
}

void solve() {
    int n = poly.size();
    int v = 0, w = 0, x = 0;
    for (int u = 0; u < n; u++) {
        vec v1 = poly[u + 1] - poly[u];
        vec v2 = v1 ^ 1i, v3 = v2 ^ 1i, v4 = v3 ^ 1i;
        while (v < u || !rotOrder(poly[v-1] - poly[v], poly[v+1] - poly[v], v2)) v++;
        while (w < v || !rotOrder(poly[w-1] - poly[w], poly[w+1] - poly[w], v3)) w++;
        while (x < w || !rotOrder(poly[x-1] - poly[x], poly[x+1] - poly[x], v4)) x++;
        update(poly[u], poly[v], poly[w], poly[x], v1, v2, v3, v4);
    }
}

int main() {
    int n;
    vector<pt> pts;
    scanf("%d", &n);
    rep (i, n) {
        double x, y; scanf("%lf%lf", &x, &y);
        pts.emplace_back(x, y);
    }
    poly.make_hull(pts);
    solve();
    for (auto p : ::pts) printf("%.12f %.12f\n", real(p), imag(p));
    return 0;
}
