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
typedef struct pt {
    T x, y;
    T operator , (pt a) { return x*a.x + y*a.y; }
    T operator * (pt a) { return x*a.y - y*a.x; }
    pt operator + (pt a) { return {x + a.x ,y + a.y}; }
    pt operator - (pt a ) { return { x - a.x, y - a.y} ;}
    pt operator * (T k) { return {x*k, y*k} ; }
    pt operator - () { return {-x, -y}; }
    T length() { return hypot(x, y); }
} vec;

istream& operator >> (istream& lhs, pt& rhs) {
    lhs >> rhs.x >> rhs.y;
    return lhs;
}

inline pt getIntersection(pt P, vec v, pt Q, vec w) {
    return P + v * (w * (P - Q) / (v * w));
}

int k;
pt car[5];

double get_int_time(vector<pt> pts, pt base, vec v) {
    int n = pts.size();
    double ret = DBL_MAX;
    bool valid = false;
    for (int i = 0; i < n; i++) {
        double d1 = (pts[i] - base) * v;
        for (int j = i + 1; j < n; j++) {
            double d2 = (pts[j] - base) * v;
            if (d1 * d2 > 0) continue;
            if (v * (pts[j] - pts[i]) == 0) continue;
            pt point = getIntersection(pts[j], pts[i] - pts[j], base, v);
            if ((point - base, v) <= 0) continue;
            double tim = (point - base).length();  
            ret = min(ret, tim);
            if (d1 * d2 < 0) valid = true;
        }
    }
    if (valid) return ret;
    return DBL_MAX;
}

int main() {
    cin >> k;
    Rep (i, 4) cin >> car[i];
    vector<double> times;
    int num; cin >> num;
    rep (i, num) {
        int n; cin >> n;
        vector<pt> pts;
        rep (_, n) {
            int x, y, z; cin >> x >> y >> z;
            if (z == 0) pts.push_back(pt{x, y});
        }
        double tim = min(get_int_time(pts, car[2], car[2] - car[3]),
                         get_int_time(pts, car[1], car[1] - car[4]));
        if (tim == DBL_MAX) continue;
        times.push_back(tim);
    }
    sort(range(times));
    if (times.size() <= k) {
        cout << "oo" << endl;
    } else {
        printf("%.7f\n", times[k]);
    }
    return 0;
}
