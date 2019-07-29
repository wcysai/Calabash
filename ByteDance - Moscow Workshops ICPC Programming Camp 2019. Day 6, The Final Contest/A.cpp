#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n, m;
set<int> cur[300005];
int odeg[300005];

void merge(set<int>& a, set<int>& b) {
    if (a.size() < b.size()) swap(a, b);
    for (int x : b) a.insert(x);
}

int main() {
    scanf("%d%d", &n, &m);
    rep (_, m) {
        int u, v; scanf("%d%d", &u, &v);
        cur[u].insert(v);
    }
    Rep (i, n) {
        odeg[i] = cur[i].size();
        if (cur[i].size()) {
            int x = *cur[i].begin();
            cur[i].erase(cur[i].begin());
            merge(cur[x], cur[i]);
        }
    }
    LL ans = 1;
    Rep (i, n) ans = ans * (n - odeg[i]) % 998244353;
    cout << ans << endl;
    return 0;
}
