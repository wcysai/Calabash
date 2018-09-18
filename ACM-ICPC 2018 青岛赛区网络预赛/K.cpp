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

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        map<int, int> mp;
        while (n--) {
            int a; scanf("%d", &a);
            mp[__builtin_clz(a)]++;
        }
        int ans = 0;
        for (auto& p : mp) ans = max(ans, p.second);
        printf("%d\n", ans);
    }
    return 0;
}
