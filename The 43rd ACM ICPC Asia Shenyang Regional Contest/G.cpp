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

int m;
vector<pair<int, int>> dis[10000005];
// map<int, vector<pair<int, int>>> dis;
map<pair<int, int>, LL> wt;
const int maxs = 10'000'000;

void push_pair(int a, int b, int norm) {
    dis[norm].emplace_back(a, b);
    if (a > 0) dis[norm].emplace_back(-a, b);
    if (b > 0) dis[norm].emplace_back(a, -b);
    if (a > 0 and b > 0) dis[norm].emplace_back(-a, -b);
}

void prep() {
    static int cnt = 0;
    for (int i = 0; i * i <= maxs; i++) {
        for (int j = 0; i * i + j * j <= maxs; j++) {
            cnt++;
            push_pair(i, j, i * i + j * j);
        }
    }
    // _debug("%d", cnt);
}

LL lastans;

void case_init() {
    lastans = 0;
    wt.clear();
    int n; scanf("%d%d", &n, &m);
    while (n--) {
        int x, y, w; scanf("%d%d%d", &x, &y, &w);
        wt[{x, y}] = w;
    }
}


void work(int kase) {
    cout << "Case #" << kase << ":" << endl;
    case_init();
    while (m--) {
        int q, x, y, k, w; scanf("%d%d%d", &q, &x, &y);
        x = (x + lastans) % 6000 + 1;
        y = (y + lastans) % 6000 + 1;
        // _debug("query %d", q);
        switch (q) {
            case 1:
                scanf("%d", &w);
                wt[{x, y}] = w;
                break;
            case 2:
                wt.erase({x, y});
                break;
            case 3: {
                scanf("%d%d", &k, &w);
//                auto it = dis.find(k);
//                if (it == dis.end()) break;
                for (auto p : dis[k]) {
                    int cx = x + p.first, cy = y + p.second;
                    auto it2 = wt.find({cx, cy});
                    if (it2 == wt.end()) continue;
                    // _debug("increase (%d, %d)", cx, cy);
                    it2->second += w;
                }
            }
                break;
            case 4: {
                scanf("%d", &k);
//               auto it = dis.find(k);
//               if (it == dis.end()) break;
                LL ans = 0;
                for (auto p : dis[k]) {
                    int cx = x + p.first, cy = y + p.second;
                    auto it2 = wt.find({cx, cy});
                    if (it2 == wt.end()) continue;
                    // _debug("query (%d, %d) = %d", cx, cy, int(it2->second));
                    ans += it2->second;
                }
                lastans = ans;
                cout << ans << endl;
            }
                break;
        }
    }

}

int main() {
    prep();
    int T; scanf("%d", &T);
    Rep (t, T) work(t);
    return 0;
}
