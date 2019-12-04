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

int n, d1, d2;
int a[100005];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &d1, &d2);
        rep (i, n) scanf("%d", a + i);
        LL ans = n;
        vector<pair<int, int>> seq;
        int last = INT_MAX, cnt = 0;
        for (int i = 1; i < n; i++) {
            int cur = a[i] - a[i-1];
            if (cur != last) {
                if (cnt) seq.emplace_back(last, cnt);
                last = cur; cnt = 0;
            }
            cnt++;
        }
        seq.emplace_back(last, cnt);
        for (auto pr : seq) {
            int x, c; tie(x, c) = pr;
            if (x == d1 || x == d2) ans += LL(c + 1) * c / 2;
        }
        for (int i = 1; i < seq.size(); i++) {
            int x1, c1, x2, c2;
            tie(x1, c1) = seq[i-1];
            tie(x2, c2) = seq[i];
            if (x1 == d1 && x2 == d2) ans += 1ll * c1 * c2;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
