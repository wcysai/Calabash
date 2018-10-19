#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

void xfrm(int& x, int& y) {
    tie(x, y) = make_pair(x + y, x - y + 1000000);
}

int r, q;
int ans[200005];

struct query {
    int l, r, pos;

    query(int l, int r, int pos) :
        l(l), r(r), pos(pos) {}
};

vector<int> points[2000005];
vector<query> queries[2000005];

struct bit_purq {
    int tr[2000005];

    void inc(int x) {
        _debug("%d", x);
        while (x < 2000005) {
            tr[x]++;
            x += x & -x;
        }
    }

    int query(int x) {
        _debug("%d", x);
        int ans = 0;
        while (x) {
            ans += tr[x];
            x -= x & -x;
        }
        _debug("%d", ans);
        return ans;
    }
} bit;

int main() {
    scanf("%d", &r);
    rep (i, r) {
        int x, y; scanf("%d%d", &x, &y);
        xfrm(x, y);
        points[x].push_back(y);
    }
    scanf("%d", &q);
    Rep (i, q) {
        int x, y, d; scanf("%d%d%d", &x, &y, &d);
        xfrm(x, y);
        queries[max(0, x - d - 1)].emplace_back(max(0, y - d - 1), min(2000002, y + d), -i);
        queries[min(2000002, x + d)].emplace_back(max(0, y - d - 1), min(2000002, y + d), i);
    }
    for (int i = 0; i <= 2000003; i++) {
        for (int y : points[i]) {
            bit.inc(y);
        }
        for (auto& qu : queries[i]) {
            int l = qu.l, r = qu.r, pos = qu.pos;
            _debug("%d: %d", i, pos);
            if (pos < 0) {
                ans[-pos] -= bit.query(r) - bit.query(l);
            } else {
                ans[pos] += bit.query(r) - bit.query(l);
            }
        }
    }
    Rep (i, q) printf("%d\n", ans[i]);

    return 0;
}

/*
3
 2 2
 3 1
 4 1
 2
 3 2 1
 4 2 1
 */

/*
5
 3 2
 3 6
 4 6
 2 4
 4 6
 2
 4 4 2
 3 4 3

 */
