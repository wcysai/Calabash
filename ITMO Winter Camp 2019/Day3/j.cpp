#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#define PROBLEM "shooting"
typedef long long LL;
typedef unsigned long long ULL;

int n;

const double pi = acos(-1);
struct pt {
    double x, y;
    pt operator - (pt a) { return {x - a.x, y - a.y}; } 
    double operator * (pt a) { return x * a.y - y * a.x; }
    double arg() { return atan2(y, x); }
};

pt s[12], t[12];
mt19937 gen(time(NULL));
uniform_real_distribution<> dis(0, 2000.0);

int check(pt p) {
    vector<pair<double, bool>> x;
    int init = 0, ans;

    auto add_range = [&] (double from, double to) {
//        fprintf(stderr, "Range: %.15f %.15f\n", from, to);
        x.emplace_back(from, true);
        x.emplace_back(to, false);
    };

    rep (i, n) {
        if ((s[i] - p) * (t[i] - p) < 0) 
            swap(s[i], t[i]);
        double r1 = (s[i] - p).arg(), r2 = (t[i] - p).arg();
        add_range(r1, r2);
        if (r1 > r2) init++;
    }
    ans = init;
    sort(range(x));
    for (auto& p : x) {
        if (p.second) init++; else init--;
        ans = max(ans, init);
    }
    return ans;
}

int main() {
    freopen("shooting.in", "r", stdin);
     freopen("shooting.out", "w", stdout);
    cin >> n;
    rep (i, n) cin >> s[i].x >> s[i].y >> t[i].x >> t[i].y;
    double ax, ay; 
//    while (cin >> ax >> ay) cout << check(pt{ax, ay}) << endl;
    int cur = INT_MAX;
    rep (_, 500000) {
        double phi = dis(gen);
        double xx = 30000 * sin(phi), yy = 30000 * cos(phi);
        int val = check(pt{xx, yy});
        if (val < cur) {
            cur = val;
            ax = xx;
            ay = yy;
        }
    }
    printf("%d\n", cur);
    printf("%.15f\n%.15f\n", ax, ay);
    return 0;
}
