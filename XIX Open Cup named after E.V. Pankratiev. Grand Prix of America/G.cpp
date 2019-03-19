#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL; 

vector<tuple<int, int, int>> queries;

int main() {
    int n; scanf("%d", &n);
    rep (i, n) {
        int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        queries.emplace_back(x1 * 2 + 1, y2, INT_MAX);
        queries.emplace_back(x2 * 2 - 1, y2, INT_MIN);
        queries.emplace_back(x1 * 2 + 1, y1, INT_MAX);
        queries.emplace_back(x2 * 2 - 1, y1, INT_MIN);
        queries.emplace_back(x1 * 2, y1, y2);
        queries.emplace_back(x2 * 2, y1, y2);
    }
    set<int> s;
    sort(range(queries));
    for (auto q : queries) {
        int y1, y2; tie(ignore, y1, y2) = q;
        if (y2 == INT_MIN) {
            assert(s.count(y1) == 1);
            s.erase(y1);
        } else if (y2 == INT_MAX) {
            assert(s.count(y1) == 0);
            s.insert(y1);
        } else {
            if (s.upper_bound(y1) != s.upper_bound(y2)) {
                puts("1");
                return 0;
            }
        }
    }
    puts("0");
    return 0;
}
