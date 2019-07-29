#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)

typedef complex<double> point;
map<tuple<int, int, int>, int> circles;

//#define __LOCAL_DEBUG__

int _query(double x, double y) {
#ifdef __LOCAL_DEBUG__
    static vector<tuple<int, int, int>> cs = {
        {1, 2, 1},
        {3, 4, 2},
        {3, 4, 2},
        {2, 2, 2},
        {8, 3, 1},
        {10, 10, 10},
        {10, 10, 9},
    };
    
    int cnt = 0;
    for (auto p : cs) {
        int xx, yy, r; tie(xx, yy, r) = p;
        if (hypot(xx - x, yy - y) <= r) cnt++;
    }
    return cnt;
#endif
    printf("Test %.9f %.9f\n", x, y);
    fflush(stdout);
    int ret; scanf("%d", &ret);
    return ret;
}

int query(double x, double y) {
    int cnt = 0;
    for (auto& c : circles) {
        double x0, y0, r;
        tie(x0, y0, r) = c.first;
        if (hypot(x - x0, y - y0) <= r) cnt += c.second;
    }
    int ret = _query(x, y) - cnt;

    return ret;
}


#define DOWN 1
#define LEFT 2
const double pi = acos(- 1.0);
const double eps = 2e-5;
void test(int x, int y, int r, int dir) {
    if (x + r > 20 or y + r > 20) return;
    double xx = x, yy = y;
    if (dir == LEFT) {
        xx += cos(-pi + eps * 1000) * (r - eps);
        yy += sin(-pi + eps * 1000) * (r - eps);
    } else {
        xx += cos(-pi/2 + eps * 1000) * (r - eps);
        yy += sin(-pi/2 + eps * 1000) * (r - eps);
    }
    int ret = query(xx, yy);
    if (ret > 0) {
    //    printf("%d %d %d detected %d\n", x, y, r, ret);
        circles[make_tuple(x, y, r)] = ret;
    } else if (ret < 0) {
        //printf("%d %d %d detected %d\n", x, y, r, ret);
    }
}

void solve(int l) {
    for (int i = l + 1; i < 20; i++) {
        test(i, i, i - l, DOWN);
        for (int j = i - 1; j > l; j--) {
            test(i, j, j - l, DOWN);
            test(j, i, j - l, LEFT);
        }
    }
}

int main() {
    for (int l = 0; l <= 20; l++) solve(l);
    int ans = 0;
    for (auto p : circles) ans += p.second;
    printf("Done %d\n", ans); 
    return 0;
}
