#pragma  GCC optimize(3)
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

typedef pair<int, int> point;

inline point operator - (point a, point b) {
    return {a.first - b.first, a.second - b.second};
}

inline point reduce(point pt) {
    if (pt.first == 0) return {0, 1};
    if (pt.second == 0) return {1, 0};
    int g = __gcd(abs(pt.first), abs(pt.second));
    pt.first /= g; pt.second /= g;
    if (pt.first < 0) {
        pt.first = -pt.first;
        pt.second = -pt.second;
    }
    return pt;
}

vector<point> slope;
int m;
point pts[24];
bool sel[24];
int tot_ans = 0;

void update_answer() {
    vector<point> slopes = slope;
    sort(range(slopes));
    /*
    for (auto p : slopes) {
        printf("%d/%d ", p.first, p.second);
    }
    puts("");
     */
    auto lit = slopes.begin(), rit = lit;
    int ans = 0;
    while (rit != slopes.end()) {
        lit = rit;
        while (rit != slopes.end() and *rit == *lit) rit++;
        int cnt = rit - lit;
        ans += cnt * (cnt - 1) / 2;
    }
    tot_ans = max(tot_ans, ans);
}

void recursive_construct(int cur, int rem) {
    if (rem == 0) {
        update_answer();
        return ;
    }
    while (sel[cur]) cur++;
    sel[cur] = true;
    for (int pair = cur + 1; pair < m; pair++) {
        if (sel[pair]) continue;
        sel[pair] = true;
        slope.push_back(reduce(pts[pair] - pts[cur]));
        recursive_construct(cur + 1, rem - 1);
        slope.pop_back();
        sel[pair] = false;
    }
    sel[cur] = false;
}

int main() {
    scanf("%d", &m);
    rep (i, m) {
        int x, y; scanf("%d%d", &x, &y);
        pts[i] = {x, y};
    }
    recursive_construct(0, m / 2);
    printf("%d\n", tot_ans);
    return 0;
}
