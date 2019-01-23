#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#define PROBLEM "bridge"

struct pt {
    double x, y;
    double operator , (pt a) { return x * a.x + y * a.y; }
    double operator * (pt a) { return x * a.y - y * a.x; }
    pt operator - (pt a) { return {x - a.x, y - a.y}; }
    double norm() { return hypot(x, y); }
    friend ostream& operator << (ostream& os, pt p) {
        os << p.x << ',' << p.y;
        return os;
    }
} a[128], b[128];
int m, n;

double mindis(pt p, pt p1, pt p2) {
    // cout << p << ' ' << p1 << ' ' << p2 << endl;
    if (((p - p1), (p2 - p1)) < 0 or ((p - p2), (p1 - p2)) < 0)
        return min((p - p1).norm(), (p - p2).norm());
//    cout << "PERP" << endl;
    return fabs((p1 - p) * (p2 - p) / (p2 - p1).norm());
}

int main() {
    freopen(PROBLEM ".in", "r", stdin);
    freopen(PROBLEM ".out", "w", stdout);
    cin >> m;
    Rep (i, m) cin >> a[i].x >> a[i].y;
    a[0] = a[1]; a[0].y = -10000;
    a[m+1] = a[m]; m++; a[m].y = 10000;
    cin >> n;
    Rep (i, n) cin >> b[i].x >> b[i].y;
    b[0] = b[1]; b[0].y = -10000;
    b[n+1] = b[n]; n++; b[n].y = 10000;
    double ans = DBL_MAX;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            double cur = mindis(a[i], b[j], b[j+1]);
//            cout << i << ' ' << j << ' ' << cur << endl;
            ans = min(ans, cur);
        }
    }
    swap_ranges(range(a), b);
    swap(n, m);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            double cur = mindis(a[i], b[j], b[j+1]);
//            cout << i << ' ' << j << ' ' << cur << endl;
            ans = min(ans, cur);
        }
    }
    printf("%.12f\n", ans);
    return 0;
}
