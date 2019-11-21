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

int n, p;
int l[1024], r[1024];
int cnt[1024];
set<int> already;

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d%d", l + i, r + i);
    scanf("%d", &p);
    rep (i, p) {
        int x; scanf("%d", &x);
        rep (i, n) if (l[i] <= x and x <= r[i]) cnt[i]++;
        already.insert(x);
    }
    rep (i, n) if (cnt[i] > 2) return puts("impossible"), 0;
    vector<int> pos;
    rep (i, n) {
        if (cnt[i] == 2) continue;
        if (cnt[i] == 0) {
            int po = l[i] + 1; while (already.count(po)) po++;
            pos.push_back(po);
            cnt[i]++;
        }
        if (cnt[i] == 1) {
            if (i + 1 < n and r[i] == l[i+1] and cnt[i+1] < 2 and already.count(r[i]) == 0) {
                pos.push_back(r[i]);
                cnt[i]++; cnt[i+1]++;
            } else {
                int po = r[i] - 1; while (already.count(po)) po--;
                pos.push_back(po);
                cnt[i]++;
            }
        }
    }
    printf("%d\n", int(pos.size()));
    for (int x : pos) printf("%d ", x); puts("");
    return 0;
}
