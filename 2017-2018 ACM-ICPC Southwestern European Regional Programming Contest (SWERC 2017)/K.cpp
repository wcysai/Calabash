#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)

typedef long long T;
typedef struct pt {
    T x, y;
    T operator , (pt a) {return x*a.x + y*a.y;} // inner product
    T operator * (pt a) {return x*a.y - y*a.x;} // outer product
    pt operator + (pt a) {return {x+a.x, y+a.y};}
    pt operator - (pt a) {return {x-a.x, y-a.y};}

    pt operator * (T k) {return {x*k, y*k};}
    pt operator - () {return {-x, -y};}

    T norm() {return x*x+y*y;}
} vec;

typedef pair<pt, pt> seg;

bool ptOnSeg(pt& p, seg& s) {
    vec v1 = s.first - p, v2 = s.second - p;
    return (v1, v2) <= 0 && v1 * v2 == 0;
}

// 0 not on segment
// 1 on segment except vertices
// 2 on vertices
int ptOnSeg2(pt& p, seg& s) {
    vec v1 = s.first - p, v2 = s.second - p;
    T ip = (v1, v2);
    if (v1 * v2 != 0 || ip > 0) return 0;
    return (v1, v2) ? 1 : 2;
}

// if two orthogonal rectangles do not touch, return true
inline bool nIntRectRect(seg a, seg b) {
    return min(a.first.x, a.second.x) > max(b.first.x, b.second.x) ||
           min(a.first.y, a.second.y) > max(b.first.y, b.second.y) ||
           min(b.first.x, b.second.x) > max(a.first.x, a.second.x) ||
           min(b.first.y, b.second.y) > max(a.first.y, a.second.y);
}

// >0 in order
// <0 out of order
// =0 not standard
inline double rotOrder(vec a, vec b, vec c) {return double(a*b)*(b*c);}

inline bool intersect(seg a, seg b) {
    if (nIntRectRect(a, b)) return false;
    return rotOrder(b.first-a.first, a.second-a.first, b.second-a.first) >= 0 &&
           rotOrder(a.first-b.first, b.second-b.first, a.second-b.first) >= 0;
}

// 0 not insersect
// 1 standard intersection
// 2 vertex-line intersection
// 3 vertex-vertex intersection
// 4 collinear and have common point(s)
int intersect2(seg a, seg b) {
    if (nIntRectRect(a, b)) return 0;
    vec va = a.second - a.first, vb = b.second - b.first;
    double j1 = rotOrder(b.first-a.first, va, b.second-a.first),
           j2 = rotOrder(a.first-b.first, vb, a.second-b.first);
    if (j1 < 0 || j2 < 0) return 0;
    if (j1 != 0 && j2 != 0) return 1;
    if (j1 == 0 && j2 == 0){
        if (va * vb == 0) return 4; else return 3;
    } else return 2;
}

template <typename Tp = T>
inline pt getIntersection(pt P, vec v, pt Q, vec w) {
    static_assert(is_same<Tp, double>::value, "must be double!");
    return P + v * (w*(P-Q)/(v*w));
}

inline double distPtSeg(pt p, seg s) {
    return double((p - s.second) * (s.first - s.second))
        / sqrt((s.first - s.second).norm());
}

// -1 outside the polygon
// 0  on the border of the polygon
// 1  inside the polygon
int ptOnPoly(pt p, pt* poly, int n) {
    int wn = 0;
    for (int i = 0; i < n; i++){
        T k, d1 = poly[i].y - p.y, d2 = poly[(i+1)%n].y - p.y;
        if ((k = (poly[(i+1)%n] - poly[i]) * (p - poly[i]))) {
            if (k > 0 && d1 <= 0 && d2 > 0) wn++;
            if (k < 0 && d2 <= 0 && d1 > 0) wn--;
        } else return 0;
    }
    return wn ? 1 : -1;
}

istream& operator >> (istream& lhs, pt& rhs){
    lhs >> rhs.x >> rhs.y;
    return lhs;
}

istream& operator >> (istream& lhs, seg& rhs){
    lhs >> rhs.first >> rhs.second;
    return lhs;
}

vector<pt> convexHull(pt* pts, int n) {
    int nn;
    vector<pt> ans(n+n);
    sort(pts, pts+n, [] (pt& lhs, pt &rhs) {
        return make_pair(lhs.x, lhs.y) < make_pair(rhs.x, rhs.y);
    });
    nn = 0;
    rep (i, n) {
        while (nn > 1 && (ans[nn-1] - ans[nn-2]) * (pts[i] - ans[nn-2]) <= 0) 
            nn--;
        ans[nn++] = pts[i];
    }
    int key = nn;
    for (int i = n - 2; i >= 0; i--) {
        while (nn > key && (ans[nn-1] - ans[nn-2]) * (pts[i] - ans[nn-2]) <= 0) 
            nn--;
        ans[nn++] = pts[i];
    }
    if (nn > 1) nn--;
    ans.resize(nn);
    return ans;
};

double rotatingCalipers(pt* pts, int n) {
    int i = 2;
    double ans = DBL_MAX;
    for (int j = 0; j < n; j++) {
        seg l(pts[j], pts[(j+1)%n]);
        while (distPtSeg(pts[i], l) < distPtSeg(pts[(i+1)%n], l)) i = (i+1)%n;
        ans = min(ans, distPtSeg(pts[i], l));
    }
    return ans;
}

int n, r;
pt pts[200006];

int main() {
    cin >> n >> r;
    rep (i, n) cin >> pts[i];
    vector<pt> ch = convexHull(pts, n);
    n = 0;
    for (pt p : ch) pts[n++] = p;
    printf("%.7f", rotatingCalipers(pts, n));
    
    return 0;
}
