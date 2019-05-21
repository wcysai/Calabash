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

const LL maxval = 4e12;
int n;
set<pair<int, int>> ans;


inline LL dd(LL x, LL y) {
    return x * x + y * y;
}

#ifdef __LOCAL_DEBUG__

vector<pair<int, int>> pts = {
    {1, -1}, {-1, 1}, {1, 1}, {-1, -1}, {0, 0}, {-2, 1}, {2, -1},
    {0, 1e6}, {0, -1e6}, {-1e6, 0}, {1e6, 0},
    {3, 4}, {-3, 4}, {3, -4}, {-3, -4},
    {4, 3}, {4, -3}, {-4, 3}, {-4, -3},
    {5, 0}, {0, 5}, {-5, 0}, {0, -5}
};


int query(int x, int y, LL r) {
    int cnt = 0;
    for (auto p : pts) 
        if (dd(p.first - x, p.second - y) <= r) cnt++;
    return cnt;
}

#else

int query(int x, int y, LL r) {
    if (max(abs(x), abs(y)) > 1000000) {
        assert(r == 0);
        return 0;
    }
    static int cnt = 0; cnt++; assert(cnt <= 15000);
    int ret;
    printf("? %d %d %lld\n", x, y, r);
    fflush(stdout); scanf("%d", &ret);
    return ret;
}

#endif

void attempt(int x, int y) {
    if (query(x, y, 0)) ans.emplace(x, y);
}

set<LL> susp1, susp2;

void attempt2(int x, int y) {
    if (!susp2.count(dd(x + 2, y - 1))) return;
    if (query(x, y, 0)) ans.emplace(x, y);
}

void solve1(LL l, int nl, LL r, int nr) {
    if (r == l + 1) {
        susp1.insert(r);
        return;
    }
    LL m = (l + r) / 2;
    int nm = query(0, 0, m);
    if (nm != nl) solve1(l, nl, m, nm);
    if (nm != nr) solve1(m, nm, r, nr);
}

void solve2(LL l, int nl, LL r, int nr) {
    if (r == l + 1) {
        susp2.insert(r);
        return;
    }
    LL m = (l + r) / 2;
    int nm = query(-2, 1, m);
    if (nm != nl) solve2(l, nl, m, nm);
    if (nm != nr) solve2(m, nm, r, nr);
}

void ssolve(LL x) {
    for (LL i = 0; i * i <= x; i++) {
        LL r = x - i * i, j = sqrt(r) + 0.5;
        if (j * j == r) {
            attempt2(i, j);
            attempt2(-i, j);
            attempt2(i, -j);
            attempt2(-i, -j);
        }
    }
}

int main() {
#ifdef __LOCAL_DEBUG__
    n = pts.size();
#else
    scanf("%d", &n);
#endif
    if (query(0, 0, 0)) susp1.insert(0);
    if (query(-2, 1, 0)) susp2.insert(0);
    solve1(0, query(0, 0, 0), maxval, query(0, 0, maxval));
    solve2(0, query(-2, 1, 0), maxval, query(-2, 1, maxval));
    for (LL d : susp1) ssolve(d);
    assert(ans.size() == n);
    putchar('!');
    for (auto p : ans) printf(" %d %d", p.first, p.second);
    putchar('\n');
    return 0;
}
