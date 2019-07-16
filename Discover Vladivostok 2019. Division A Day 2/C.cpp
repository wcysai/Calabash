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

int n;
int a[1 << 20];
bool vis[1 << 20];
vector<int> swaps;

bool try_sort(int l, int r) {
    vector<int> swp;
    for (int i = l; i < r; i++) {
        for (int j = i - 1; j >= l; j--) {
            if (a[j] > a[j+1]) {
                swap(a[j], a[j+1]);
                swp.push_back(j);
                if (swp.size() >= r - l) return false;
            } else break;
        }
    }
    swaps.insert(swaps.end(), range(swp));
    return true;
}

vector<pair<int, int>> find_cycle() {
    vector<pair<int, int>> cycs;
    Rep (i, n) if (!vis[i]) {
        int u = i;
        vector<int> cyc;
        while (!vis[u]) {
            vis[u] = true;
            cyc.push_back(u);
            u = a[u];
        }
        int l = *min_element(range(cyc)), r = *max_element(range(cyc)) + 1;
        if (r - l == cyc.size()) cycs.emplace_back(l, r);
    }
    return cycs;
}

int main() {
    while (scanf("%d", &n), n) {
        Rep (i, n) scanf("%d", a + i);
        fill(vis + 1, vis + n + 1, false);
        swaps.clear();
        vector<pair<int, int>> cycs = find_cycle();
        int ans = n;
        for (auto p : cycs) 
            if (try_sort(p.first, p.second)) ans--;
        printf("%d %d ", ans, int(swaps.size()));
        for (int x : swaps) printf(" %d", x);
        puts("");
    }
    return 0;
}
