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

int minv;
vector<int> c;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        c.clear(); minv = INT_MAX;
        int n; scanf("%d", &n);
        map<int, int> cnt;
        while (n--) {
            int x; scanf("%d", &x);
            cnt[x]++;
        }
        for (auto pr : cnt) {
            c.push_back(pr.second);
            minv = min(minv, pr.second + 1);
        }
        int ans = INT_MAX;
        for (int i = 2; i <= minv; i++) {
            int cur = 0;
            for (int x : c) {
                int nr_use = (x + i - 1) / i;
                if (nr_use * i - x > nr_use) goto cont;
                cur += nr_use;
            }
            ans = min(ans, cur);
        cont:;
        }
        printf("%d\n", ans);
    }
    return 0;
}
